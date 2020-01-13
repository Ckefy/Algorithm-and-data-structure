#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector <bool> color;
vector <bool> color2;
vector < vector < pair < int, int > > > g;
ll timer = 0;
vector <int> tin, alltime;
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
        } else {
            alltime[now] = (alltime[now] > tin [g[now][i].first]) ? tin[g[now][i].first] : alltime[now];
            //not a bridge;
        }
    }
}

void dfs2(int now, int parent, int comp){
    color2[now] = 1;
    for (pair <int, int> i : g[now]){
        if (i.second == parent) continue;
        if (!color2[i.first]){
            if (alltime[i.first] < tin[now]) {
                ans[i.second] = comp;
                dfs2(i.first, i.second, comp);
            } else {
                maxi++;
                ans[i.second] = maxi;
                dfs2(i.first, i.second, maxi);
            }
        } else if (tin[i.first] < tin[now]){
            ans[i.second] = comp;
        }
    }
}

void make_answer(){
    for (int i = 0; i < n; i++){
        if (!color2[i]){
            dfs2(i, -1, maxi);
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
    for (int i = 0; i < m; i++){
       ll u, v;
       cin>>u>>v;
       u--; v--;
       g[u].push_back(make_pair(v, i + 1));
       g[v].push_back(make_pair(u, i + 1));
    }
    ans.resize(m + 1, 0);
    tin.resize(n);
    alltime.resize(n);
    for (int i = 0; i < n; i++){
        if (!color[i]){
            dfs(i, -1);
        }
    }
    make_answer();
    cout<<maxi<<endl;
    for (int i = 0; i < m; i++){
        cout<<ans[i + 1]<<' ';
    }
}
