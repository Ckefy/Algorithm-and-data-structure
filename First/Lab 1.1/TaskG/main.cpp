#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll n, pretime = 0, best;
int x, y;
ll old = -1, now;

ll binSearch (ll l, ll r){
    while (r > l+1){
        ll m = (l + (r - l)/2);
        now = max(x * m, y * (n - m));
        if (old == -1){
            old = now + 1;
            best = now;
        }
        best = min (min (now, old), best);
        if (now == x*m && old < now){
            old = now;
            r = m;
        } else if (now == y*(n - m) && old < now) {
            old = now;
            l = m;
        } else if (now == x*m) {
            r=m;
        } else if (now == y*(n - m)) {
            l=m;
        }
    }
    return best;
}

int main()
{
    cin>>n>>x>>y;
    if (x > y){ //х теперь меньший
        swap (x, y);
    }
    pretime+=x;
    n--;
    ll ans = pretime + binSearch (-1, n+1);
    cout<<ans;
}
