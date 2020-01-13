import java.util.*;

public class Main {
    static int n;
    static ArrayList<ArrayList<Integer>> g, gtr;
    static ArrayList<Boolean> was;
    static ArrayList<Integer> order, component;

    public static void dfsG(int v) {
        was.set(v, true);
        int u;
        for (int i = 0; i < g.get(v).size(); i++) {
            u = g.get(v).get(i);
            if (!was.get(u)) {
                dfsG(u);
            }
        }
        order.add(v);
    }

    public static void dfsGTR(int v, int count) {
        component.set(v, count);
        int u;
        for (int i = 0; i < gtr.get(v).size(); i++) {
            u = gtr.get(v).get(i);
            if (component.get(u) == -1) {
                dfsGTR(u, count);
            }
        }
    }

    public static void main(String[] args) {
        Scanner f1 = new Scanner(System.in);
        n = f1.nextInt();
        int m = f1.nextInt();

        g = new ArrayList<>();
        gtr = new ArrayList<>();
        was = new ArrayList<>();
        component = new ArrayList<>();
        order = new ArrayList<>();

        for (int i = 0; i < 2 * n; i++) {
            was.add(false);
            component.add(-1);
            g.add(new ArrayList<>());
            gtr.add(new ArrayList<>());
        }

        String[] names = new String[2 * n];
        for (int i = 0; i < n; i++){
            String name = f1.next();
            names[i] = "+" + name;
            names[n + i] = "-" + name;
        }

        for (int i = 0; i < m; i++) {
            String first = f1.next();
            String garbage = f1.next();
            String second = f1.next();
            // String nFirst, nSecond;
            int a = 0, b = 0, nota = 0, notb = 0;

            /*if (first.charAt(0) == '-'){
                nFirst = "+" + first.substring(1);
            } else {
                nFirst = "-" + first.substring(1);
            }
            if (second.charAt(0) == '-'){
                nSecond = "+" + second.substring(1);
            } else {
                nSecond = "-" + second.substring(1);
            }*/

            for (int j = 0; j < 2 * n; j++){
                if (first.equals(names[j])){
                    a = j;
                }
                if (second.equals(names[j])){
                    b = j;
                } /*
                if (nFirst.equals(names[j])){
                    nota = j;
                }
                if (nSecond.equals(names[j])){
                    notb = j;
                }*/
            }
            for (int j = 0; j < 2 * n; j++){
                if (first.substring(1).equals(names[j].substring(1)) && j != a){
                    nota = j;
                }
                if (second.substring(1).equals(names[j].substring(1)) && j != b){
                    notb = j;
                }
            }
            g.get(a).add(b);
            gtr.get(b).add(a);
            g.get(notb).add(nota);
            gtr.get(nota).add(notb);
        }

        for (int i = 0; i < 2 * n; i++) {
            if (!was.get(i)) {
                dfsG(i);
            }
        }

        int count = 0;
        for (int i = 0; i < 2 * n; i++) {
            int c = order.get(2 * n - 1 - i);
            if (component.get(c) == -1) {
                dfsGTR(c, ++count);
                //count++;
            }
        }

        ArrayList <Integer> answer = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (component.get(i).equals(component.get(i + n))) {
                System.out.println("-1");
                return;
            } else if (component.get(i) > component.get(i + n)){
                answer.add(i);
            }
        }
        System.out.println(answer.size());
        for (Integer i : answer){
            System.out.println(names[i].substring(1));
        }
    }
}
