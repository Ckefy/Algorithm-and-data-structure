#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector <int> master;

int findMaster (int now){
    if (now == master[now]){
        return now;
    } else {
        master[now] = findMaster(master[now]);
        return master[now];
    }
}

void connect (int from, int to){
    master[findMaster(to)] = findMaster(from);
}

int main()
{
    vector < pair < int, pair < int, int > > > g;
    int n, m;
    cin>>n>>m;
    for (int i = 0; i < n; i++){
        master.push_back(i);
    }
    for (int i = 0; i < m; i++){
        int a, b, w;
        cin>>a>>b>>w;
        a--; b--;
        g.push_back(make_pair(w, make_pair(a, b)));
    }
    sort(g.begin(), g.end());
    ll answer = 0;
    for (int i = 0; i < m; i++){
        pair <int, int> edge = g[i].second;
        int w = g[i].first;
        int from = edge.first;
        int to = edge.second;
        if (findMaster(from) != findMaster(to)){
            connect(from, to);
            answer += w;
        }
    }
    cout<<answer;
}
