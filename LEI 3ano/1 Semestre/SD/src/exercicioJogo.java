import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.locks.*;

// Interfaces fornecidas no enunciado
interface Jogo {
    Partida participa() throws InterruptedException;
}

interface Partida {
    int numeroJogadores();
    String adivinha(int n);
}

// Implementação
class JogoImpl implements Jogo {
    Lock l = new ReentrantLock();
    Condition cond = l.newCondition();

    Partida partida = new Partida();

    public Partida participa() throws InterruptedException {
        l.lock();
        try {
            Partida p = partida;
            
            while (partida == p)
                cond.await();
                
        } finally {
            l.unlock();
        }
    }
}

class PartidaManager {
    private final Lock lock = new ReentrantLock();
    private final Condition enoughPlayers = lock.newCondition();
    private final List<Jogador> waitingPlayers = new ArrayList<>();
    private long firstPlayerArrivalTime = -1;
    private int partidaCounter = 0;
    
    public Partida participa() {
        lock.lock();
        try {
            Jogador jogador = new Jogador();
            waitingPlayers.add(jogador);
            
            if (firstPlayerArrivalTime == -1) {
                firstPlayerArrivalTime = System.currentTimeMillis();
            }
            
            // Verifica se podemos iniciar uma partida
            checkStartPartida();
            
            // Bloqueia até a partida começar
            while (!jogador.isPartidaStarted()) {
                try {
                    // Aguarda até 2 minutos ou ser notificado
                    if (!enoughPlayers.await(2, TimeUnit.MINUTES)) {
                        // Timeout de 2 minutos - verifica se podemos começar com jogadores atuais
                        checkStartPartida();
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    throw new RuntimeException("Interrompido enquanto aguardava partida");
                }
            }
            
            waitingPlayers.remove(jogador);
            return jogador.getPartida();
        } finally {
            lock.unlock();
        }
    }
    
    private void checkStartPartida() {
        long currentTime = System.currentTimeMillis();
        boolean shouldStart = false;
        
        // Condição 1: Temos 6 jogadores
        if (waitingPlayers.size() >= 6) {
            shouldStart = true;
        }
        // Condição 2: Passaram 2 minutos e temos pelo menos 4 jogadores
        else if (firstPlayerArrivalTime != -1 && 
                 currentTime - firstPlayerArrivalTime >= TimeUnit.MINUTES.toMillis(2) && 
                 waitingPlayers.size() >= 4) {
            shouldStart = true;
        }
        
        if (shouldStart && !waitingPlayers.isEmpty()) {
            startNewPartida();
        }
    }
    
    private void startNewPartida() {
        PartidaImpl partida = new PartidaImpl(++partidaCounter);
        int playersToAssign = Math.min(waitingPlayers.size(), 6); // Máximo 6 jogadores
        
        // Assign first playersToAssign players to this partida
        List<Jogador> assigned = new ArrayList<>();
        for (int i = 0; i < playersToAssign; i++) {
            Jogador jogador = waitingPlayers.get(i);
            jogador.setPartida(partida);
            partida.addJogador(); // Registra jogador na partida
            assigned.add(jogador);
        }
        
        // Remove assigned players from the waiting list
        waitingPlayers.removeAll(assigned);
        
        partida.start();
        
        // If there are still players waiting, set a new arrival time to now
        if (!waitingPlayers.isEmpty()) {
            firstPlayerArrivalTime = System.currentTimeMillis();
        } else {
            firstPlayerArrivalTime = -1;
        }
        
        enoughPlayers.signalAll(); // Notifica todos os jogadores em espera
    }
}

class Jogador {
    private PartidaImpl partida;
    private boolean partidaStarted = false;
    private final Lock lock = new ReentrantLock();
    private final Condition partidaCondition = lock.newCondition();
    
    public void setPartida(PartidaImpl partida) {
        lock.lock();
        try {
            this.partida = partida;
            this.partidaStarted = true;
            partidaCondition.signalAll();
        } finally {
            lock.unlock();
        }
    }
    
    public boolean isPartidaStarted() {
        lock.lock();
        try {
            return partidaStarted;
        } finally {
            lock.unlock();
        }
    }
    
    public Partida getPartida() {
        lock.lock();
        try {
            while (!partidaStarted) {
                try {
                    partidaCondition.await();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    throw new RuntimeException("Interrompido enquanto aguardava partida");
                }
            }
            return partida;
        } finally {
            lock.unlock();
        }
    }
}

class PartidaImpl implements Partida {
    private final int id;
    private int numeroJogadores = 0;
    private final Lock lock = new ReentrantLock();
    private final Random random = new Random();
    
    private int numeroSecreto;
    private boolean jogoTerminado = false;
    private String resultadoVencedor = null;
    private int tentativasRestantes = 100;
    private long tempoInicio;
    private final long tempoLimite = TimeUnit.MINUTES.toMillis(1);
    private final ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);
    
    public PartidaImpl(int id) {
        this.id = id;
        this.numeroSecreto = random.nextInt(100) + 1;
    }
    
    public void start() {
        tempoInicio = System.currentTimeMillis();
        
        // Agenda verificação de timeout
        scheduler.schedule(() -> {
            lock.lock();
            try {
                if (!jogoTerminado && (System.currentTimeMillis() - tempoInicio) > tempoLimite) {
                    jogoTerminado = true;
                    resultadoVencedor = "TEMPO";
                }
            } finally {
                lock.unlock();
            }
        }, tempoLimite, TimeUnit.MILLISECONDS);
    }
    
    public void addJogador() {
        lock.lock();
        try {
            numeroJogadores++;
        } finally {
            lock.unlock();
        }
    }
    
    @Override
    public int numeroJogadores() {
        lock.lock();
        try {
            return numeroJogadores;
        } finally {
            lock.unlock();
        }
    }
    
    @Override
    public String adivinha(int n) {
        lock.lock();
        try {
            // Verifica se o jogo já terminou
            if (jogoTerminado) {
                if ("TEMPO".equals(resultadoVencedor)) return "TEMPO";
                if ("TENTATIVAS".equals(resultadoVencedor)) return "TENTATIVAS";
                if ("GANHOU".equals(resultadoVencedor)) return "PERDEU";
                return "PERDEU";
            }
            
            // Verifica timeout
            if ((System.currentTimeMillis() - tempoInicio) > tempoLimite) {
                jogoTerminado = true;
                resultadoVencedor = "TEMPO";
                return "TEMPO";
            }
            
            // Verifica tentativas
            if (tentativasRestantes <= 0) {
                jogoTerminado = true;
                resultadoVencedor = "TENTATIVAS";
                return "TENTATIVAS";
            }
            
            tentativasRestantes--;
            
            // Verifica palpite
            if (n == numeroSecreto) {
                jogoTerminado = true;
                resultadoVencedor = "GANHOU";
                return "GANHOU";
            } else if (n < numeroSecreto) {
                return "MENOR";
            } else {
                return "MAIOR";
            }
        } finally {
            lock.unlock();
        }
    }
    
    public void shutdown() {
        scheduler.shutdown();
    }
}

// Classe de teste (renomeada para corresponder ao nome do ficheiro exercicioJogo.java)
public class exercicioJogo {
    public static void main(String[] args) {
        Jogo jogo = new JogoImpl();
        
        // Teste com múltiplos jogadores
        for (int i = 0; i < 10; i++) {
            final int playerId = i;
            new Thread(() -> {
                try {
                    Partida partida = jogo.participa();
                    System.out.println("Jogador " + playerId + " entrou na partida com " + 
                                     partida.numeroJogadores() + " jogadores");
                    
                    // Faz algumas tentativas
                    Random rand = new Random();
                    for (int tentativa = 0; tentativa < 5; tentativa++) {
                        int palpite = rand.nextInt(100) + 1;
                        String resultado = partida.adivinha(palpite);
                        System.out.println("Jogador " + playerId + " palpite " + palpite + ": " + resultado);
                        
                        if (resultado.equals("GANHOU") || resultado.equals("PERDEU") || 
                            resultado.equals("TEMPO") || resultado.equals("TENTATIVAS")) {
                            break;
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }).start();
        }
    }
}
