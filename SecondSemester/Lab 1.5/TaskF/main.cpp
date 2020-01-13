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
    } else if (key >= now -> key){
        pair < node*, node* > splited = split (now -> l, key);
        now -> l = splited.second;
        reSum (now);
        return (make_pair (splited.first, now));
    } else {
        pair < node*, node* > splited = split (now -> r, key);
        now -> r = splited.first;
        reSum (now);
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
    for (ll i = 0; i < 1000; i++){
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

node* del (node* now, ll x){
    pair < node*, node* > splited = split (now, x);
    return merge (splited.first, split(splited.second, x - 1).second);
}

ll findK(node* now, ll k) {
    while (now != nullptr) {
        ll was = getSize(now -> l);
        if (was == k) {
            return now -> key;
        }
        now = was > k ? now -> l : now -> r;
        if (was < k) {
            k-= was + 1;
        }
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin>>n;
    for (ll i = 0; i < n; i++){
        ll first, second;
        cin>>first>>second;
        if (first == 0){
            cout<<findK(root, second - 1)<<"\n";
        } else if (first == 1){
            root = insert(root, second);
        } else {
            root = del(root, second);
        }
    }
}
close
