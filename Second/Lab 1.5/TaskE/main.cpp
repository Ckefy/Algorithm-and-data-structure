#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct node {
    node *l, *r;
    ll key, prior, sum;
    node(){}
    node (ll key, ll prior) : l(nullptr), r(nullptr), key (key), prior (prior), sum(key){};
};

ll getSize (node* now){
    return (now == nullptr) ? 0 : now -> sum;
}

void reSum (node* now){
    if (now == nullptr){
        return;
    }
    now -> sum = getSize(now -> l) + getSize(now -> r) + now -> key;
}

node* root = nullptr;

pair < node*, node* > split (node* now, ll key){
    if (now == nullptr){
            return (make_pair(nullptr, nullptr));
    } else if (key <= now -> key){
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
    } else {
        tree2 -> l = merge (tree1, tree2 -> l);
        reSum (tree2);
        return tree2;
    }
}

set <ll> randed;

ll getrand() {
    return rand();
}

node* insert (node* now, ll key){
    pair < node*, node* > splited = split (now, key);
    node* newRoot = new node (key, getrand());
    newRoot = merge(splited.first, newRoot);
    newRoot = merge (newRoot, split(splited.second, key + 1).second);
    return newRoot;
}

ll query (node* now, ll l, ll r){
    pair < node*, node* > splited1 = split (now, l);
    pair < node*, node* > splited2 = split (splited1.second, r + 1);
    ll ans = splited2.first == nullptr? 0 : splited2.first -> sum;
    root = merge(merge(splited1.first, splited2.first), splited2.second);
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    char type;
    cin>>n;
    ll last = 0;
    bool flag = true;
    for (ll i = 0; i < n; i++){
        cin>>type;
        if (type == '+'){
            ll value;
            cin>>value;
            if (!flag){
                root = insert (root, (value + last) % 1000000000);
                flag = true;
            } else {
                root = insert (root, value);
            }
        } else {
            ll l, r;
            cin>>l>>r;
            ll ans = query (root, l, r);
            last = ans;
            flag = false;
            cout<<ans<<"\n";
        }
    }
}
