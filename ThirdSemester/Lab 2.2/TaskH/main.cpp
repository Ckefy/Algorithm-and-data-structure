#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector <int> color;
vector < vector < int > > g;
vector <int> answer;

void dfs (int now){
    color[now] = 1;
    for (int i = 0; i < g[now].size(); i++){
        if (!color[g[now][i]]){
            dfs(g[now][i]);
        }
    }
    answer.push_back(now);
}

int main()
{
    ifstream f1 ("game.in");
    int start;
    int n, m;
    f1>>n>>m>>start;
    start--;
    g.resize(n, vector <int> (0));
    color.resize(n, 0);
    for (int i = 0; i < m; i++){
       ll u, v;
       f1>>u>>v;
       u--; v--;
       g[u].push_back(v);
    }
    color.resize(n, 0);
    for (int i = 0; i < n; i++){
        if (!color[i]){
            dfs(i);
        }
    }
    //answer = top sorted
    vector <bool> victory(n, false);
    for (int i : answer){
        for (int j : g[i]){
            victory[i] = !victory[j];
            if (victory[i]){
                break;
            }
        }
    }
    ofstream f2("game.out");
    if (victory[start]){
        f2<<"First player wins";
    } else {
        f2<<"Second player wins";
    }

}
