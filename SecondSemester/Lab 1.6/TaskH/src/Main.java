import java.util.Scanner;

public class Main {

    static Node[] arr = new Node[100001];

    static class Node {
        Node left;
        Node right;
        Node parent;
        boolean rev;
        int size = 1;

        boolean root(Node now) {
            return ((parent == null) || (parent.left != now && parent.right != now));
        }

        void update() {
            if (rev) {
                rev = false;
                Node now = left;
                left = right;
                right = now;
                if (left != null) {
                    left.rev = !left.rev;
                }
                if (right != null) {
                    right.rev = !right.rev;
                }
            }
        }
    }

    static void relations(Node kid, Node parent, Boolean typeOfChild) {
        if (kid != null) {
            kid.parent = parent;
        }
        if (typeOfChild == null) {
            return;
        }
        if (typeOfChild) {
            parent.left = kid;

        } else {
            parent.right = kid;
        }
    }

    static void twists(Node node) {
        Node parent = node.parent;
        Node grandpa = parent.parent;
        boolean isRoot = parent.root(parent);
        boolean isLeft = (node == parent.left);
        relations((isLeft ? node.right : node.left), parent, isLeft);
        relations(parent, node, !isLeft);
        relations(node, grandpa, !isRoot ? parent == grandpa.left : null);
        if (grandpa != null) {
            grandpa.size = 1 + (grandpa.left == null ? 0 : grandpa.left.size) + (grandpa.right == null ? 0 : grandpa.right.size);
            System.out.println(grandpa.size);
        }
        parent.size = 1 + (parent.left == null ? 0 : parent.left.size) + (parent.right == null ? 0 : parent.right.size);
        //System.out.println(parent.size);
        node.size = 1 + (node.left == null ? 0 : node.left.size) + (node.right == null ? 0 : node.right.size);
        //System.out.println(node.size);
    }

    static void splay(Node now) {
        while (!now.root(now)) {
            Node parent = now.parent;
            Node grand = parent.parent;
            if (!parent.root(parent)) {
                grand.update();
            }
            parent.update();
            now.update();
            if (!parent.root(parent)) {
                twists((now == parent.left) == (parent == grand.left) ? parent : now);
            }
            twists(now);
        }
        now.update();
    }

    static Node expose(Node now) {
        Node recent = null;
        for (Node i = now; i != null; i = i.parent) {
            splay(i);
            i.left = recent;
            recent = i;
        }
        splay(now);
        return recent;
    }

    static void reverse(Node now) {
        expose(now);
        now.rev = !now.rev;
    }

    static boolean connected(Node now1, Node now2) {
        if (now1 == now2) {
            return true;
        }
        expose(now1);
        expose(now2);
        return now1.parent != null;
    }

    static void cut(Node now1, Node now2) {
        reverse(now1);
        expose(now2);
        now2.right.parent = null;
        now2.right = null;
    }

    static void link(Node now1, Node now2) {
        reverse(now1);
        now1.parent = now2;
    }

    public static void main(String[] args) {
        int n, m;
        Scanner cin = new Scanner(System.in);
        n = cin.nextInt();
        m = cin.nextInt();
        for (int i = 0; i <= n; i++) {
            arr[i] = new Node();
        }
        String type;
        int now1, now2;
        for (int i = 0; i < m; i++) {
            type = cin.next();
            now1 = cin.nextInt();
            now2 = cin.nextInt();
            if (type.equals("cut")) {
                cut(arr[now1], arr[now2]);
            } else if (type.equals("link")) {
                link(arr[now1], arr[now2]);
            } else {
                System.out.println(expose(arr[now1]).size);
            }
        }
    }
}