package utils;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import models.MusicTypes.*;

public class CSVImporter {

    public static List<Music> importMusicFromCSV(String filePath) {
        List<Music> musicList = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line = br.readLine(); // Skip the header line
            while ((line = br.readLine()) != null) {
                String[] fields = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)"); // Split by commas, ignoring commas inside quotes

                String tipo = fields[0].replace("\"", "").trim();
                String nome = fields[1].replace("\"", "").trim();
                String autor = fields[2].replace("\"", "").trim();
                String editora = fields[3].replace("\"", "").trim();
                String letra = fields[4].replace("\"", "").trim();
                String[] notasMusicais = fields[5].replace("\"", "").split("\\s*,\\s*");
                String genero = fields[6].replace("\"", "").trim();

                int duracao;
                try {
                    duracao = Integer.parseInt(fields[7].replace("\"", "").trim());
                } catch (NumberFormatException e) {
                    duracao = 0; // Default to 0 if parsing fails
                    System.err.println("Invalid duration value for music: " + nome + ". Defaulting to 0.");
                }

                int reproducoes = fields[8].isEmpty() ? 0 : Integer.parseInt(fields[8].replace("\"", "").trim());
                String multimedia = fields[9].replace("\"", "").trim();
                int explicito = fields[10].isEmpty() ? 0 : Integer.parseInt(fields[10].replace("\"", "").trim());

                Music music;
                switch (tipo) {
                    case "Multimedia":
                        music = new Multimedia(nome, autor, editora, letra, notasMusicais, genero, duracao, multimedia);
                        break;
                    case "Explicit":
                        music = new Explicit(nome, autor, editora, letra, notasMusicais, genero, duracao, explicito);
                        break;
                    case "ExplicitMultimedia":
                        music = new ExplicitMultimedia(nome, autor, editora, letra, notasMusicais, genero, duracao, explicito, multimedia);
                        break;
                    default:
                        music = new BaseMusic(nome, autor, editora, letra, notasMusicais, genero, duracao);
                        break;
                }

                for (int i = 0; i < reproducoes; i++) {
                    music.reproduzir(); // Simulate reproductions
                }

                musicList.add(music);
            }
        } catch (IOException | NumberFormatException e) {
            System.err.println("Error reading CSV file: " + e.getMessage());
        }

        return musicList;
    }
}
