#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct myType{
    ll value;
    ll index;
    ll delay;
};

ll inf = -1;//LONG_LONG_MIN;

ll n;
vector <myType> t;
vector <ll> a;

void makeTree (ll l, ll r, ll v){
    if (r - l == 1){
        t[v].value = 0;
        t[v].delay = 0;
        t[v].index = l;
    } else {
        long long m = (l + r) / 2;
        makeTree(l, m, 2 * v + 1);
        makeTree(m, r, 2 * v + 2);
        t[v].value = max(t[v * 2 + 1].value, t[v * 2 + 2].value);
        t[v].delay = 0;
        t[v].index = ((t[v].value == t[v * 2 + 1].value) ? t[v * 2 + 1].index : t[v * 2 + 2].index);
    }
}

void push (ll v){
    t[2 * v + 1].delay += t[v].delay;
    t[2 * v + 2].delay += t[v].delay;
    t[v].delay = 0;
    ll valueLeft = t[2 * v + 1].value + t[2 * v + 1].delay;
    ll valueRight = t[2 * v + 2].value + t[2 * v + 2].delay;
    t[v].value = max (valueLeft, valueRight);
    t[v].index = ((t[v].value == valueLeft) ? t[v * 2 + 1].index : t[v * 2 + 2].index);
}

void update(ll v, ll l, ll r, ll needl, ll needr, ll value){
        if (needr <= l || needl >= r){
            return;
        }
        if (r - l == 1){
            t[v].value += (value + t[v].delay);
            t[v].delay = 0;
            return;
        }
        if (l >= needl && r <= needr){
            t[v].delay += value;
            push(v);
            return;
        }
        push (v);
        ll m = (l + r) / 2;
        update (2 * v + 1, l, m, needl, needr, value);
        update (2 * v + 2, m, r, needl, needr, value);
        ll valueLeft = t[2 * v + 1].value + t[2 * v + 1].delay;
        ll valueRight = t[2 * v + 2].value + t[2 * v + 2].delay;
        t[v].value = max (valueLeft, valueRight);
        t[v].index = ((t[v].value == valueLeft) ? t[v * 2 + 1].index : t[v * 2 + 2].index);
}

pair <ll, ll> answer (ll v, ll l, ll r, ll needl, ll needr){
    if (needr <= l || needl >= r){
            return make_pair(inf, inf);
        }
    if (r - l == 1){
        ll trueValue = t[v].delay + t[v].value;
        return make_pair(trueValue, t[v].index);
    }
    if (l >= needl && r <= needr){
        push(v);
        return make_pair(t[v].value, t[v].index);
    }
    push (v);
    ll m = (l + r) / 2;
    pair <ll, ll> left = answer(2 * v + 1, l, m, needl, needr);
    pair <ll, ll> right = answer(2 * v + 2, m, r, needl, needr);
    pair <ll, ll> ans = (left.first > right.first ? left : right);
    return ans;
}


int main()
{
    ll m;
    cin>>m;
    n = 2 * m;
    a.resize(n);
    t.resize(4 * n);
    vector < pair < pair < ll, ll >, pair < ll, ll > > > smth;
    set <ll> setY;
    for (ll i = 0; i < m; i++){
        pair < pair < ll, ll >, pair < ll, ll > > now;
        ll x1, x2, y1, y2;
        cin>>x1>>y1>>x2>>y2;
        now.first.first = x1;
        now.first.second = -1; //open;
        now.second.first = y1;
        now.second.second = y2;
        smth.push_back(now);
        now.first.first = x2;
        now.first.second = 1; //close;
        now.second.first = y1;
        now.second.second = y2;
        smth.push_back(now);
        setY.insert(y1);
        setY.insert(y2);
    }
    sort(smth.begin(), smth.end());
    vector <ll> arrY;
    for (set<ll>::iterator it = setY.begin(); it != setY.end(); it++){
        arrY.push_back(*it);
    }
    makeTree(0, arrY.size(), 0);
    ll maxi = inf, maxindexX, maxindexY;
    for (ll i = 0; i < smth.size(); i++){
        vector<ll>::iterator it = lower_bound(arrY.begin(), arrY.end(), smth[i].second.first);
        ll left = distance(arrY.begin(), it);
        it = lower_bound(arrY.begin(), arrY.end(), smth[i].second.second);
        ll right = distance(arrY.begin(), it);
        right++;
        if (smth[i].first.second == -1){
             update(0, 0, arrY.size(), left, right, 1);
        } else {
            update(0, 0, arrY.size(), left, right, -1);
        }
        pair <ll,ll> ans = answer(0, 0, arrY.size(), 0, arrY.size());
        if (ans.first > maxi){
            maxi = ans.first;
            maxindexX = smth[i].first.first;
            maxindexY = ans.second;
        }
    }
    cout<<maxi<<"\n"<<maxindexX<<' '<<arrY[maxindexY];
}
