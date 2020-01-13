#include <bits/stdc++.h>

using namespace std;
#define ll long long

int n, m;

set< pair < ll, ll > > edges;

vector < vector < ll > > g;
vector <ll> answer;

ll mex (vector <int> args){
    set<ll> argsSet (args.begin(), args.end());
    for (int i = 0; ; i++){
        if (!argsSet.count(i))
            return i;
    }
}

ll recMex(int now){
    if (answer[now] == -1){
        if (g[now].size() == 0){
            answer[now] = 0;
            return 0;
        }
        vector <int> args;
        for (int i = 0; i < g[now].size(); i++){
            args.push_back(recMex(g[now][i]));
        }
        answer[now] = mex(args);
        return answer[now];
    } else {
        return answer[now];
    }
}

int main()
{
    cin>>n>>m;
    g.resize(n);
    for (int i = 0; i < m; i++){
        int x, y;
        cin>>x>>y;
        x--; y--;
        pair <ll, ll> edge = make_pair(x, y);
        if (!edges.count(edge)){
            g[x].push_back(y);
            edges.insert(edge);
        }
    }
    answer.resize(n, -1);
    for (int i = 0; i < n; i++){
        if (answer[i] == -1){
            recMex(i);
        }
    }
    for (int i = 0; i < n; i++){
        cout<<answer[i]<<endl;
    }
}
