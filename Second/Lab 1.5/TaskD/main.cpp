#include <bits/stdc++.h>

using namespace std;
#define ll long long
typedef struct node{
    node* l=nullptr;
    node* r=nullptr;
    node* p=nullptr;
    ll x, y;
    ll c=1;
    bool rev=false;
    bool cycle=false;
};
typedef node* pnode;
ll length=0;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 5000000);

ll getC(pnode v){
    if (v==nullptr) return 0;
    return v->c;
}
void updateC(pnode v){
    if (v==nullptr) return;
    v->c=getC(v->l)+getC(v->r)+1;
    if (v->l!=nullptr) v->l->p=v;
    if (v->r!=nullptr) v->r->p=v;
}
void makeRev(pnode v){
    if(v==nullptr) return;
    if (!v->rev) return;
    v->rev=false;
    if(v->l!=nullptr){
        if (v->r!=nullptr){
            pnode help=v->r;
            v->r=v->l;
            v->l=help;
            v->l->rev=!(v->l->rev);
            v->r->rev=!(v->r->rev);
        } else{
            v->r=v->l;
            v->r->rev=!(v->r->rev);
        }
    } else{
        if (v->r!=nullptr){
            v->l=v->r;
            v->l->rev=!(v->l->rev);
        }
    }
}
pair<pnode, pnode> split(pnode v, ll x){
    if (v==nullptr) return make_pair(nullptr, nullptr);
    makeRev(v);
    ll l=getC(v->l);
    if (l<x){
        pair<pnode, pnode> help = split(v->r, x-l-1);
        if (v->r!=nullptr) v->r->p=nullptr;
        v->r=help.first;
        if (v->r!=nullptr) v->r->p=v;
        updateC(v);
        updateC(help.second);
        return make_pair(v, help.second);
    } else{
        pair<pnode, pnode> help = split(v->l, x);
        if (v->l!=nullptr) v->l->p=nullptr;
        v->l=help.second;
        if (v->l!=nullptr) v->l->p=v;
        updateC(v);
        updateC(help.first);
        return make_pair(help.first, v);
    }
}
pnode merging(pnode l, pnode r){
    if (l==nullptr) return r;
    if (r==nullptr) return l;
    makeRev(l);
    makeRev(r);
    if (r->y>l->y){
        r->l=merging(l, r->l);
        updateC(r);
        return r;
    } else{
        l->r=merging(l->r, r);
        updateC(l);
        return l;
    }
}

pnode getRoot(pnode v){
    if (v->p!=nullptr){
        return getRoot(v->p);
    }
    return v;
}
ll getNumber(pnode now){
    int ans = 1;
        if (now -> l != nullptr) {
            ans += now -> l -> x;
        }
        if (now -> isTransposed) {
            ans = now -> x - ans + 1;
        } //in case it`s the right kid for real
        while (now -> parent != nullptr) {
            if (now -> parent -> isTransposed) {
                ans = now -> x - ans + 1;
                transpose(now -> parent);
                continue;
            }
            if (now == now -> parent -> r) {
                ans += 1 + (now -> parent -> l == null ? 0 : now.parent -> l -> x);
            }
            now = no -> parent;
        }
        return ans - 1;
}

bool getPosition(pnode v){
    if (getNumber(v)==0) return true;
    return false;
    //true-left false-right
    /*pnode root=getRoot(v);
    while (true){
        if (root->rev){
            makeRev(root);
        }
        if (root->l==nullptr) return root==v;
        root=root->l;
    }
    */
}
void makeRoad(pnode x, pnode y){
    pnode rootX=getRoot(x);
    pnode rootY=getRoot(y);
    if (rootX==rootY) rootX->cycle=true;
    else{
        if (rootX==x && rootY==y) {merging(x, y); return;}
        if (rootX==x){
            if (getPosition(y)){merging(x, y); return;}
            merging(y, x); return;
        } else{
            if (rootY==y){
                if (getPosition(x)){merging(y, x); return;}
                merging(x, y); return;
            } else{
                if (getPosition(y)){
                    if (!getPosition(x)) {merging(x, y); return;}
                    rootX->rev=!(rootX->rev);
                    merging(x, y); return;
                } else{
                    if (getPosition(x)) {merging(y, x); return;}
                    rootY->rev=!(rootY->rev);
                    merging(x, y); return;
                }
            }
        }
    }
}

void unCycle(pnode v){
    if (v==nullptr) return;
    v->cycle=false;
}
void ripRoad(pnode x, pnode y){
    pnode root=getRoot(x);
    ll numX=getNumber(x);
    ll numY=getNumber(y);
    if (root->cycle){
        root->cycle=false;
        if ((numX==0 && numY==(root->c-1)) || (numY==0 && numX==(root->c-1))){
            return;
        } else{
            pair <pnode, pnode> help=split(root, min(numX, numY)+1);
            unCycle(help.first);
            unCycle(help.second);
            merging(help.second, help.first);
            return;
        }
    } else{
        pair <pnode, pnode> help=split(root, min(numX, numY)+1);
        unCycle(help.first);
        unCycle(help.second);
    }
}

void ans(pnode x, pnode y){
    if (x==y){cout<<"0"<<endl; return;}
    pnode rootX=getRoot(x);
    pnode rootY=getRoot(y);
    cout<<rootX->x<<" "<<rootY->x<<endl;
    if (rootX!=rootY) {cout<<"-1"<<endl; return;}
    cout<<"was"<<endl;
    ll numX=getNumber(x);
    ll numY=getNumber(y);
    if (rootX->cycle) cout<<(min(abs(numX-numY), rootX->c-abs(numX-numY))-1)<<endl;
    else cout<<abs(numX-numY)-1<<endl;
}

int main(){
    ll n, m, q;
    cin>>n>>m>>q;
    vector <pnode> city(n);
    for (ll i=1; i<n+1; i++){
        city[i-1]=new node;
        city[i-1]->x=i;
        city[i-1]->y=dis(gen);
    }
    ll x,y;
    for (ll i=0; i<m; i++){
        cin>>x>>y;
        x--; y--;
        makeRoad(city[x], city[y]);
    }
    string s;
    for (ll i=0; i<q; i++){
        cin>>s;
        cin>>x>>y;
        x--; y--;
        if (s=="?"){
            ans(city[x], city[y]);
        }
        if (s=="-"){
            ripRoad(city[x], city[y]);
        }
        if (s=="+"){
            makeRoad(city[x], city[y]);
        }
    }
    return 0;
}
