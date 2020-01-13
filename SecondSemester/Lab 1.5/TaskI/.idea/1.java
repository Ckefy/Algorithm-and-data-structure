import java.io.*;
import java.util.Random;
import java.util.StringTokenizer;

public class I {
    static Random random = new Random();

    static class FastScanner {
        BufferedReader input;
        StringTokenizer readString;

        FastScanner() {
            input = new BufferedReader(new InputStreamReader(System.in));
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        String next() {
            while (readString == null || !readString.hasMoreElements()) {
                try {
                    readString = new StringTokenizer(input.readLine());
                } catch (IOException e) {
                    System.out.println("Really sorry for my Task H, it was awful");
                }
            }
            return readString.nextToken();
        }
    }

    static class Node {
        int value;
        int y;
        int sum;
        Node l;
        Node r;
        Node parent;
        boolean isCycle;
        boolean isTransposed;

        Node(int value) {
            this.value = value;
            this.y = random.nextInt();
            this.sum = 1;
        }
    }

    static class Pair {
        Node first;
        Node second;

        Pair(Node l, Node r) {
            first = l;
            second = r;
        }
    }

    public static void main(String[] args) {
        FastScanner scanner = new FastScanner();
        int n = scanner.nextInt(), m = scanner.nextInt(), q = scanner.nextInt();
        Node[] map = new Node[n];
        for (int i = 1; i <= n; i++) {
            map[i - 1] = new Node(i);
        }
        int firstTown, secondTown;
        for (int i = 0; i < m; i++) {
            firstTown = scanner.nextInt();
            secondTown = scanner.nextInt();
            build(map[firstTown - 1], map[secondTown - 1]);
        }
        for (int i = 0; i < q; i++) {
            String c = scanner.next();
            firstTown = scanner.nextInt();
            secondTown = scanner.nextInt();
            firstTown--;
            secondTown--;
            if (c.equals("+")) {
                build(map[firstTown], map[secondTown]);
            } else if (c.equals("-")) {
                if (firstTown != secondTown)
                    remove(map[firstTown], map[secondTown]);
            } else {
                System.out.println(firstTown == secondTown ? 0 : getAnswer(map[firstTown], map[secondTown]));
            }
        }
    }

    static Node getRoot(Node now) {
        return now.parent == null ? now : getRoot(now.parent);
    }

    static void transpose(Node now) {
        //as we swapped our kids, we`re now with true flag in time our kids with false one
        if (!(now == null || !now.isTransposed)) {
            Node dynamic = now.l;
            now.l = now.r;
            now.r = dynamic;
            now.isTransposed = false;
            if (now.l != null) {
                now.l.isTransposed = !now.l.isTransposed;
            }
            if (now.r != null) {
                now.r.isTransposed = !now.r.isTransposed;
            }
            recalc(now);
        }
    }

    static void recalc(Node now) {
        if (now != null) {
            now.sum = 0;
            if (now.l != null) {
                now.sum += now.l.sum;
                now.l.parent = now;
            }
            if (now.r != null) {
                now.sum += now.r.sum;
                now.r.parent = now;
            }
            now.sum++;
        }
    }

    static int getPosition(Node now) {
        int ans = 1;
        if (now.l != null) {
            ans += now.l.sum;
        }
        if (now.isTransposed) {
            ans = now.sum - ans + 1;
        } //in case it`s the right kid for real
        while (now.parent != null) {
            if (now.parent.isTransposed) {
                ans = now.sum - ans + 1;
                transpose(now.parent);
                continue;
            }
            if (now == now.parent.r) {
                ans += 1 + (now.parent.l == null ? 0 : now.parent.l.sum);
            }
            now = now.parent;
        }
        return ans - 1;
    }

    static Node merge(Node tree1, Node tree2) {
        if (tree1 == null) {
            return tree2;
        }
        if (tree2 == null) {
            return tree1;
        }
        //pushing down the transposing flag
        transpose(tree1);
        transpose(tree2);
        if (tree1.y > tree2.y) {
            tree1.r = merge(tree1.r, tree2);
            recalc(tree1);
            return tree1;
        }
        tree2.l = merge(tree1, tree2.l);
        recalc(tree2);
        return tree2;
    }

    static Pair split(Node now, int value) {
        if (now == null) {
            return new Pair(null, null);
        }
        //pushing down the transposing flag
        transpose(now);
        int position = now.l == null ? 0 : now.l.sum; //index
        if (position >= value) {
            Pair splited = split(now.l, value);
            if (now.l != null)
                now.l.parent = null;
            now.l = splited.second;
            if (now.l != null) now.l.parent = now;
            recalc(now);
            recalc(splited.first);
            splited.second = now;
            return splited;
        } else {
            Pair splited2 = split(now.r, value - position - 1);
            if (now.r != null)
                now.r.parent = null;
            now.r = splited2.first;
            if (now.r != null) now.r.parent = now;
            recalc(now);
            recalc(splited2.second);
            splited2.first = now;
            return splited2;
        }
    }

    static int getAnswer(Node firstTown, Node secondTown) {
        Node firstParent = getRoot(firstTown);
        Node secondParent = getRoot(secondTown);
        if (firstParent != secondParent) {
            return -1; //belong to different trees
        }
        int firstPosition = getPosition(firstTown);
        int secondPosition = getPosition(secondTown);
        return firstParent.isCycle ? Integer.min(Math.abs(firstPosition - secondPosition) - 1, firstParent.sum - Math.abs(firstPosition - secondPosition) - 1) : Math.abs(firstPosition - secondPosition) - 1;
    }

    static void build(Node firstTown, Node secondTown) {
        Node firstParent = getRoot(firstTown);
        Node secondParent = getRoot(secondTown);
        if (firstParent.equals(secondParent)) {
            firstParent.isCycle = true;
            return;
        }
        int firstPosition = getPosition(firstTown);
        int secondPosition = getPosition(secondTown);
        if (firstPosition == 0) {
            if (secondPosition == 0) {
                //left-left - transpose the first and 1 + 2 merge
                firstParent.isTransposed = !firstParent.isTransposed;
                merge(firstParent, secondParent);
            } else {
                //left-right - 2 + 1 merge
                merge(secondParent, firstParent);
            }
        } else {
            if (secondPosition == 0) {
                //right-left - 1 + 2 merge
                merge(firstParent, secondParent);
            } else {
                //right-right - transpose the second and 1 + 2 merge
                secondParent.isTransposed = !secondParent.isTransposed;
                merge(firstParent, secondParent);
            }
        }
    }

    static void remove(Node firstTown, Node secondTown) {
        Node root = getRoot(firstTown);
        if (root.isCycle) {
            root.isCycle = false;
            int firstPosition = getPosition(firstTown);
            int secondPosition = getPosition(secondTown);
            if (Integer.min(firstPosition, secondPosition) == 0 && Integer.max(firstPosition, secondPosition) == root.sum - 1) {
                return;
            } //in case they are left-right
            Pair splited = split(root, Integer.min(firstPosition, secondPosition) + 1);
            merge(splited.second, splited.first);
            Node root2 = getRoot(splited.first);
            if (root2 != null) {
                root2.isCycle = false;
            }
        } else {
            int firstPosition = getPosition(firstTown);
            int secondPosition = getPosition(secondTown);
            Pair splited = split(root, Integer.min(firstPosition, secondPosition) + 1);
            if (splited.first != null) {
                splited.first.isCycle = false;
            }
            if (splited.second != null) {
                splited.second.isCycle = false;
            }
        }
    }
}