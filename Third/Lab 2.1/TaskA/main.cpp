#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector <int> color;
vector < vector < int > > g;
vector <int> answer;

bool isCycle (int now){
    color[now] = 1;
    for (int i = 0; i < g[now].size(); i++){
        if (color[g[now][i]] == 0){
            if (isCycle(g[now][i])){
                return true;
            }
        }
        else if (color[g[now][i]] == 1){
            return true;
        }
    }
    color[now] = 2;
    return false;
}

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
    int n, m;
    cin>>n>>m;
    g.resize(n, vector <int> (0));
    color.resize(n, 0);
    for (int i = 0; i < m; i++){
       ll u, v;
       cin>>u>>v;
       u--; v--;
       g[u].push_back(v);
    }
    for (int i = 0; i < n; i++){
        if (color[i] != 2 && isCycle(i)){
            cout<<-1<<endl;
            return 0;
        }
    }
    color.resize(0);
    color.resize(n, 0);
    for (int i = 0; i < n; i++){
        if (!color[i]){
            dfs(i);
        }
    }
    for (int i = n - 1; i >= 0; i--){
        cout<<answer[i] + 1<<' ';
    }
}
