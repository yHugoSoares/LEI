/*********************************************************************************/
/** DISCLAIMER: Este código foi criado e alterado durante as aulas práticas      */
/** de POO. Representa uma solução em construção, com base na matéria leccionada */
/** até ao momento da sua elaboração, e resulta da discussão e experimentação    */
/** durante as aulas. Como tal, não deverá ser visto como uma solução canónica,  */
/** ou mesmo acabada. É disponibilizado para auxiliar o processo de estudo.      */
/** Os alunos são encorajados a testar adequadamente o código fornecido e a      */
/** procurar soluções alternativas, à medida que forem adquirindo mais           */
/** conhecimentos de POO.                                                        */
/*********************************************************************************/

/**
 * Classe que implementa uma Lâmpada cf exercício da Ficha 3.
 * Esta classe foi desenvolvida durante as aulas práticas pelo que algumas das
 * linhas de código decorrem de decisões tomadas na altura. Existe naturalmente
 * espaço para melhorar e alterar este código.
 *
 * ATENÇÃO: a classe Lampada utiliza um enum para guardar os diferentes tipos
 * de consumo. Poderia também ser feito com constantes.

 *
 * @author  MaterialPOO
 * @version 20220321
 * @version 20230320
 * @version 20250316
 */
 
public class Lampada
{
    private ModoLampada modo;

    /* consumo por segundo em Modo.ON */
    private double cpSOn;  
    /* consumo por segundo em Modo.OFF */
    private double cpSEco;
    private double consumoTotal;
    private double consumoPeriodo;
    /*  */
    private long stamp;

    public Lampada() {
        this.modo = ModoLampada.OFF;
        this.cpSEco = 1;
        this.cpSOn = 2;
        this.consumoTotal = 0;
        this.consumoPeriodo = 0;
        this.stamp = System.currentTimeMillis();
    }

    public Lampada(Lampada l) {
        this.modo = l.getModo();
        this.cpSEco = l.getCpSEco();
        this.cpSOn = l.getCpSOn();
        this.consumoTotal = l.totalConsumo();
        this.consumoPeriodo = l.periodoConsumo();
        this.stamp = l.getStamp();
    }

    public Lampada(ModoLampada x, double cpsE, double cpsO, double cT, double pC) {
        this.modo = x;
        this.cpSEco = cpsE;
        this.cpSOn = cpsO;
        this.consumoTotal = cT;
        this.consumoPeriodo = pC;
        this.stamp = System.currentTimeMillis();
    }

    public ModoLampada getModo() {
        return modo;
    }

    public void setModo(ModoLampada m) {
        this.modo = m;
    }

    public long getStamp() {
        return stamp;
    }

    public double getCpSEco(){
        return this.cpSEco;
    }

    public void setCpSEco(double x){
        this.cpSEco = x;
    }

    public double getCpSOn(){
        return this.cpSOn;
    }

    public void setCpSOn(double x){
        this.cpSOn = x;
    }

    public double getConsumoTotal() {
        return consumoTotal;
    }

    public void setConsumoTotal(double cT){
        this.consumoTotal = cT;
    }

    public double getConsumoPeriodo() {
        return consumoPeriodo;
    }

    public void setConsumoPeriodo(double pC){
        this.consumoPeriodo = pC;
    }

    public void lampON() {
        this.atualizaConsumo();
        this.modo = ModoLampada.ON;
    }

    public void lampOFF() {
        this.atualizaConsumo();
        this.modo = ModoLampada.OFF;
    }

    public void lampECO() {
        this.atualizaConsumo();
        this.modo = ModoLampada.ECO;
    }

    public void resetPeriodo(){
        atualizaConsumo();
        this.consumoPeriodo = 0;
    }

    public double periodoConsumo(){
        atualizaConsumo();
        return consumoPeriodo;
    }
    public double totalConsumo() {
        atualizaConsumo();
        return consumoTotal;
    }

    private void atualizaConsumo() {
        long periodo = System.currentTimeMillis() - stamp;

        if(this.modo == ModoLampada.ON) {
            this.consumoTotal += cpSOn *periodo;
            this.consumoPeriodo += cpSOn *periodo;
        } else if(this.modo == ModoLampada.ECO) {
            this.consumoTotal += cpSEco *periodo;
            this.consumoPeriodo += cpSEco *periodo;
        }

        this.stamp = System.currentTimeMillis();
    }

    public Lampada clone(){
        return new Lampada(this);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Lampada: ").append(this.modo)
                .append("\nConsumo por segundo Eco: ").append(this.cpSEco)
                .append("\nConsumo por segundo On: ").append(this.cpSOn)
                .append("\nConsumoTotal: ").append(this.consumoTotal)
                .append("\nInicio de ultimo consumo: ").append(this.consumoPeriodo);
        return sb.toString();
    }

    public boolean equals(Object o){
        if (this==o) return true;
        if ((o == null) || (this.getClass() != o.getClass())) return false;

        Lampada l = (Lampada) o;
        return l.getModo() == this.modo &&
                l.getCpSOn() == this.cpSOn &&
                l.getCpSEco() == this.cpSEco &&
                l.getConsumoTotal() == this.consumoTotal &&
                l.getConsumoPeriodo() == this.consumoPeriodo &&
                l.getStamp() == this.stamp;
    }
}
