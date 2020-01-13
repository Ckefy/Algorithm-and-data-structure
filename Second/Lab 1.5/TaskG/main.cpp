#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct node {
    node *l, *r;
    ll key, prior, sum;
    node(){}
    node (ll key, ll prior) : l(nullptr), r(nullptr), key (key), prior (prior), sum(1){};
};

ll getSize (node* now){
    return (now == nullptr) ? 0 : now -> sum;
}

void reSum (node* now){
    if (now == nullptr){
        return;
    }
    now -> sum = getSize(now -> l) + getSize(now -> r) + 1;
}

node* root = nullptr;

pair < node*, node* > split (node* now, ll key){
    if (now == nullptr){
            return (make_pair(nullptr, nullptr));
    } else if (key <= getSize(now -> l)){
        pair < node*, node* > splited = split (now -> l, key);
        now -> l = splited.second;
        reSum (now);
        reSum (splited.first);
        return (make_pair (splited.first, now));
    } else {
        pair < node*, node* > splited = split (now -> r, key - getSize(now -> l) - 1);
        now -> r = splited.first;
        reSum (now);
        reSum(splited.second);
        return (make_pair (now, splited.second));
    }
}

node* merge (node* tree1, node* tree2){
    if (tree1 == nullptr){
        return tree2;
    }
    if (tree2 == nullptr){
        return tree1;
    }
    if (tree1 -> prior > tree2 -> prior){
        tree1 -> r = merge (tree1 -> r, tree2);
        reSum (tree1);
        return tree1;
    }
    if (tree1 -> prior < tree2 -> prior){
        tree2 -> l = merge (tree1, tree2 -> l);
        reSum (tree2);
        return tree2;
    }
}

set <ll> randed;

ll getrand() {
    ll ans = 0;
    for (ll i = 0; i < 5000; i++){
        ans += rand();
    }
    if (randed.find(ans) == randed.end()){
            randed.insert (ans);
            return ans;
        }
    else {
        randed.insert(ans + 100);
        return ans + 100;
    }
}

node* insert (node* now, ll key){
    pair < node*, node* > splited = split (now, key);
    node* newRoot = new node (key, getrand());
    newRoot = merge(splited.first, newRoot);
    newRoot = merge (newRoot, splited.second);
    return newRoot;
}

void swaps(ll l, ll r) {
    pair< node*, node* > splited = split(root, l - 1);
    pair< node*, node* > splited2 = split(splited.second, r - l + 1);
    root = merge(merge(splited2.first, splited.first), splited2.second);
    reSum (root);
}

void makeOrder (node* now){
    if (now != nullptr){
        makeOrder(now -> l);
        cout<<now -> key<<' ';
        makeOrder(now -> r);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, m;
    cin>>n>>m;
    root = new node(1, getrand());
    for (ll i = 1; i < n; i++){
        root = insert (root, i + 1);
    }
    for (ll i = 0; i < m; i++){
        ll l, r;
        cin>>l>>r;
        swaps(l, r);
    }
    makeOrder(root);
}
