#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector <ll> a;
int n;

int funclb (int i, ll x){
    if (a[i] <= x){
        return 0;
    } else {
        return 1;
    }
}

int lower_b (ll x){ //для r
    int l = -1;
    int r = n;
    while (r > l + 1){
        int m = (r + l)/2;
        if (funclb(m, x) == 0){
            l = m;
        } else {
            r = m;
        }
    }
    return (((r < n) && (funclb(r, x) == 0))? r : l);
}


int funcub (int i, ll x){
    if (a[i] < x){
        return 0;
    } else {
        return 1;
    }
}

int upper_b (ll x){ //для l
    int l = -1;
    int r = n;
    while (r > l + 1){
        int m = (r + l)/2;
        if (funcub(m, x) == 0){
            l = m;
        } else {
            r = m;
        }
    }
    if ((l >= 0) && (a[l]==x)){
        return l;
    }
    if ((r < n) && (a[r]==x)){
        return r;
    }
    return (((l >= 0) && (funcub(l,x) == 1))? l : r);
}

int main()
{
    int k = 0;
    cin>>n>>k;
    a.resize(n);
    for (int i = 0; i < n; i++){
        cin>>a[i];
    }
    vector <ll> b (k);
    for (int i = 0; i < k; i++){
        cin>>b[i];
    }
    for (int i = 0; i < k; i++){
        ll x = b[i];
        ll lower = a[lower_b(x)], upper = a[upper_b(x)];
        cout<<((abs(lower-x) <= abs(upper-x)) ? lower : upper)<<endl;
    }
}
