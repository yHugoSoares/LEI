public class AlunoTE extends Aluno {
    private String empresa;

    public String getEmpresa() {
        return this.empresa;
    }

    public void setEmpresa(String empresa) {
        this.empresa = empresa;
    }

    @Override
    public AlunoTE clone() {
        return new AlunoTE(this);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null || this.getClass() != obj.getClass()) {
            return false;
        }

        AlunoTE alunoTE = (AlunoTE) obj;
        return super.equals(alunoTE) && this.empresa.equals(alunoTE.empresa);
    }

    @Override
    public String toString() {
        StringBuffer sb = new StringBuffer();
        
        sb.append(this.empresa);

        return sb.toString();
    }

    public AlunoTE() {
        super();
        this.empresa = "";
    }

    public AlunoTE(String numero, String nome, String curso, int nota, String empresa) {
        super(numero, nome, curso, nota);
        this.empresa = empresa;
    }

    public AlunoTE(AlunoTE alunoTE) {
        super(alunoTE);
        this.empresa = alunoTE.empresa;
    }
    
}
