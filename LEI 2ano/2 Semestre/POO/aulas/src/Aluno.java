import java.io.Serializable;

public abstract class Aluno implements Serializable {
    private String numero;
    private String nome;
    private String curso;
    private int nota;

    public String getNome() {
        return this.nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getCurso() {
        return this.curso;
    }

    public void setCurso(String curso) {
        this.curso = curso;
    }

    public int getNota() {
        return this.nota;
    }

    public void setNota(int nota) {
        this.nota = nota;
    }

    public String getNumero() {
        return this.numero;
    }

    public void setNumero(String numero) {
        this.numero = numero;
    }

    public Aluno() {
        this.numero = "";
        this.nome = "";
        this.curso = "";
        this.nota = 0;
    }

    public Aluno(String numero, String nome, String curso, int nota) {
        this.numero = numero;
        this.nome = nome;
        this.curso = curso;
        this.nota = nota;
    }

    public Aluno(Aluno aluno) {
        this.numero = aluno.getNumero();
        this.nome = aluno.getNome();
        this.curso = aluno.getCurso();
        this.nota = aluno.getNota();
    }

    public abstract Aluno clone();

    public abstract boolean equals(Object obj);

    public abstract String toString();

}
