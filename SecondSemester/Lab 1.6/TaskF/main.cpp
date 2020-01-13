#include <bits/stdc++.h>
#define ll int

using namespace std;

ll n, logn = 0;
vector <ll> depth;
vector <ll> timeIn;
vector < vector < ll > > g;
vector < vector < ll > > dp;
ll timeCount = 0;
vector <ll> powed;

void dfs (ll v, ll depthCount){
    depth[v] = depthCount;
    timeIn[v] = timeCount++;
    for (ll i : g[v]){
        dfs(i, depthCount + 1);
    }
}

ll lca (ll a, ll b){
    if (depth[a] < depth[b]){
            swap (a, b);
        }
        ll height = depth[a] - depth[b];
        for (ll i = logn; i >= 0; i--){
            if (powed[i] <= height){
                height -= powed[i];
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll root;
    cin>>n;
    depth.resize(n);
    timeIn.resize(n);
    vector <ll> p(n);
    g.resize(n, vector <ll>());
    for (ll i = 0; i < n; i++){
        cin>>p[i];
        p[i]--;
        if (p[i] == -2){
            p[i] = i;
            root = i;
            continue;
        }
        g[p[i]].push_back(i);
    }
    while (pow(2, logn) < n){
        logn++;
    }
    for (ll i = 0; i <= logn; i++){
        powed.push_back(pow(2, i));
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
    dfs(root, 0);
    ll m;
    cin>>m;
    //lca
    vector <ll> now (n + 2);
    for (ll j = 0; j < m; j++){
        ll sz;
        cin>>sz;
        now[0] = root;
        for (ll i = 1; i <= sz; i++){
            cin>>now[i];
            now[i]--;
        }
        sort(now.begin() + 1, now.begin() + sz + 1, [&timeIn](ll a, ll b) {
            return timeIn[a] < timeIn[b];
        });
        ll ans = 1;
        for (ll i = 1; i <= sz; i++){
            ll nowLCA = lca(now[i - 1], now[i]);
            ans += (depth[now[i]] - depth [nowLCA]);
        }
        cout<<ans<<"\n";
    }
}
