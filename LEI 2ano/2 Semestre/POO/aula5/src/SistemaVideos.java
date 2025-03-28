import java.util.ArrayList;
import java.util.List;

public class SistemaVideos {

    private List<VideoYoutube> videos = new ArrayList<>();

    public SistemaVideos() {
        // Constructor to initialize the list if needed
    }

    public void addVideo(VideoYoutube video) {
        this.videos.add(video);
    }

    public VideoYoutube getVideo(String codVideo) {
        for (VideoYoutube video : this.videos) {
            if (video.getCodigo().equals(codVideo)) {
                return video;
            }
        }
        return null;        
    }
}
