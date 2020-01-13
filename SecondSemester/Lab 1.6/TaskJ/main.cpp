#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll n;
vector < vector < ll > > g;
vector <bool> was;
vector <bool> del;
vector <ll> sz;
vector <ll> answer;

void dfs (ll now){
    was[now] = true;
    ll size = 1;
    for (ll i = 0; i < g[now].size(); i++){
        if (!del[g[now][i]] && !was[g[now][i]]){
            dfs(g[now][i]);
            size += sz[g[now][i]];
        }
    }
    sz[now] = size;
}

ll centroid (ll now, ll size){
    was[now] = true;
    ll invar = size / 2;
    for (ll i = 0; i < g[now].size(); i++){
        if (!del[g[now][i]] && !was[g[now][i]]){
            if (sz[g[now][i]] > invar){
                return centroid(g[now][i], size);
            }
        }
    }
    //cout<<now<<endl;
    return now;
}

ll ans (ll now){
    if (sz[now] == 1){
        del[now] = true;
        return now;
    }
    was.resize(0);
    was.resize(n, false);
    dfs(now);
    if (sz[now] == 1){
        del[now] = true;
        return now;
    }
    was.resize(0);
    was.resize(n, false);
    ll center = centroid(now, sz[now]);
    del[center] = true;
    for (ll i = 0; i < g[center].size(); i++){
        if (!del[g[center][i]]){
            ll subTreeCenter = ans(g[center][i]);
            answer [subTreeCenter] = center + 1;
        }
    }
    return center;
}

int main()
{
    cin>>n;
    g.resize(n, vector <ll>());
    was.resize(n, false);
    del.resize(n, false);
    sz.resize(n, 0);
    answer.resize(n, 0);
    for (ll i = 0; i < n - 1; i++){
        ll a, b;
        cin>>a>>b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    ans(0);
    for (ll i = 0; i < n; i++){
        cout<<answer[i]<<' ';
    }
}
