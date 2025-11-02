class Node<T> {
    public T value;
    public Node<T> next;

    public Node(T value){
        this.value = value;
        this.next = null;
    }

    public Node(){
        this.value = null;
        this.next = null;
    }
}

public class Stack<T> {
    public Node<T> head;

    public Stack(Node<T> node){
        this.head = node;
    }
    
    public Stack(){
        this.head = new Node<T>();
    }

    public void push(T value){
        Node<T> node = new Node<T>(value);
        if (head == null)
            head = node;
        else {
            var temp = head;
            head.next = temp;
            head = node;
        }
    }

    public T pop(){
        if (head == null){
            throw new NullPointerException("The stack is empty");
        }
        else {
            var node = head;
            head = head.next;
            return node.value;
        }
    }
}
