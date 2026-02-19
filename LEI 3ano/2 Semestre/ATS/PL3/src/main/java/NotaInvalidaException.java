public class NotaInvalidaException extends Exception {

    public NotaInvalidaException(String message) {
        super(message);
    }

    public NotaInvalidaException() {
        super("Nota inválida");
    }
}
