import java.util.Scanner;

public class Main
{
    static Scanner in = new Scanner(System.in);

public static void main(String[] args) {
    int n = in.nextInt();
    Node root = new Node();
    for (int op = 0; op < n; ++op) {
        String opStr = in.next();
        int num = in.nextInt();
        if (opStr.equals("I")) {
            //int val = in.nextInt();
            Insert(root, num);
        } else if (opStr.equals("D")) {
        } else if (opStr.equals("M")) {
        } else {
            //int maxN = in.nextInt();
            System.out.println(Query(root, num));
        }
    }
}

static int Query(Node node, int k) {
    if (node.left.val == k - 1)
        return node.data;
    if (node.left.val < k - 1)
        return Query(node.right, (int) (k - node.left.val - 1));
    else
        return Query(node.left, k);
}

static void Insert(Node node, int data)
{
    if (node.inserted) {
        node.val++;
        if (data > node.data)
            Insert(node.right, data);
        else
            Insert(node.left, data);
    } else {
        node.data = data;
        node.inserted = true;
        node.val = 1;
        node.left = new Node();
        node.right = new Node();
    }
}
}

class Node
{
    public boolean inserted;
    public int data;
    public long val;
    public Node parent;
    public Node left;
    public Node right;
}
