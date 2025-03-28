public class Aluno implements Comparable<Aluno> {
    private String nome;
    private int numeroAluno;
    private String curso;


    // Constructor
    public Aluno() {
        this.nome = "";
        this.numeroAluno = 0;
        this.curso = "";
    }

    public Aluno(String nome, int numero, String curso) {
        this.nome = nome;
        this.numeroAluno = numero;
        this.curso = curso;
    }
    
    public Aluno(Aluno a) {
        this.nome = a.getNome();
        this.numeroAluno = a.getNumeroAluno();
        this.curso = a.getCurso();
    }
    
    // Getters and Setters
    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public int getNumeroAluno() {
        return numeroAluno;
    }

    public void setNumeroAluno(int numero) {
        this.numeroAluno = numero;
    }

    public String getCurso() {
        return curso;
    }

    public void setCurso(String curso) {
        this.curso = curso;
    }

    // toString method
    @Override
    public String toString() {
        return "Aluno{" +
                "nome='" + nome + '\'' +
                ", numero=" + numeroAluno +
                ", curso='" + curso + '\'' +
                '}';
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) return false;
        Aluno a = (Aluno) o;
        return this.nome.equals(a.getNome()) && this.numeroAluno == a.getNumeroAluno() && this.curso.equals(a.getCurso());
    }

    public Aluno clone() {
        return new Aluno(this);
    }

    @Override
    public int compareTo(Aluno a) {
        return Integer.compare(this.numeroAluno, a.getNumeroAluno()); // Error: int is a primitive type
    }
}
