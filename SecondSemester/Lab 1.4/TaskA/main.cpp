#include <bits/stdc++.h>
#define ll unsigned long long

using namespace std;

int main()
{
    long long n, x, y;
    ll a0;
    cin>>n>>x>>y>>a0;
    vector <ll> a(n);
    a[0] = a0;
    ll mod1 = 1 << 16;
    for (int i = 1; i < n; i++){
        a[i] = (x * a[i - 1] + y) % mod1;
    }
    for (int i = 1; i < n; i++){
        a[i] += a[i - 1];
    }
    long long m, z, t;
    ll b0, b1, c0, c1;
    cin>>m>>z>>t>>b0;
    ll mod2 = 1 << 30;
    b0 %= mod2;
    b1 = (z * b0 + t) % mod2;
    ll ans = 0;
    for (int i = 0; i < m; i++){
        c0 = b0 % n;
        c1 = b1 % n;
        ll mini = min(c0, c1);
        ll maxi = max(c0, c1);
        if (mini == 0){
            ans += a[maxi];
        } else {
            ans += (a[maxi] - a[mini - 1]);
        }
        b0 = (z * b1 + t) % mod2;
        b1 = (z * b0 + t) % mod2;
    }
    cout<<ans;
}
