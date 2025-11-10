import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.ArrayList;

class ContactList extends ArrayList<Contact> {

    // @TODO
    public void serialize(DataOutputStream out) throws IOException {
        out.writeInt(this.size());
        for (Contact contact : this) {
            contact.serialize(out);
        }
    }

    // @TODO
    public static ContactList deserialize(DataInputStream in) throws IOException {
        ContactList contactList = new ContactList();
        int size = in.readInt();
        for (int i = 0; i < size; i++) {
            Contact contact = Contact.deserialize(in);
            contactList.add(contact);
        }
        return contactList;
    }

}
