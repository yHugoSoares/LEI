import java.io.*;
import java.util.*;
import java.nio.*;
import java.nio.charset.*;
import java.nio.file.*;

public class Main {
    
    public static void guardaEmTexto(Object obj, String nomeFicheiro) throws FileNotFoundException {
        PrintWriter pw = new PrintWriter(nomeFicheiro);
        pw.println(obj.toString());
        pw.flush();
        pw.close();
    }

    public static List<String> lerFicheiro(String nomeFicheiro) {
        List<String> linhas = new ArrayList<>();
        try {
            linhas = Files.readAllLines(Paths.get(nomeFicheiro), StandardCharsets.UTF_8);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return linhas;
    }

    public static void guardaEmObjects(Object obj, String nomeFicheiro) throws IOException {
        FileOutputStream fos = new FileOutputStream(nomeFicheiro);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(obj);
        oos.flush();
        oos.close();
    }

    public static Object lerFicheiroObjects(String nomeficheiro) throws IOException, ClassNotFoundException {
        FileInputStream fis = new FileInputStream(nomeficheiro);
        ObjectInputStream ois = new ObjectInputStream(fis);
        Object obj = ois.readObject();
        ois.close();
        return obj;
    }

    public static void main(String[] args) {
        Aluno aluno1 = new Aluno("123", "João", "Engenharia", 18);
        Aluno aluno2 = new Aluno("456", "Maria", "Medicina", 20);
        Aluno aluno3 = new Aluno("789", "Pedro", "Direito", 15);
        AlunoTE alunoTE1 = new AlunoTE("101", "Ana", "Engenharia", 19, "Empresa A");

        Turma turma = new Turma("12345", "Turma A", Map.of(
            aluno1.getNumero(), aluno1,
            aluno2.getNumero(), aluno2,
            aluno3.getNumero(), aluno3,
            alunoTE1.getNumero(), alunoTE1));
        
        
    }
}
