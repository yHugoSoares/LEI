public class VideoYoutube {
    String codVideo;
    String titulo;
    String descricao;
    String url;
    String autor;
    int visualizacoes;
    int likes;

    VideoYoutube() {
        this.codVideo = "";
        this.titulo = "";
        this.descricao = "";
        this.url = "";
        this.autor = "";
        this.visualizacoes = 0;
        this.likes = 0;
    }

    VideoYoutube(String codVideo, String titulo, String descricao, String url, String autor) {
        this.codVideo = codVideo;
        this.titulo = titulo;
        this.descricao = descricao;
        this.url = url;
        this.autor = autor;
        this.visualizacoes = 0;
        this.likes = 0;
    }

    VideoYoutube(VideoYoutube v) {
        this.codVideo = v.codVideo;
        this.titulo = v.titulo;
        this.descricao = v.descricao;
        this.url = v.url;
        this.autor = v.autor;
        this.visualizacoes = v.visualizacoes;
        this.likes = v.likes;
    }

    public String getCodigo() {
        return this.codVideo;
    }

    public String getTitulo() {
        return this.titulo;
    }
    
    public String getDescricao() {
        return this.descricao;
    }

    public String getUrl() {
        return this.url;
    }

    public String getAutor() {
        return this.autor;
    }

    public int getVisualizacoes() {
        return this.visualizacoes;
    }

    public int getLikes() {
        return this.likes;
    }

    public void setCodigo(String codVideo) {
        this.codVideo = codVideo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public void setDescricao(String descricao) {
        this.descricao = descricao;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public void setAutor(String autor) {
        this.autor = autor;
    }

    public void setVisualizacoes(int visualizacoes) {
        this.visualizacoes = visualizacoes;
    }

    public void setLikes(int likes) {
        this.likes = likes;
    }

    public void addVisualizacao() {
        this.visualizacoes++;
    }

    public void addLike() {
        this.likes++;
    }

    public VideoYoutube clone() {
        return new VideoYoutube(this);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof VideoYoutube)) return false;
        VideoYoutube that = (VideoYoutube) o;
        return codVideo.equals(that.codVideo);
    }

    // Override hashCode to ensure that two VideoYoutube objects with the same codVideo have the same hash code
    @Override
    public int hashCode() {
        return codVideo.hashCode();
    }

    public String toStringFull() {
        return "VideoYoutube{" +
                "codVideo='" + codVideo + '\'' +
                ", titulo='" + titulo + '\'' +
                ", descricao='" + descricao + '\'' +
                ", url='" + url + '\'' +
                ", autor='" + autor + '\'' +
                ", visualizacoes=" + visualizacoes +
                ", likes=" + likes +
                '}';
    }
    public String toStringShort() {
        return "VideoYoutube{" +
                "codVideo='" + codVideo + '\'' +
                ", titulo='" + titulo + '\'' +
                ", autor='" + autor + '\'' +
                '}';
    }


}