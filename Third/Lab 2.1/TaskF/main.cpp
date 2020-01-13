#include <bits/stdc++.h>

using namespace std;

vector <bool> color;
vector < vector < int > > g, gTransp;
vector <int> que;
vector <int> comp;
vector <int> compColor;

void initTout (int now){
    color[now] = 1;
    for (int i = 0; i < g[now].size(); i++){
        if (!color[g[now][i]]){
            initTout(g[now][i]);
        }
    }
    que.push_back(now);
}

void findComp (int now){
    color[now] = 1;
    comp.push_back(now);
    for (int i = 0; i < gTransp[now].size(); i++){
        if (!color[gTransp[now][i]]){
            findComp(gTransp[now][i]);
        }
    }
}

int main()
{
    int n, m;
    cin>>n>>m;
    g.resize(n, vector <int> (0));
    gTransp.resize(n, vector <int> (0));
    color.resize(n, 0);
    compColor.resize(n, -1);
    for (int i = 0; i < m; i++){
        int from, to;
        cin>>from>>to;
        from--; to--;
        g[from].push_back(to);
        gTransp[to].push_back(from);
    }
    for (int i = 0; i < n; i++){
        if (!color[i]) {
                initTout(i);
        }
    }
    color.resize(0);
    color.resize(n, 0);
    int compCounter = 0;
    reverse(que.begin(), que.end());
    for (int i = 0; i < n; i++){
        int now = que[i];
        if (!color[now]){
            findComp(now);
            for (int j = 0; j < comp.size(); j++){
                compColor[comp[j]] = compCounter;
            }
            compCounter++;
            comp.clear();
        }
    }
    set < pair < int, int > > answer;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < g[i].size(); j++){
            if (compColor[i] != compColor[g[i][j]]){
                if (compColor[i] > compColor[g[i][j]]) swap (compColor[i], compColor[g[i][j]]); // i < j
                answer.insert(make_pair(compColor[i], compColor[g[i][j]]));
            }
        }
    }
    cout<<answer.size();
}
