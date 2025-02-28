public class Musica {
    private String Nome;
    private String Interprete;
    private String Autor;
    private String[] Letra;
    private String[] MusicaCaracteres;
    private int Duracao;
    private int VezesOuvidas;


    public Musica() {
        Nome = "";
        Interprete = "";
        Autor = "";
        Letra = new String[0];
        MusicaCaracteres = new String[0];
        Duracao = 0;
        VezesOuvidas = 0;
    }

    public Musica(String nome, String interprete, String autor, String[] letra, String[] musicaCaracteres, int duracao, int vezesOuvidas) {
        Nome = nome;
        Interprete = interprete;
        Autor = autor;
        Letra = letra;
        MusicaCaracteres = musicaCaracteres;
        Duracao = duracao;
        VezesOuvidas = vezesOuvidas;
    }

    public Musica(Musica m) {
        Nome = m.getNome();
        Interprete = m.getInterprete();
        Autor = m.getAutor();
        Letra = m.getLetra();
        MusicaCaracteres = m.getMusicaCaracteres();
        Duracao = m.getDuracao();
        VezesOuvidas = m.getVezesOuvidas();
    }
    
    // GRABBERS & SETTERS

    public String getNome() {
        return Nome;
    }

    public String getInterprete() {
        return Interprete;
    }

    public String getAutor() {
        return Autor;
    }

    public String[] getLetra() {
        return Letra;
    }

    public String[] getMusicaCaracteres() {
        return MusicaCaracteres;
    }

    public int getDuracao() {
        return Duracao;
    }

    public int getVezesOuvidas() {
        return VezesOuvidas;
    }

    public void setNome(String nome) {
        Nome = nome;
    }

    public void setInterprete(String interprete) {
        Interprete = interprete;
    }

    public void setAutor(String autor) {
        Autor = autor;
    }

    public void setLetra(String[] letra) {
        Letra = letra;
    }

    public void setMusicaCaracteres(String[] musicaCaracteres) {
        MusicaCaracteres = musicaCaracteres;
    }

    public void setDuracao(int duracao) {
        Duracao = duracao;
    }

    public void setVezesOuvidas(int vezesOuvidas) {
        VezesOuvidas = vezesOuvidas;
    }



}
//    UML 
// ---------------------------------
// |            Musica             |
// ---------------------------------
// | - Nome: String                |
// | - Interprete: String          |
// | - Autor: String               |
// | - Letra: String[]             |
// | - MusicaCaracteres: String[]  |
// | - Duracao: int                |
// | - VezesOuvidas: int           |
// ---------------------------------
// | + Musica()                    |
// | + Musica(nome: String,        |
// |   interprete: String,         |
// |   autor: String,              |
// |   letra: String[],            |
// |   musicaCaracteres: String[], |
// |   duracao: int,               |
// |   vezesOuvidas: int)          |
// | + Musica(m: Musica)           |
// | + getNome(): String           |
// | + getInterprete(): String     |
// | + getAutor(): String          |
// | + getLetra(): String[]        |
// | + getMusicaCaracteres():      |
// |   String[]                    |
// | + getDuracao(): int           |
// | + getVezesOuvidas(): int      |
// | + setNome(nome: String)       |
// | + setInterprete(interprete:   |
// |   String)                     |
// | + setAutor(autor: String)     |
// | + setMusicaCaracteres(        |
// |   musicaCaracteres: String[]) |
// | + setDuracao(duracao: int)    |
// | + setVezesOuvidas(vezesOuvidas:|
// |   int)                        |
// | + uml()                       |
// ---------------------------------
