public class LinhaEncomenda {
    private String reference;
    private String description;
    private double price;
    private int quantity;
    private double tax;
    private double discount;

    // CONSTRUCTORS

    public LinhaEncomenda() {
        reference = "";
        description = "";
        price = 0;
        quantity = 0;
        tax = 0;
        discount = 0;
    }

    public LinhaEncomenda(String reference, String description, double price, int quantity, double tax, double discount) {
        this.reference = reference;
        this.description = description;
        this.price = price;
        this.quantity = quantity;
        this.tax = tax;
        this.discount = discount;
    }

    public LinhaEncomenda(LinhaEncomenda p) {
        reference = p.getReference();
        description = p.getDescription();
        price = p.getPrice();
        quantity = p.getQuantity();
        tax = p.getTax();
        discount = p.getDiscount();
    }

    // GRABBERS & SETTERS

    public String getReference() {
        return reference;
    }

    public String getDescription() {
        return description;
    }

    public double getPrice() {
        return price;
    }

    public int getQuantity() {
        return quantity;
    }

    public double getTax() {
        return tax;
    }

    public double getDiscount() {
        return discount;
    }

    public void setReference(String reference) {
        this.reference = reference;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public void setTax(double tax) {
        this.tax = tax;
    }

    public void setDiscount(double discount) {
        this.discount = discount;
    }

    // EQUALS
    public boolean equals(LinhaEncomenda p) {
        return reference.equals(p.getReference()) && description.equals(p.getDescription()) 
        && price == p.getPrice() && quantity == p.getQuantity() 
        && tax == p.getTax() && discount == p.getDiscount();
    }

    // REPRESENTATION
    public String toString() {
        return "Referencia: " + reference + "\nDescricao: " + description + "\nPreco: " + price + "\nQuantidade: " + quantity + "\nImposto: " + tax + "\nDesconto: " + discount;
    }

    // CLONE
    public LinhaEncomenda clone() {
        return new LinhaEncomenda(this);
    }

    // METHODS
    public double calculaValorLinhaEnc() {
        return  (price * (1 + tax) - (price * discount)) * quantity;
    }

    public double calculaValorDesconto() {
        return price * quantity * discount;
    }

    public double calculaValorIVA() {
        return price * quantity * tax;
    }
}
