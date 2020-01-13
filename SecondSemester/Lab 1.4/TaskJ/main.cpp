#include <bits/stdc++.h>
#define ll long long

using namespace std;

struct myType{
    ll value;
    ll index;
    ll delay;
};

ll peace = LONG_LONG_MAX;//нейтральный

ll n;
vector <myType> t;
vector <ll> a;

void makeTree (long long l, long long r, long long v){
    if (r - l == 1){
        t[v].value = a[l];
        t[v].delay = peace;
        t[v].index = l;
    } else {
        long long m = (l + r) / 2;
        makeTree(l, m, 2 * v + 1);
        makeTree(m, r, 2 * v + 2);
        t[v].value = min(t[v * 2 + 1].value, t[v * 2 + 2].value);
        t[v].delay = peace;
        t[v].index = ((t[v].value == t[v * 2 + 1].value) ? t[v * 2 + 1].index : t[v * 2 + 2].index);
    }
}

void push (ll v){
    //cout<<t[v].delay<<' '<<t[2 * v + 1].delay<<' '<<t[2 * v + 2].delay<<endl;
    t[2 * v + 1].delay = ((t[v].delay == peace || (t[v].delay <= t[2 * v + 1].delay && t[2 * v + 1].delay != peace)) ? t[2 * v + 1].delay : t[v].delay);
    t[2 * v + 2].delay = ((t[v].delay == peace || (t[v].delay <= t[2 * v + 2].delay && t[2 * v + 2].delay != peace)) ? t[2 * v + 2].delay : t[v].delay);
    t[v].delay = peace;
    //cout<<t[v].delay<<' '<<t[2 * v + 1].delay<<' '<<t[2 * v + 2].delay<<endl;
    ll valueLeft = ((t[2 * v + 1].delay == peace || t[2 * v + 1].value >= t[2 * v + 1].delay) ? t[2 * v + 1].value : t[2 * v + 1].delay);
    ll valueRight = ((t[2 * v + 2].delay == peace || t[2 * v + 2].value >= t[2 * v + 2].delay) ? t[2 * v + 2].value : t[2 * v + 2].delay);
    t[v].value = min (valueLeft, valueRight);
    /////
    t[v].index = ((t[v].value == valueLeft) ? t[v * 2 + 1].index : t[v * 2 + 2].index);
}

void update(ll v, ll l, ll r, ll needl, ll needr, ll value){
        if (needr <= l || needl >= r){
            return;
        }
        if (r - l == 1){
            t[v].delay = ((value <= t[v].delay && t[v].delay != peace) ? t[v].delay : value);
            t[v].value = ((t[v].delay == peace || t[v].value >= t[v].delay) ? t[v].value : t[v].delay);
            return;
        }
        if (l >= needl && r <= needr){
            t[v].delay = ((value <= t[v].delay && t[v].delay != peace) ? t[v].delay : value);
            push(v);
            return;
        }
        push (v);
        ll m = (l + r) / 2;
        update (2 * v + 1, l, m, needl, needr, value);
        update (2 * v + 2, m, r, needl, needr, value);
        ll valueLeft = ((t[2 * v + 1].delay == peace || t[2 * v + 1].value >= t[2 * v + 1].delay) ? t[2 * v + 1].value : t[2 * v + 1].delay);
        ll valueRight = ((t[2 * v + 2].delay == peace || t[2 * v + 2].value >= t[2 * v + 2].delay) ? t[2 * v + 2].value : t[2 * v + 2].delay);
        t[v].value = min (valueLeft, valueRight);
        t[v].index = ((t[v].value == valueLeft) ? t[v * 2 + 1].index : t[v * 2 + 2].index);
}

pair <ll, ll> answer (ll v, ll l, ll r, ll needl, ll needr){
    if (needr <= l || needl >= r){
            return make_pair(peace, peace);
        }
    if (r - l == 1){
        ll trueValue = ((t[v].delay == peace || t[v].value >= t[v].delay) ? t[v].value : t[v].delay);
        return make_pair(trueValue, t[v].index);
    }
    if (l >= needl && r <= needr){
        ////
        push(v);
        ////
        return make_pair(t[v].value, t[v].index);
    }
    push (v);
    ll m = (l + r) / 2;
    pair <ll, ll> left = answer(2 * v + 1, l, m, needl, needr);
    pair <ll, ll> right = answer(2 * v + 2, m, r, needl, needr);
    pair <ll, ll> ans = (left.first < right.first ? left : right);
    return ans;
}

int main()
{
    ll m;
    cin>>n>>m;
    a.resize(n, 0);
    t.resize(4 * n);
    makeTree(0, n, 0);
    string s;
    for (ll i = 0; i < m; i++){
        cin>>s;
        long long first, second, third;
        if (s[0] == 'd'){
                cin>>first>>second>>third;
                first--;
                update(0, 0, n, first, second, third);
        } else {
            cin>>first>>second;
            first--;
            pair <ll, ll> ans = answer(0, 0, n, first, second);
            if (ans.second < first)
                ans.second++;
            else if (ans.second > second){
                ans.second--;
            }
            cout<<ans.first<<' '<<ans.second + 1<<endl;
        }
    }
}


