public class AlunoInexistenteException extends Exception {

    public AlunoInexistenteException(String message) {
        super(message);
    }

    public AlunoInexistenteException() {
        super("Aluno inexistente");
    }
}
