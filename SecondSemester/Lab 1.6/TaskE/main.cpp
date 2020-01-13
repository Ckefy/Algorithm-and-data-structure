#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll n, logn = 0;
vector <ll> depth;
vector <ll> numerate;
vector < vector < ll > > g;
vector < vector < ll > > dp;
vector < vector < ll > > mini;
ll ans = -1;

void dfs (ll now, ll from, ll counter){
    depth[now] = counter;
    dp[now][0] = from;
    for (ll i = 1; i < logn; i++){
        dp[now][i] = dp[dp[now][i - 1]][i - 1];
    }
    for (ll i : g[now]){
        if (i != from){
            dfs(i, now, counter + 1);
        }
    }
}

ll getAns(ll now, ll from){
    ll sum = numerate[now];
    for (ll i : g[now]){
        if (i != from){
            sum += getAns(i, now);
        }
    }
    if (sum == 0){
        ans++;
    }
    return sum;
}

int main()
{
    cin>>n;
    depth.resize(n);
    g.resize(n, vector <ll>());
    while (pow(2, logn) < n){
        logn++;
    }
    dp.resize(n, vector <ll> (logn + 1));
    ll x, y;
    for (ll i = 1; i < n; i++){
        cin>>x>>y;
        x--; y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs (0, 0, 0);
    numerate.resize(n);
    ll m;
    cin>>m;
    for (ll i = 0; i < m; i++){
        cin>>x>>y;
        x--; y--;
        numerate[x]++; numerate[y]++;
        if (depth[x] < depth[y]) swap(x,y);
        ll height = depth[x] - depth[y];
        for (ll i = logn - 1; i >= 0; i--){
            if (pow (2, i) <= height){
                height -= pow(2, i);
                x = dp[x][i];
            }
        }
        ll now = logn - 1;
        while (x != y){
            while(now != 0 && dp[x][now] == dp[y][now]){
                now--;
            }
            x = dp[x][now]; y = dp[y][now];
        }
        numerate[x] -=2;
    }
    getAns(0, 0);
    cout<<ans;
}
