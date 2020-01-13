#include <bits/stdc++.h>
#define ll int64_t
using namespace std;
ll inf = 6000000000000000000ll;

struct Edge {
    int a, b;
    ll cost;
    Edge(int a, int b, ll cost) : a(a), b(b), cost(cost){}
} ;

vector <bool> was;

int n;
vector < vector < ll > > d;
vector <ll> dist;
vector <ll> dist2;
vector<Edge> edges;

void dfs(int now){
    was[now] = 1;
    for (auto i : d[now]){
        if (!was[i]){
            dfs(i);
        }
    }
}

int main()
{
    int m, s;
    cin>>n>>m>>s;
    s--;
    d.resize(n);
    for (int i = 0; i < m; i++){
            ll a, b, cost;
            cin>>a>>b>>cost;
            a--; b--;
            d[a].push_back(b);
            edges.push_back(Edge(a, b, cost));
    }
    dist.resize(n, inf*1.5);
    dist2.resize(n);
    dist[s] = 0;
    was.resize(n);
    dfs(s);
    vector <bool> connection (n);
    for (int i = 0; i < n; i++){
        connection[i] = was[i];
    }
    was.resize(0);
    was.resize(n, 0);
    for (int i = 0; i < n; i++){
        for (auto edge : edges){
            if (!connection[edge.b]) continue;
            if (dist[edge.a] < inf && dist[edge.b] > dist[edge.a] + edge.cost){
                dist[edge.b] = dist[edge.a] + edge.cost;
                if (dist[edge.b] < -inf)
                    dist[edge.b] = -inf;
            }
        }
    }
    for (int i = 0; i < n; i++){
        dist2[i] = dist[i];
    }
    for (int i = 0; i < 1; i++){
        for (auto edge : edges){
            if (!connection[edge.b]) continue;
            if (dist[edge.a] < inf && dist[edge.b] > dist[edge.a] + edge.cost){
                dist[edge.b] = dist[edge.a] + edge.cost;
            }
        }
    }
    for (int i = 0; i < n; i++){
        if (connection[i] && dist[i] != dist2[i]){
            dfs(i);
        }
    }
    for (int i = 0; i < n; i++){
        if (dist2[i] >= inf){
            cout<<'*'<<endl;
        } else if (was[i]){
            cout<<'-'<<endl;
        } else {
            cout<<dist2[i]<<endl;
        }
    }
}
