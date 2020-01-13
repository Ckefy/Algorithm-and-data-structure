#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector <bool> color;
vector < vector < pair < int, int > > > g;
ll timer = 0;
vector <int> tin, alltime;
set <int> ans;

void dfs (int now, int parent){
    color[now] = 1;
    tin[now] = timer;
    timer++;
    int children = 0;
    alltime[now] = tin[now];
    for (int i = 0; i < g[now].size(); i++){
        if (g[now][i].first == parent) continue;
        if (!color[g[now][i].first]){
            dfs(g[now][i].first, now);
            alltime[now] = (alltime[now] > alltime[g[now][i].first]) ? alltime[g[now][i].first] : alltime[now];
            if (tin[now] <= alltime[g[now][i].first] && parent != -1){
                ans.insert(now + 1);
            }
            children++;
        } else {
            alltime[now] = (alltime[now] > tin [g[now][i].first]) ? tin[g[now][i].first] : alltime[now];
            //not a bridge;
        }
    }
    if (parent == -1 && children > 1){
        //this is root and cutpoint
        ans.insert(now + 1);
    }
}

int main()
{
    int n, m;
    cin>>n>>m;
    g.resize(n, vector < pair < int, int > > (0));
    color.resize(n, 0);
    for (int i = 0; i < m; i++){
       ll u, v;
       cin>>u>>v;
       u--; v--;
       g[u].push_back(make_pair(v, i + 1));
       g[v].push_back(make_pair(u, i + 1));
    }
    tin.resize(n);
    alltime.resize(n);
    for (int i = 0; i < n; i++){
        if (!color[i]){
            dfs(i, -1);
        }
    }
    cout<<ans.size()<<endl;
    for (int i : ans){
        cout<<i<<' ';
    }
}
