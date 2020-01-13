#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll fl(ll len){
    if (len == 1)
        return 0;
    else
        return (fl(len / 2) + 1);
}

int main()
{
    ll n, m, a0;
    cin>>n>>m>>a0;
    vector <ll> a(n);
    ll mod = 16714589;
    ll x = 23, y = 21563; //(x * a[i - 1] + y) % mod;
    a[0] = a0;
    for (ll i = 1; i < n; i++){
        a[i] = (x * a[i - 1] + y) % mod;
    }
    vector <ll> floors (n);
    for (ll i = 1; i <= n; i++){
        floors[i - 1] = fl(i);
    }
    ll logn = floors[n - 1] + 1;
    vector < vector < ll > > st (n, vector <ll> (logn));
    for (ll j = 0; j < logn; j++){
        for (ll i = 0; i < n; i++){
            if (j == 0){
                    st[i][j] = a[i];
            } else if (i + pow(2, j - 1) < n) {
                st[i][j] = min (st[i][j - 1], st[i + pow(2, j - 1)][j - 1]);
            }
        }
    }
    ll left, right;
    cin>>left>>right;
    left--;
    right--;
    ll ans = 0;
    for (ll i = 1; i <= m; i++){
        ll left1 = min (left, right), right1 = max (left, right);
        ll j = floors [right1 - left1];
        ans = min(st[left1][j], st[right1 - pow(2, j) + 1][j]);
        if (i != m) left = ((17 * (left + 1) + 751 + ans + 2 * i) % n);
        if (i != m) right = ((13 * (right + 1) + 593 + ans + 5 * i) % n);
    }
    cout<<left + 1<<' '<<right + 1<<' '<<ans;
}
