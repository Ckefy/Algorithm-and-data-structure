#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll n, logn = 0;
vector <ll> depth;
vector < vector < ll > > g;
vector < vector < ll > > dp;

void dfs (ll v, ll counter){
    depth[v] = counter;
    for (ll i : g[v]){
        dfs(i, counter + 1);
    }

}

ll lca (ll a, ll b){
    if (depth[a] < depth[b]){
            swap (a, b);
        }
        ll height = depth[a] - depth[b];
        for (ll i = logn; i >= 0; i--){
            if (pow (2, i) <= height){
                height -= pow(2, i);
                a = dp[a][i];
            }
        }
        ll ans = -1;
        if (a == b){
            ans = a;
        }
        for (ll i = logn; i >= 0; i--){
            if(dp[a][i] != dp[b][i]){
                a = dp[a][i];
                b = dp[b][i];
            }
        }
        if (ans == -1){
            ans = dp[a][0];
        }
        return ans;
}

int main()
{
    ll root = 0;
    cin>>n;
    depth.resize(n);
    vector <ll> p(n);
    g.resize(n, vector <ll>());
    for (ll i = 1; i < n; i++){
        cin>>p[i];
        p[i]--;
        g[p[i]].push_back(i);
    }
    while (pow(2, logn) < n){
        logn++;
    }
    dp.resize(n, vector <ll> (logn + 1));
    for (ll i = 0; i < n; i++){
        dp[i][0] = p[i];
    }
    for (ll i = 0; i < logn; i++){
        for (ll v = 0; v < n; v++){
            if (dp[v][i] == -1 || dp[v][i] == root) {
                dp[v][i + 1] = -1;
                continue;
            }
            dp[v][i + 1] = dp[dp[v][i]][i];
        }
    }
    dfs(0, 0);
    ll m;
    cin>>m;
    //lca
    for (ll j = 0; j < m; j++){
        ll a, b;
        cin>>a>>b;
        a--; b--;
        cout<<lca(a, b) + 1<<endl;
    }
}
