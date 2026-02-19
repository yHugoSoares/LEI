import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

public class Turma {

    private List<Aluno> alunos;

    public Turma() {
        this.alunos = new ArrayList<>();
    }

    public Turma(List<Aluno> novosAlunos) {
        this.setAlunos(novosAlunos);
    }

    public Turma(Turma t) {
        this(t == null ? null : t.getAlunos());
    }

    public void setAlunos(List<Aluno> novosAlunos) {
        if (novosAlunos == null) {
            this.alunos = new ArrayList<>();
            return;
        }
        this.alunos = novosAlunos
            .stream()
            .filter(Objects::nonNull)
            .map(Aluno::clone)
            .collect(Collectors.toList());
    }

    public List<Aluno> getAlunos() {
        return alunos.stream().map(Aluno::clone).collect(Collectors.toList());
    }

    public Aluno getAluno(String numero) throws AlunoInexistenteException {
        return alunos
            .stream()
            .filter(x -> x.getNumero().equals(numero))
            .findFirst()
            .orElseThrow(() -> new AlunoInexistenteException())
            .clone();
    }

    public void addAluno(Aluno a) {
        if (a == null) return;
        if (!containsAluno(a.getNumero())) {
            alunos.add(a.clone());
        }
    }

    public boolean containsAluno(String numero) {
        return alunos.stream().anyMatch(x -> x.getNumero().equals(numero));
    }

    public void removeAluno(String numero) throws AlunoInexistenteException {
        Iterator<Aluno> it = alunos.iterator();
        boolean removido = false;
        while (it.hasNext() && !removido) {
            Aluno aluno = it.next();
            if (aluno.getNumero().equals(numero)) {
                it.remove();
                removido = true;
            }
        }
        if (!removido) throw new AlunoInexistenteException();
    }

    public double media() throws NotaInvalidaException {
        if (alunos.isEmpty()) return 0.0;
        double soma = 0.0;
        for (Aluno a : alunos) {
            soma += a.media();
        }
        double media = soma / alunos.size();
        if (media < 0.0 || media > 20.0) throw new NotaInvalidaException();
        return media;
    }

    public List<Aluno> reprovados() {
        List<Aluno> r = new ArrayList<>();
        for (Aluno a : alunos) {
            if (a.media() < 10.0) r.add(a.clone());
        }
        return r;
    }
}
