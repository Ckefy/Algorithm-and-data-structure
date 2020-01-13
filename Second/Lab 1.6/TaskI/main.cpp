#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define mp make_pair
#define whole quest.begin(), quest.end()

using namespace std;

struct Operation{
    ll parent, kid;
    bool wasNewEvr;
    Operation(ll parent, ll kid, bool wasNewEvr) : parent(parent), kid(kid), wasNewEvr(wasNewEvr){}
};

ll n, npow2 = 1;
vector <Operation> operations;
vector <ll> p, evr, size1;
map < pair < ll,  ll >, vector < ll > > link, cut;
vector < pair < ll, ll > > quest;
vector < vector < pair < ll, ll > > > tree;

void initialize(){
    tree.resize(npow2 * 2);
    p.resize(n);
    evr.resize(n);
    size1.resize(n);
    for (ll i = 0; i < n; i++){
        p[i] = i;
        evr[i] = 0;
        size1[i] = 1;
    }
}

ll root (ll now){
    if (p[now] != now){
        return root(p[now]);
    }
    return now;
}

void open_operation (ll now, ll l, ll r, ll needl, ll needr, pair <ll, ll> value){
    if (needr < l || needl > r){
        return;
    }
    if (needl <= l && needr >= r){
        tree[now].pb(value);
        return;
    }
    ll m = l + (r - l) / 2;
    open_operation (2 * now , l, m, needl, needr, value);
    open_operation (2 * now + 1, m + 1, r, needl, needr, value);
}

void close_operation(){
    Operation now = operations.back();
    operations.pop_back();
    p[now.kid] = now.kid;
    size1[now.parent] -= size1[now.kid];
    if (now.wasNewEvr){
        --evr[now.parent];
    }
}

void accept_operation (pair <ll, ll> value){
    ll first = value.first, second = value.second;
    ll parent1 = root(first), parent2 = root(second);
    bool newEvr = false;
    if (evr[parent1] == evr[parent2]){
        newEvr = true;
        evr[parent1]++;
    }
    if (evr[parent2] > evr[parent1]){
        p[parent1] = parent2;
        size1[parent2] += size1[parent1];
        operations.pb(Operation(parent2, parent1, newEvr));
    } else {
        p[parent2] = parent1;
        size1[parent1] += size1[parent2];
        operations.pb(Operation(parent1, parent2, newEvr));
    }
}

bool get_answer(ll now){
    for (pair <ll, ll> value : tree[now]){
        accept_operation(value);
    }
    if (now >= npow2){
        if (now - npow2 >= quest.size()){
            return false;
        }
        cout<<size1[root(quest[now - npow2].second)]<<endl;
    } else {
        if (!get_answer(2 * now) || !get_answer(2 * now + 1)){
            return false;
        }
    }
    for (ll i = 0; i < tree[now].size(); i++){
        close_operation();
    }
    return true;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll m, smth = 0;
    cin>>n>>m;
    while (npow2 <= n && npow2 < 4){
        npow2 *= 2;
    }
    initialize();
    string s;
    ll first, second;
    for (ll i = 0; i < m; i++){
        cin>>s;
        if (s != "size"){
            cin>>first>>second;
            first--; second--;
            if (first > second) swap (first, second);
            if (s == "link") {
                    link[mp(first, second)].pb(i);
            } else {
                cut[mp(first, second)].pb(i);
            }
        } else {
            cin>>first;
            first--;
            quest.pb(mp(i, first));
        }
    }
    if (quest.size() == 0){
        return 0;
    }
    for (auto i : link){
        vector <ll> linkNow = i.second;
        vector <ll> cutNow = cut[i.first];
        ll cSize = cutNow.size(), lSize = linkNow.size();
        if (cSize != lSize){
            cutNow.pb(m);
            cSize++;
        }
        for (ll j = 0; j < lSize; j++){
            ll start = lower_bound(whole, mp(linkNow[j], smth)) - quest.begin();
            ll finish = lower_bound(whole, mp(cutNow[j], smth)) - quest.begin();
            finish--;
            open_operation (1, 0, npow2 - 1, start, finish, i.first);
        }
    }
    get_answer(1);
}
