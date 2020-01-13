#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll inf = 600000000000000ll;

struct Edge {
    int a, b;
    ll cost;
    Edge(int a, int b, ll cost) : a(a), b(b), cost(cost){}
} ;

vector <bool> was;

int n;
vector < vector < ll > > d;
vector< vector < Edge > > edges;

int main()
{
    int m, s, counter;
    cin>>n>>m>>counter>>s;
    s--;
    d.resize(counter + 1, vector <ll> (n, inf));
    edges.resize(n);
    for (int i = 0; i < m; i++){
            ll a, b, cost;
            cin>>a>>b>>cost;
            a--; b--;
            edges[b].push_back(Edge(a, b, cost));
    }
    d[0][s] = 0;
    for (int i = 0; i < counter; i++){
        for (int j = 0; j < n; j++){
            for (Edge edge : edges[j]){
                ll sum;
                if (d[i][edge.a] == -inf || edge.cost == -inf){
                    sum = -inf;
                } else if (d[i][edge.a] == inf || edge.cost == inf){
                    sum = inf;
                } else {
                    sum = d[i][edge.a] + edge.cost;
                }
                d[i + 1][j] = min(d[i + 1][j], sum);
            }
        }
    }
    for (int i = 0; i < n; i++){
        if (abs(d[counter][i]) == inf){
            cout<<-1<<endl;
        } else {
            cout<<d[counter][i]<<endl;
        }
    }
}
