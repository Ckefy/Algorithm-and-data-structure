#include <bits/stdc++.h>
#define ll int
#define pb push_back

using namespace std;

vector < vector < ll > > g;
vector <bool> was;
vector <ll> p;
vector <ll> depth;
vector <ll> subtreeSz;
vector <ll> root;
vector <ll> numerate;

ll n;

void initialize_array(){
    g.resize(n);
    was.resize(n);
    p.resize(n);
    depth.resize(n);
    subtreeSz.resize(n);
    root.resize(n);
    numerate.resize(n);
}

ll indexNow = -1;
void make_lhd(ll now, ll rooting){
    numerate[now] = ++indexNow;
    root[now] = rooting;
    ll maxi, maxind;
    maxi = -1; maxind = -1;
    for (auto to = g[now].begin(); to != g[now].end(); to++){
        if (maxi < subtreeSz[*to] && p[now] != *to){
            maxi = subtreeSz[*to];
            maxind = *to;
        }
    }
    if (maxi == -1) return;
    make_lhd(maxind, rooting);
    for (auto to = g[now].begin(); to != g[now].end(); to++){
        if (maxind != *to && p[now] != *to){
            make_lhd(*to, *to);
        }
    }
}

ll make_subtreeSz (ll now){
    subtreeSz[now] = 1;
    for (auto to = g[now].begin(); to != g[now].end(); to++){
        if (p[now] != *to){
            subtreeSz[now] += make_subtreeSz(*to);
        }
    }
    return subtreeSz[now];
}

void make_tree(ll now){
    if (!was[now]){
        was[now] = true;
        for (auto to = g[now].begin(); to != g[now].end(); to++){
            if (!was[*to]){
                p[*to] = now;
                depth[*to] = depth[now] + 1;
                make_tree(*to);
            }
        }
    }
}

void initialize_lhd(){
    cin>>n;
    initialize_array();
    ll now1, now2;
    for (ll i = 0; i < n - 1; i++){
        cin>>now1>>now2;
        now1--; now2--;
        g[now1].pb(now2);
        g[now2].pb(now1);
    }
    p[0] = 0;
    depth[0] = 0;
    make_tree(0);
    make_subtreeSz(0);
    make_lhd(0, 0);

}

struct node {
    long long delay;
    node() : delay(0){}
};

vector <node> tree;

long long query_main(ll now, ll l, ll r, ll index){
    if (l == index && r == index){
        return tree[now].delay;
    }
    ll m = l + (r - l) / 2;
    if (m < index){
        return tree[now].delay + query_main(2 * now + 1, m + 1, r, index);
    } else {
        return tree[now].delay + query_main(2 * now, l, m, index);
    }
}

long long query (ll index){
    return query_main(1, 0, n - 1, index);
}

void modify_main (ll now, ll l, ll r, ll needl, ll needr, long long value){
    if (needl > needr){
        return;
    }
    if (needl == l && needr == r){
        tree[now].delay += value;
        return;
    }
    ll m = l + (r - l) / 2;
    modify_main(2 * now, l, m, needl, min(m, needr), value);
    modify_main(2 * now + 1, m + 1, r, max(needl, m + 1), needr, value);
}

void modify (ll l, ll r, long long value){
    while (root[l] != root[r]){
        if (depth[root[l]] < depth[root[r]]) {
                swap (l, r);
        }
        ll first = numerate[root[l]], second = numerate[l];
        modify_main(1, 0, n - 1, min(first, second), max(first, second), value);
        l = p[root[l]];
    }
    modify_main(1, 0, n - 1, min(numerate[l], numerate[r]), max(numerate[l], numerate[r]), value);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    initialize_lhd();
    tree.resize(4 * n);
    ll m;
    cin>>m;
    char symb;
    for (ll i = 0; i < m; i++){
        cin>>symb;
        if (symb == '?'){
            ll index;
            cin>>index;
            cout<<query(numerate[index - 1])<<endl;
        } else {
            ll first, second, value;
            cin>>first>>second>>value;
            first--; second--;
            modify(first, second, value);
        }
    }
}
