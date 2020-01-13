#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector <bool> color;
vector <bool> color2;
vector < vector < pair < int, int > > > g;
ll timer = 0;
ll counter = 0;
vector <int> tin, alltime;
vector <bool> bridges;
vector <int> ans;
int maxi = 0;
int n;


void dfs (int now, int parent){
    color[now] = 1;
    tin[now] = timer;
    timer++;
    alltime[now] = tin[now];
    for (int i = 0; i < g[now].size(); i++){
        if (g[now][i].second == parent) continue;
        if (!color[g[now][i].first]){
            dfs(g[now][i].first, g[now][i].second);
            alltime[now] = (alltime[now] > alltime[g[now][i].first]) ? alltime[g[now][i].first] : alltime[now];
            if (tin[now] < alltime[g[now][i].first]){
                bridges[g[now][i].second] = true;
            }
        } else {
            alltime[now] = (alltime[now] > tin [g[now][i].first]) ? tin[g[now][i].first] : alltime[now];
            //not a bridge;
        }
    }
}

void dfs2 (int now, int comp){
    color2[now] = 1;
    for (int i = 0; i < g[now].size(); i++){
        if (!color2[g[now][i].first]){
            if (!bridges[g[now][i].second]){
                ans[g[now][i].first] = comp;
                dfs2(g[now][i].first, comp);
            } else {
                maxi++;
                ans[g[now][i].first] = maxi;
                dfs2(g[now][i].first, maxi);
            }
        }
    }
}

void make_answer(){
    for (int i = 0; i < n; i++){
        if (!color2[i]){
            maxi++;
            ans[i] = maxi;
            dfs2(i, maxi);
        }
    }
}

int main()
{
    int m;
    cin>>n>>m;
    g.resize(n, vector < pair < int, int > > (0));
    color.resize(n, 0);
    color2.resize(n, 0);
    bridges.resize(m + 1, 0);
    ans.resize(n);
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
    make_answer();
    cout<<maxi<<endl;
    for (int i = 0; i < n; i++){
        cout<<ans[i]<<' ';
    }
}
