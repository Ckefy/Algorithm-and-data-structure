#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll w, h, n;

bool check (ll m){
    ll row, column;
    row = m/w;
    column = m/h;
    return (row*column >= n);
}

ll binSearch (ll l, ll r){
    while (r > l+1){
        ll m = (l + (r - l)/2);
        if (check(m)){
            r = m;
        } else {
            l = m;
        }
    }
    return (check(l) ? l : r);
}

int main()
{
   cin>>w>>h>>n;
   ll l = 0, r = max (w*n, h*n) + 1;
   cout<<binSearch (l, r);
}
