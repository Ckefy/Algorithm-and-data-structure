#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll n, logn = 0;
vector <ll> depth;
vector < vector < ll > > g;
vector < vector < ll > > dp;
vector < vector < ll > > mini;

void dfs (ll v, ll counter){
    depth[v] = counter;
    for (ll i : g[v]){
        dfs(i, counter + 1);
    }

}

ll lca (ll a, ll b){
    ll ansMin = LONG_MAX;
    if (depth[a] < depth[b]){
            swap (a, b);
        }
        ll height = depth[a] - depth[b];
        for (ll i = logn; i >= 0; i--){
            if (pow (2, i) <= height){
                height -= pow(2, i);
                ansMin = min(ansMin, mini[a][i]);
                a = dp[a][i];
            }
        }
        ll ans = -1;
        if (a == b){
            ans = a;
        }
        for (ll i = logn; i >= 0; i--){
            if(dp[a][i] != dp[b][i]){
                ansMin = min(ansMin, mini[a][i]);
                ansMin = min(ansMin, mini[b][i]);
                a = dp[a][i];
                b = dp[b][i];
            }
        }
        if (ans == -1){
            ansMin = min(ansMin, mini[a][0]);
            ansMin = min(ansMin, mini[b][0]);
        }
        return ansMin;
}

int main()
{
    ifstream f1("minonpath.in");
    ofstream f2("minonpath.out");
    ll root = 0;
    f1>>n;
    depth.resize(n);
    vector <ll> p(n);
    vector <ll> w(n);
    w[0] = LONG_MAX;
    g.resize(n, vector <ll>());
    for (ll i = 1; i < n; i++){
        f1>>p[i];
        p[i]--;
        g[p[i]].push_back(i);
        f1>>w[i];
    }
    while (pow(2, logn) < n){
        logn++;
    }
    dp.resize(n, vector <ll> (logn + 1));
    mini.resize(n, vector <ll> (logn + 1));
    for (ll i = 0; i < n; i++){
        dp[i][0] = p[i];
        mini[i][0] = w[i];
    }
    for (ll i = 0; i < logn; i++){
        for (ll v = 0; v < n; v++){
            if (dp[v][i] == -1 || dp[v][i] == root) {
                dp[v][i + 1] = -1;
                mini[v][i + 1] = LONG_MAX;
                continue;
            }
            dp[v][i + 1] = dp[dp[v][i]][i];
            mini[v][i + 1] = min(mini[v][i], mini[dp[v][i]][i]);
        }
    }
    dfs(0, 0);
    ll m;
    f1>>m;
    //lca
    for (ll j = 0; j < m; j++){
        ll a, b;
        f1>>a>>b;
        a--; b--;
        f2<<lca(a, b)<<endl;
    }
}
