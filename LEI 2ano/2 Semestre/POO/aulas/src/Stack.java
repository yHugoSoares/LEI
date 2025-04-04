import java.util.ArrayList;

public class Stack {
    private ArrayList<String> stack;

    // CONSTRUCTORS

    public Stack() {
        stack = new ArrayList<>();
    }

    public Stack(int size) {
        stack = new ArrayList<>(size);
    }

    public Stack(Stack s) {
        stack = s.getStack();
    }

    // GRABBERS & SETTERS
    public ArrayList<String> getStack() {
        return stack;
    }

    public void setStack(ArrayList<String> stack) {
        this.stack = stack;
    }

    // METHODS
    public String toString() {
        return stack.toString();
    }

    public String top() {
        return stack.get(stack.size() - 1);
    }

    public void push(String s) {
        stack.add(s);
    }

    public void pop() {
        stack.remove(stack.size() - 1);
    }

    public boolean empty() {
        return stack.isEmpty();
    }

    public int length() {
        return stack.size();
    }
}
