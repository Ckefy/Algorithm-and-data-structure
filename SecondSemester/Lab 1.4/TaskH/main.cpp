#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll n;
ll peace = LONG_LONG_MAX;
vector <ll> t, a;
vector < pair < ll, pair < ll, ll > > > smth;
vector < pair < ll, pair < ll, ll > > > tree; //для чека дерева

void makeTree (long long l, long long r, long long v){
    if (r - l == 1){
        t[v] = a[l];
    } else {
        long long m = (l + r)/2;
        makeTree(l, m, 2 * v + 1);
        makeTree(m, r, 2 * v + 2);
        t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
    }
}

ll getMin (ll l, ll r, ll needl, ll needr, ll v){
    if (needr <= l || needl >= r){
        return peace;
    }
    if (l >= needl && r <= needr){
        return t[v];
    }
    ll m = (l + r) / 2;
    return min(getMin(l, m, needl, needr, 2 * v + 1), getMin (m, r, needl, needr, 2 * v + 2));
}

int main()
{
    ll m;
    ifstream f1("rmq.in");
    ofstream f2("rmq.out");
    f1>>n>>m;
    a.resize(n, peace);
    t.resize(4 * n, peace);
    for (ll i = 0; i < m; i++){
        ll left, right, mini;
        f1>>left>>right>>mini;
        left--; //left включительно, right нет
        pair < ll, pair < ll, ll > > now;

        now.first = left;
        now.second.second = mini;
        now.second.first = 1; //open
        smth.push_back(now);

        now.first = right;
        now.second.second = mini;
        now.second.first = -1; //close
        smth.push_back(now);

        now.first = mini;
        now.second.first = left;
        now.second.second = right - 1;
        tree.push_back(now);
    }
    sort(smth.begin(), smth.end());
    multiset <ll> events;
    ll nowMax = peace;
    ll jstart = 0, jfinish;
    for (ll i = 0; i < smth.size(); i++){
        if (smth[i].second.first == 1){
            jfinish = smth[i].first;
            for (ll k = jstart; k < jfinish; k++){
                a[k] = nowMax;
            }
            jstart = jfinish;

            events.insert(smth[i].second.second);
            multiset <ll> :: iterator it = events.end();
            it--;
            nowMax = *it;
        } else {
            jfinish = smth[i].first;
            for (ll k = jstart; k < jfinish; k++){
                a[k] = nowMax;
            }
            jstart = jfinish;
            multiset <ll> :: iterator found = events.find(smth[i].second.second);
            events.erase(found);
            if (events.empty()) nowMax = peace;
                else {
                        multiset <ll> :: iterator it = events.end();
                        it--;
                        nowMax = *it;
                }
        }
    }
    makeTree(0, n, 0);
    for (ll i = 0; i < m; i++){
        if (getMin(0, n, tree[i].second.first, tree[i].second.second + 1, 0) != tree[i].first){
            f2<<"inconsistent";
            return 0;
        }
    }
    f2<<"consistent"<<"\n";
    for (ll i = 0; i < n; i++){
        if (a[i] != peace){
                f2<<a[i]<<' ';
        } else {
            f2<<0<<' ';
        }
    }
    f1.close();
    f2.close();
}
