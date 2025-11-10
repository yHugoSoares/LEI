import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;

class ContactManager {
    private HashMap<String, Contact> contacts = new HashMap<>();

    // @TODO
    public void update(Contact c) {
        contacts.put(c.name(), c);
    }

    // @TODO
    public ContactList getContacts() {
        ContactList list = new ContactList();
        for (Contact c : contacts.values()) {
            list.add(c);
        }
        return list;
    }
}

class ServerWorker implements Runnable {
    private Socket socket;
    private ContactManager manager;

    public ServerWorker(Socket socket, ContactManager manager) {
        this.socket = socket;
        this.manager = manager;
    }

    // @TODO
    @Override
    public void run() {
        try (DataInputStream in = new DataInputStream(socket.getInputStream());
             DataOutputStream out = new DataOutputStream(socket.getOutputStream())) {

            String clientAddr = socket.getRemoteSocketAddress().toString();
            String command = in.readUTF();
            System.out.println("[Server] Received command from " + clientAddr + ": " + command);

            if (command.equals("UPDATE")) {
                Contact contact = Contact.deserialize(in);
                System.out.println("[Server] Received contact from " + clientAddr + ": " + contact);
                manager.update(contact);
                out.writeUTF("OK");
            } else if (command.equals("GET")) {
                ContactList contacts = manager.getContacts();
                System.out.println("[Server] Sending contact list to " + clientAddr + ", size=" + contacts.size());
                contacts.serialize(out);
            } else {
                out.writeUTF("ERROR: Unknown command");
            }
        } catch (java.io.EOFException eof) {
            // client closed connection unexpectedly; log and exit quietly
            System.out.println("[Server] Client " + socket.getRemoteSocketAddress() + " closed connection (EOF)");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


public class Server {

    public static void main (String[] args) throws IOException {
        int port = 12345;
        ContactManager manager = new ContactManager();

        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Server listening on port " + port);
            while (true) {
                Socket socket = serverSocket.accept();
                Thread worker = new Thread(new ServerWorker(socket, manager));
                worker.start();
            }
        }
    }

}
