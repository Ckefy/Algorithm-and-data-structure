#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll n, logn = 0, index = 1;
vector <ll> depth;
vector <ll> next1;
vector <bool> deleted;
vector < vector < ll > > dp;
ll root = 0;

ll getNext (ll now){
    if (!deleted[now]){
        return now;
    }
    next1[now] = getNext(next1[now]);
    return next1[now];
}

void addNew(ll parentRex, ll index){
    next1[index] = parentRex;
    depth[index] = depth[parentRex] + 1;
    dp[index][0] = parentRex;
    for (ll i = 0; i < logn; i++){
        if (dp[index][i] == -1 || dp[index][i] == root) {
            dp[index][i + 1] = -1;
            continue;
        }
        dp[index][i + 1] = dp[dp[index][i]][i];
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
        if (a == b){
            return b;
        }
        for (ll i = logn; i >= 0; i--){
            if(dp[a][i] != dp[b][i]){
                a = dp[a][i];
                b = dp[b][i];
            }
        }
        return getNext(dp[a][0]);
}

int main()
{
    cin>>n;
    depth.resize(n + 1, 0);
    next1.resize(n + 1, 0);
    deleted.resize(n + 1, false);
    while (pow(2, logn) < n){
        logn++;
    }
    dp.resize(n + 1, vector <ll> (logn + 1));
    dp[0][0] = 0;
    char type;
    for (ll i = 0; i < n; i++){
        cin>>type;
        if (type == '+'){
            ll parentRex;
            cin>>parentRex;
            parentRex--;
            addNew (parentRex, index);
            index++;
        } else if (type == '-'){
            ll forgetRex;
            cin>>forgetRex;
            deleted[--forgetRex] = true;
        } else {
            ll rex, dyna;
            cin>>rex>>dyna;
            cout<<lca(--rex, --dyna) + 1<<endl;
        }
    }
}
