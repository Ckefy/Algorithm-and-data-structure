#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll maxFilled = 0;
vector <ll> answerArr;


struct node {
    node *l, *r;
    ll value, prior, sum;
    node(){}
    node (ll value, ll prior, ll sum0) : l(nullptr), r(nullptr), key (key), prior (prior), sum(1){};
};

random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000000);

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
        tree1 -> sum0 = (tree1 -> key == 0) ? 1 : 0;
        reSum (tree1);
        return tree1;
    }
    if (tree1 -> prior < tree2 -> prior){
        tree2 -> l = merge (tree1, tree2 -> l);
        tree2 -> sum0 = (tree2 -> key == 0) ? 1 : 0;
        reSum (tree2);
        return tree2;
    }
}

ll getrand() {
    return dis(gen);
}

node* insert (node* now, ll key){
    pair < node*, node* > splited = split (now, key);
    node* newRoot = new node (0, getrand(), 1);
    newRoot = merge(splited.first, newRoot);
    newRoot = merge (newRoot, splited.second);
    return newRoot;
}

int main()
{
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    ll n, m;
    cin>>n>>m;
    root = new node(0, getrand(), 1);
    for (ll i = 1; i <= n + m; i++){
        root = insert (root, i + 1);
    }
    maxFilled = n;
    for (ll i = 1; i <= n; i++){
        ll l;
        cin>>l;
        swaps(l, i);
    }
    cout<<maxFilled<<endl;
    makeOrder(root);
    for (ll i = 0; i < maxFilled; i++){
        cout<<answerArr[i]<<' ';
    }
}
