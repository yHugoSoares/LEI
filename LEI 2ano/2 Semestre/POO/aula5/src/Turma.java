import java.util.TreeSet;
import java.util.Set;
import java.util.Objects;
import java.util.Map;
import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedHashSet;
import java.util.stream.*;

public class Turma {
    private String codigoUc;
    private String nome;
    private Map<String, Aluno> alunos;

    public void insereAluno(Aluno a) {
        this.alunos.put(a.getNome(), a.clone());
    }

    public Aluno getAluno(String numeroAluno) {
        if (!this.alunos.containsKey(numeroAluno)) {
            return null;
        }
        return this.alunos.get(numeroAluno).clone();
    }

    public void removeAluno(String numeroAluno) {
        this.alunos.remove(numeroAluno);
    }

    public Set<String> todosOsCodigos() {
        return this.alunos.keySet();
    }

    public int qtdAlunos() {
        return this.alunos.size();
    }

    public Collection<Aluno> alunosOrdemAlfabetica() {
        return this.alunos.values().stream().sorted((a1, a2)-> a1.getNome().compareTo(a2.getNome())).toList();
    }

    public Set<Aluno> alunosOrdemDecrescenteNumero() {
        return this.alunos.values().stream()
            .collect(Collectors.toCollection(() -> new TreeSet<>((a1, a2) -> Integer.compare(a2.getNumeroAluno(), a1.getNumeroAluno()))));
    }

    public Turma() {
        this.codigoUc = "";
        this.nome = "";
        this.alunos = new HashMap<>();
    }

    public Turma(String codigoUc, String nome, Map<String, Aluno> alunos) {
        this.codigoUc = codigoUc;
        this.nome = nome;
        this.alunos = alunos.entrySet().stream().collect(Collectors.toMap(e -> e.getKey(), e -> e.getValue().clone()));
    }

    // public Turma(Turma t) {
    //     this.codigoUc = t.getCodigoUc();
    //     this.nome = t.getNome();
    //     this.alunos = t.getAluno();
    // }

    public String getCodigoUc() {
        return this.codigoUc;
    }

    public void setCodigoUc(String codigoUc) {
        this.codigoUc = codigoUc;
    }

    public String getNome() {
        return this.nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }


}
