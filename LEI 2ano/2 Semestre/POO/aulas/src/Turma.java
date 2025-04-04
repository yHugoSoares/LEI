import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Turma implements Serializable {
    private List<Aluno> alunos;

    // Constructor
    public Turma() {
        this.alunos = new ArrayList<>();
    }

    public Turma(List<Aluno> alunos) {
        this.alunos = new ArrayList<>(alunos);
    }

    public Turma(Turma turma) {
        this.alunos = new ArrayList<>(turma.getAlunos());
    }

    // Getters and Setters
    public List<Aluno> getAlunos() {
        return new ArrayList<>(this.alunos);
    }

    public void setAlunos(List<Aluno> alunos) {
        this.alunos = new ArrayList<>(alunos);
    }

    // Add an Aluno to the Turma
    public void adicionarAluno(Aluno aluno) {
        this.alunos.add(aluno);
    }

    // Remove an Aluno by their number
    public void removerAluno(String numero) {
        this.alunos.removeIf(aluno -> aluno.getNumero().equals(numero));
    }

    // Find an Aluno by their number
    public Aluno procurarAluno(String numero) {
        for (Aluno aluno : this.alunos) {
            if (aluno.getNumero().equals(numero)) {
                return aluno;
            }
        }
        return null;
    }

    // Get the number of students in the Turma
    public int tamanho() {
        return this.alunos.size();
    }

    public Turma clone() {
        return new Turma(this);
    }

    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || this.getClass() != obj.getClass()) return false;

        Turma turma = (Turma) obj;
        return this.alunos.equals(turma.getAlunos());
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Turma:\n");
        for (Aluno aluno : this.alunos) {
            sb.append(aluno.toString()).append("\n");
        }
        return sb.toString();
    }
}
