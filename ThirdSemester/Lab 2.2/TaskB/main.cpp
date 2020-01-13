#include <bits/stdc++.h>

using namespace std;

const long long inf = 1000000000;

int main()
{
    int n, m;
    cin>>n>>m;
    vector < vector < pair<long long, long long> > > graph(n);
    vector <long long> dist (n, inf);
    for (int i = 0; i < m; i++){
        long long a, b, w;
        cin>>a>>b>>w;
        a--; b--;
        graph[a].push_back(make_pair(b, w));
        graph[b].push_back(make_pair(a, w));
    }
    dist[0] = 0;
    set < pair<long long, long long> > que;
    que.insert (make_pair(0, 0)); //first is dist second is vertex
    while (!que.empty()){
        int minVertex = que.begin()->second;
        que.erase(que.begin());
        for (int j = 0; j < graph[minVertex].size(); j++){
            pair<long long, long long> cur = graph[minVertex][j];
            if (dist[minVertex] + cur.second < dist[cur.first]){
                que.erase(make_pair(dist[cur.first], cur.first));
                dist[cur.first] = dist[minVertex] + cur.second;
                que.insert(make_pair(dist[cur.first], cur.first));
            }
        }
    }
    for (int i = 0; i < n; i++){
        cout<<dist[i]<<' ';
    }
}
