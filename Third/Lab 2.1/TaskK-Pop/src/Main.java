import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    static class Edge {
        int from;
        int to;
        long w;

        Edge(int from, int to, long w) {
            this.from = from;
            this.to = to;
            this.w = w;
        }
    }

    static long inf = Long.MAX_VALUE;
    static ArrayList<Edge> g = new ArrayList<>();
    static ArrayList<Boolean> was = new ArrayList<>();

    static void css(int now){
        was.set(now, true);
        for (int i = 0; i < g.size(); i++){
            if (g.get(i).from == now){
                if (!was.get(g.get(i).to)){
                    css(g.get(i).to);
                }
            }
        }
    }

    static long greatWall(int n, int root, ArrayList<Edge> graph){
        ArrayList<Boolean> cycle = new ArrayList<>();
        ArrayList<Integer> comp = new ArrayList<>();
        ArrayList<Edge> lowest = new ArrayList<>();
        ArrayList<Edge> newGraph = new ArrayList<>();
        long ans = 0;
        for (int i = 0; i < n; i++){
            was.set(i, false);
            cycle.add(false);
            comp.add(0);
            lowest.add(new Edge (-1, -1, inf));
        }
        int counter = 0;
        for (Edge cur : graph){
            if (lowest.get(cur.to).w > cur.w){
                lowest.set(cur.to, cur);
            }
        }
        //min edge from the cur.to
        lowest.set(root, new Edge(-1, root, 0));
        for (int i = 0; i < n; i++){
            if (!was.get(i)){
                ArrayList <Integer> way = new ArrayList<>();
                int cur = i;
                while (cur != -1 && !was.get(cur)){
                    was.set(cur, true);
                    way.add(cur);
                    cur = lowest.get(cur).from;
                }
                boolean isCycle = false;
                for (int j : way){
                    comp.set(j, counter);
                    if (j == cur){
                        cycle.set(counter, true);
                        isCycle = true;
                    }
                    if (!isCycle){
                        counter++;
                    }
                }
                if (isCycle){
                    counter++;
                }
            }
        }
        if (counter == n){
            for (int i = 0; i < lowest.size(); i++){
                ans += lowest.get(i).w;
            }
            return ans;
        } else {
            for (int i = 0; i < lowest.size(); i++){
                if (cycle.get(comp.get(lowest.get(i).to))){
                    ans += lowest.get(i).w;
                }
            }
            for (Edge i : graph){
                int a = comp.get(i.from);
                int b = comp.get(i.to);
                long weight = i.w;
                if (a != b){
                    if (cycle.get(b)){
                        newGraph.add(new Edge(a, b, weight - lowest.get(i.to).w));
                    } else {
                        newGraph.add(new Edge(a, b, weight));
                    }
                }
            }
            return ans + greatWall(counter, comp.get(root), newGraph);
        }
    }

    public static void main(String[] args) {
        Scanner f1 = new Scanner(System.in);
        boolean flag;
        int n, m;
        n = f1.nextInt();
        m = f1.nextInt();
        for (int i = 0; i < n; i++){
            was.add(false);
        }
        for (int i = 0; i < m; i++) {
            int a, b, weight;
            a = f1.nextInt();
            b = f1.nextInt();
            weight = f1.nextInt();
            a--;
            b--;
            if (a == b) {
                continue;
            }
            flag = false;
            Edge now = new Edge(a, b, weight);
            for (Edge j : g) {
                if (j.from == now.from && j.to == now.to){
                    flag = true;
                    j.w = Long.min(j.w, now.w);
                }
            }
            if (!flag){
                g.add(now);
            }
        }
        css(0);
        //need to find if we can reach any vertex from the root
        for (int i = 0; i < n; i++){
            if (!was.get(i)){
                System.out.println("NO");
                return;
            }
        }
        long ans = greatWall(n, 0, g);
        System.out.println("YES");
        System.out.println(ans);
    }
}
