import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class Aluno {

    private String nome;
    private String numero;
    private Map<String, Double> notas = new HashMap<String, Double>();

    public Aluno() {
    }

    public Aluno(String nome, String numero) {
        this.nome = nome;
        this.numero = numero;
    }

    /**
     * Copy constructor — performs a deep-ish copy of the notas map so cloned
     * students preserve their grades and do not share mutable state.
     */
    public Aluno(Aluno outro) {
        this.nome = outro.nome;
        this.numero = outro.numero;
        this.notas = new HashMap<String, Double>(outro.notas);
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getNumero() {
        return numero;
    }

    public void setNumero(String numero) {
        this.numero = numero;
    }

    /**
     * Returns the arithmetic mean of the student's grades.
     * If there are no grades, returns 0.0 to avoid NaN results.
     */
    public double media() {
        if (notas.isEmpty())
            return 0.0;
        double soma = 0.0;
        for (double nota : notas.values()) {
            soma += nota;
        }
        return soma / notas.size();
    }

    /**
     * Returns the grade for the given discipline.
     * If there is no grade recorded for the discipline, returns 0.0.
     */
    public double getNota(String disciplina) {
        Double v = notas.get(disciplina);
        return v == null ? 0.0 : v;
    }

    public void setNota(String disciplina, double nota)
            throws NotaInvalidaException {
        if (nota >= 0 && nota <= 20) {
            notas.put(disciplina, nota);
        } else {
            throw new NotaInvalidaException();
        }
    }

    public double incrementaNota(String disciplina, double incremento)
            throws NotaInvalidaException {
        Double atual = notas.get(disciplina);
        if (atual == null) {
            // If there's no existing grade, treat as adding incremento to 0.0
            atual = 0.0;
        }
        double novaNota = atual + incremento;
        if (novaNota < 0 || novaNota > 20)
            throw new NotaInvalidaException();
        notas.put(disciplina, novaNota);
        return novaNota;
    }

    @Override
    public String toString() {
        return "Aluno{" + "nome='" + nome + '\'' + ", numero=" + numero + '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;
        Aluno aluno = (Aluno) o;
        return Objects.equals(numero, aluno.numero);
    }

    @Override
    public Aluno clone() {
        return new Aluno(this);
    }
}
