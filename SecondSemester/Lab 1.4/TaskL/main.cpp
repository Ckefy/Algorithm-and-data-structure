#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll n;
vector < vector < vector < ll > > > f;

ll sum (ll x, ll y, ll z){
    ll answer = 0;
    for (ll i = x; i >= 0; i = (i & (i + 1)) - 1){
        for (ll j = y; j >= 0; j = (j & (j + 1)) - 1){
            for (ll k = z; k >= 0; k = (k & (k + 1)) - 1){
                answer += f[i][j][k];
            }
        }
    }
    return answer;
}

ll ourSum (ll x1, ll y1, ll z1, ll x2, ll y2, ll z2){
    ll all = sum (x2, y2, z2);
    ll down_all;
    ll all_far;
    ll all_right;
    ll all_corner;
    ll down_far;
    ll down_right;
    ll down_corner;
    if (z1 != 0){
        down_all = -1 * sum(x2, y2, z1 - 1);
    } else {
        down_all = 0;
    }
    if (x1 != 0){
        all_far = -1 * sum(x1 - 1, y2, z2);
    } else{
        all_far = 0;
    }
    if (y1 != 0){
        all_right = -1 * sum(x2, y1 - 1, z2);
    } else {
        all_right = 0;
    }
    if (x1 != 0 && y1 != 0){
        all_corner = sum(x1 - 1, y1 - 1, z2);
    } else {
        all_corner = 0;
    }
    if (x1 != 0 && z1 != 0){
        down_far = sum(x1 - 1, y2, z1 - 1);
    } else {
        down_far = 0;
    }
    if (y1 != 0 && z1 != 0){
        down_right = sum(x2, y1 - 1, z1 - 1);
    } else {
        down_right = 0;
    }
    if (x1 != 0 && y1 != 0 && z1 != 0){
        down_corner = -1 * sum(x1 - 1, y1 - 1, z1 - 1);
    } else {
        down_corner = 0;
    }
    return (all + down_all + all_far + all_right + all_corner + down_far + down_right + down_corner);
}

void add (ll x, ll y, ll z, ll value){
    for (ll i = x; i < n; i = (i | (i + 1))){
        for (ll j = y; j < n; j = (j | (j + 1))){
            for (ll k = z; k < n; k = (k | (k + 1))){
                f[i][j][k] += value;
            }
        }
    }
}

int main()
{
    cin>>n;
    f.resize(n);
    for (ll i = 0; i < n; i++){
        f[i].resize(n);
        for (ll j = 0; j < n; j++){
            f[i][j].resize(n, 0);
        }
    }
    int mode;
    while (cin>>mode){
        if (mode == 3){
            return 0;
        }
        if (mode == 2){
            ll x1, y1, z1, x2, y2, z2;
            cin>>x1>>y1>>z1>>x2>>y2>>z2;
            cout<<ourSum(x1, y1, z1, x2, y2, z2)<<endl;
        } else if (mode == 1){
            ll x, y, z, k;
            cin>>x>>y>>z>>k;
            add(x, y, z, k);
        }
    }
}
