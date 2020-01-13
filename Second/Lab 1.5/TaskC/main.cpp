#include <bits/stdc++.h>
#define ll int

using namespace std;

vector < pair < ll, pair < ll, ll > > > pool;

struct node {
    node *l, *r, *parent;
    ll key, prior, number;
    node(){}
    node (ll key, ll prior, ll number) : l(nullptr), r(nullptr), parent(nullptr), key (key), prior (prior), number (number){};
};

struct myType {
    ll first, second, third;
    myType(){}
    myType (ll first, ll second, ll third) : first(first), second(second), third(third){};
};

vector <myType> answer;

node* root = nullptr;

pair < node*, node* > split (node* now, ll key){
    if (now == nullptr){
            return (make_pair(nullptr, nullptr));
    } else if (key < now -> key){
        pair < node*, node* > splited = split (now -> l, key);
        now -> l = splited.second;
        return (make_pair (splited.first, now));
    } else {
        pair < node*, node* > splited = split (now -> r, key);
        now -> r = splited.first;
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
    if (tree1 -> prior < tree2 -> prior){
        tree1 -> r = merge (tree1 -> r, tree2);
        return tree1;
    }
    if (tree1 -> prior > tree2 -> prior){
        tree2 -> l = merge (tree1, tree2 -> l);
        return tree2;
    }
}

node* insert (ll key, ll prior, ll number){
    pair < node*, node* > splited = split (root, key);
    node* newRoot = new node (key, prior, number);
    newRoot = merge(splited.first, newRoot);
    newRoot = merge (newRoot, splited.second);
    return newRoot;
}

void printTree (node* cur, ll parent){
    myType* nowAns = new myType (parent, ((cur -> l == nullptr) ? 0 : cur -> l -> number), ((cur -> r == nullptr) ? 0 : cur -> r -> number));
    //cout<<nowAns -> first<<' '<<nowAns -> second<<' '<<nowAns -> third<<endl;
    answer[cur -> number - 1] = *nowAns;
   if (cur -> l != nullptr){
        printTree (cur -> l, cur -> number);
    }
    if (cur -> r != nullptr){
        printTree (cur -> r, cur -> number);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin>>n;
    answer.resize(n);
    for (int i = 0; i < n; i++){
        pair < ll, pair < ll, ll > > now;
        cin>>now.first;
        cin>>now.second.first;
        now.second.second = i + 1;
        pool.push_back(now);
    }
    sort (pool.begin(), pool.end());
    root = new node (pool[0].first, pool[0].second.first, pool[0].second.second);
    node* previous = root;
    for (int i = 1; i < n; i++){
        bool flag = false;
        int x = pool[i].first;
        int y = pool[i].second.first;
        if (previous -> prior < y){
            previous -> r = new node (x, y, pool[i].second.second);
            previous -> r -> parent = previous;
            previous = previous -> r;
            continue;
        }
        while (previous -> prior > y){
            if (previous -> parent != nullptr){
                previous = previous -> parent;
            } else {
                node* now = new node (x, y, pool[i].second.second);
                now -> l = previous;
                now -> l -> parent = now;
                previous = now;
                root = now;
                flag = true;
                break;
            }
        }
        if (flag)
            continue;
        node* now = new node (x, y, pool[i].second.second);
        now -> l = previous -> r;
        now -> l -> parent = now;
        now -> parent = previous;
        previous -> r = now;
        previous = now;
    }
    cout<<"YES"<<"\n";
    printTree (root, 0);
    for (int i = 0; i< n; i++){
        cout<<answer[i].first<<' '<<answer[i].second<<' '<<answer[i].third<<"\n";
    }
}
