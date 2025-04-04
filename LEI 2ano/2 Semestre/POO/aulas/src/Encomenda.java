import java.time.LocalDateTime;

public class Encomenda {
    private String Client;
    private int NIF;
    private String Address;
    private int OrderNumber;
    private LocalDateTime Date;
    private LinhaEncomenda[] Lines;

    // CONSTRUCTORS

    public Encomenda() {
        Client = "";
        NIF = 0;
        Address = "";
        OrderNumber = 0;
        Date = LocalDateTime.now();
        Lines = new LinhaEncomenda[0];
    }

    public Encomenda(String client, int nif, String address, int orderNumber, LocalDateTime date, LinhaEncomenda[] lines) {
        Client = client;
        NIF = nif;
        Address = address;
        OrderNumber = orderNumber;
        Date = date;
        Lines = lines;
    }

    public Encomenda(Encomenda e) {
        Client = e.getClient();
        NIF = e.getNIF();
        Address = e.getAddress();
        OrderNumber = e.getOrderNumber();
        Date = e.getDate();
        Lines = e.getLines();
    }

    // GRABBERS & SETTERS

    public String getClient() {
        return Client;
    }

    public int getNIF() {
        return NIF;
    }

    public String getAddress() {
        return Address;
    }

    public int getOrderNumber() {
        return OrderNumber;
    }

    public LocalDateTime getDate() {
        return Date;
    }

    public LinhaEncomenda[] getLines() {
        return Lines;
    }

    public void setClient(String client) {
        Client = client;
    }

    public void setNIF(int nif) {
        NIF = nif;
    }

    public void setAddress(String address) {
        Address = address;
    }

    public void setOrderNumber(int orderNumber) {
        OrderNumber = orderNumber;
    }

    public void setDate(LocalDateTime date) {
        Date = date;
    }

    public void setLines(LinhaEncomenda[] lines) {
        Lines = lines;
    }

    public double calculaValorTotal() {
        double total = 0;
        for (LinhaEncomenda l : Lines) {
            total += l.calculaValorLinhaEnc();
        }
        return total;
    }

    public double calculaValorDesconto() {
        double total = 0;
        for (LinhaEncomenda l : Lines) {
            total += l.calculaValorDesconto();
        }
        return total;
    }

    public int numeroTotalProdutos() {
        int total = 0;
        for (LinhaEncomenda l : Lines) {
            total += l.getQuantity();
        }
        return total;
    }

    public boolean existeProdutoEncomenda(String refProduto) {
        for (LinhaEncomenda l : Lines) {
            if (l.getReference().equals(refProduto)) {
                return true;
            }
        }
        return false;
    }

    public void adicionaLinha(LinhaEncomenda l) {
        LinhaEncomenda[] newLines = new LinhaEncomenda[Lines.length + 1];
        for (int i = 0; i < Lines.length; i++) {
            newLines[i] = Lines[i];
        }
        newLines[Lines.length] = l;
        Lines = newLines;
    }
    
    public void removeProduto(String codProd) {
        LinhaEncomenda[] newLines = new LinhaEncomenda[Lines.length - 1];
        int j = 0;
        for (int i = 0; i < Lines.length; i++) {
            if (!Lines[i].getReference().equals(codProd)) {
                newLines[j] = Lines[i];
                j++;
            }
        }
        Lines = newLines;
    }

}
