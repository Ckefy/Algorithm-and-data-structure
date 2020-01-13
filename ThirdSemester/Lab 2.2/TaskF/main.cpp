#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll inf = 1e18;


vector < vector < pair<ll, ll> > > graph;

void dijkstra (ll s, vector <ll>& dist) {
 dist[s] = 0;
    set < pair<ll, ll> > que;
    que.insert (make_pair(0, s)); //first is dist second is vertex
    while (!que.empty()){
        ll minVertex = que.begin()->second;
        que.erase(que.begin());
        for (int j = 0; j < graph[minVertex].size(); j++){
            pair<ll, ll> cur = graph[minVertex][j];
            if (dist[minVertex] + cur.second < dist[cur.first]){
                que.erase(make_pair(dist[cur.first], cur.first));
                dist[cur.first] = dist[minVertex] + cur.second;
                que.insert(make_pair(dist[cur.first], cur.first));
            }
        }
    }
 }

int main()
{
    int n, m;
    cin>>n>>m;
    graph.resize(n);
    vector <ll> dist1 (n, inf);
    vector <ll> dist2 (n, inf);
    vector <ll> dist3 (n, inf);
    for (int i = 0; i < m; i++){
        ll a, b, w;
        cin>>a>>b>>w;
        a--; b--;
        graph[a].push_back(make_pair(b, w));
        graph[b].push_back(make_pair(a, w));
    }
    ll fir, sec, th;
    cin>>fir>>sec>>th;
    fir--; sec--; th--;
    dijkstra(fir, dist1);
    dijkstra(sec, dist2);
    dijkstra(th, dist3);
    ll ans = inf;
    //abc
    if (dist1[sec] != inf && dist2[th] != inf){
        ans = min(ans, dist1[sec] + dist2[th]);
    }
    //acb
    if (dist1[th] != inf && dist3[sec] != inf){
        ans = min(ans, dist1[th] + dist3[sec]);
    }
    //bac
    if (dist2[fir] != inf && dist1[th] != inf){
        ans = min(ans, dist2[fir] + dist1[th]);
    }
    if (ans == inf){
        cout<<-1;
    } else {
        cout<<ans;
    }
}
