#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{
    ll n, root;
    cin>>n;
    vector <ll> p(n);
    for (ll i = 0; i < n; i++){
        cin>>p[i];
        if (p[i] != 0){
            p[i]--;
        } else {
            root = i;
            p[i] = i;
        }
    }
    ll logn = 0;
    while (pow(2, logn) < n){
        logn++;
    }
    vector < vector < ll > > dp (n, vector <ll> (logn));
    for (ll i = 0; i < n; i++){
        dp[i][0] = p[i];
    }
    for (ll i = 0; i < logn - 1; i++){
        for (ll v = 0; v < n; v++){
            if (dp[v][i] == -1 || dp[v][i] == root) {
                dp[v][i + 1] = -1;
                continue;
            }
            dp[v][i + 1] = dp[dp[v][i]][i];
        }
    }
    for (ll i = 0; i < n; i++){
        if (i == root){
            cout<<root + 1<<":"<<endl;
            continue;
        }
        cout<<i + 1<<":"<<" ";
        for (ll j = 0; j < logn; j++){
            if (dp[i][j] == -1) {
                break;
            }
            cout<<dp[i][j] + 1<<' ';
        }
        cout<<endl;
    }
}
