#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    int n;
    cin>>n;
    ll mod = 1000000000;
    vector < vector < ll > > a (10, vector < ll > (n));
    for (int i = 0; i < 10; i++){
        if (i == 0 || i == 8){
            a[i][0] = 0; //длиной 1
        } else {
            a[i][0] = 1;
        }
    }
    for (int i = 1; i < n; i++){
        a[0][i] = (a[4][i - 1] % mod + a[6][i - 1] % mod) % mod;
        a[1][i] = (a[6][i - 1] % mod + a[8][i - 1] % mod) % mod;
        a[2][i] = (a[7][i - 1] % mod + a[9][i - 1] % mod) % mod;
        a[3][i] = (a[4][i - 1] % mod + a[8][i - 1] % mod) % mod;
        a[4][i] = (a[0][i - 1] % mod + a[3][i - 1] % mod + a[9][i - 1]% mod) % mod;
        a[5][i] = 0;
        a[6][i] = (a[0][i - 1] % mod + a[1][i - 1] % mod + a[7][i - 1] % mod) % mod;
        a[7][i] = (a[2][i - 1] % mod + a[6][i - 1] % mod) % mod;
        a[8][i] = (a[1][i - 1] % mod + a[3][i - 1] % mod) % mod;
        a[9][i] = (a[2][i - 1] % mod + a[4][i - 1] % mod) % mod;
    }
    ll ans = 0;
    for (int i = 0; i < 10; i++){
        ans += (a[i][n - 1]);
        ans %= mod;
    }
    cout<<ans<<endl;
}
