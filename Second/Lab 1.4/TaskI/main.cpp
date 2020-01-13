#include <bits/stdc++.h>
#define ll int
using namespace std;

struct myTree {
    ll left;
    ll right;
    ll value;
    ll sum;
    ll maxi;
    bool isTrue;
    myTree *toLeft = nullptr;
    myTree *toRight = nullptr;
};

ll n;
myTree *root;

void push (myTree *v){
    ll m = (v -> left + v -> right) / 2;
    if (v -> toLeft == nullptr){
        myTree *now = new myTree;
        now -> left = v -> left;
        now -> right = m;
        now -> value = v -> value;
        now -> sum = now -> maxi = v -> value * (m - v -> left + 1);
        now -> isTrue =  true;
        v -> toLeft = now;

        myTree *now1 = new myTree;
        now1 -> left = m + 1;
        now1 -> right = v -> right;
        now1 -> value = v -> value;
        now1 -> sum = now1 -> maxi = v -> value * (v -> right - m);
        now1 -> isTrue = true;
        v -> toRight = now1;

        v -> isTrue = false; //теперь актуальное в детях лежит
    } else if (v -> isTrue){
        v -> toLeft -> maxi = v -> toLeft -> sum = v -> value * (v -> toLeft -> right - v -> toLeft -> left + 1);
        v -> toLeft -> value = v -> value;
        v -> toLeft -> isTrue = true;

        v -> toRight -> maxi = v -> toRight -> sum = v -> value * (v -> toRight -> right - v -> toRight -> left + 1);
        v -> toRight -> value = v -> value;
        v -> toRight -> isTrue = true;

        v -> isTrue = false;
    }
}

void add (myTree *v, ll needl, ll needr, ll value){
    ll l = v -> left;
    ll r = v -> right;
    if (r < needl || l > needr){
        return;
    }
    if (l >= needl && r <= needr){
        v -> maxi = v -> sum = value * (r - l + 1);
        v -> isTrue = true;
        v -> value = value;
        return;
    }
    push(v);
    add(v -> toLeft, needl, needr, value);
    add(v -> toRight, needl, needr, value);
    v -> maxi = max (v -> toLeft -> maxi, v -> toLeft -> sum + v -> toRight -> maxi);
    v -> sum = v -> toLeft -> sum + v -> toRight -> sum;
}

ll ans (myTree *v, ll h){
    if (v -> left == v -> right){
        return v -> left - 1;
    }
    push (v);
    if (v -> toLeft -> maxi > h){
        return ans (v -> toLeft, h);
    }
    return ans (v -> toRight, h - v -> toLeft -> sum);
}
void print(myTree *v){
    cout<<v->left<<" "<<v->right<<" "<<v->value<<" "<<v->maxi<<" "<<v->isTrue<<endl;
    if (v->toLeft!=nullptr) print(v->toLeft);
    if (v->toRight!=nullptr) print(v->toRight);
}
int main()
{
 //   ios_base::sync_with_stdio(false);
   // cin.tie(NULL);
    cin>>n;
    root = new myTree;
    root -> left = 1;
    root -> right = n;
    root -> isTrue = true;
    root -> maxi = 0;
    root -> sum = 0;
    root -> value = 0;
    root -> toLeft = nullptr;
    root -> toRight = nullptr;
    string s;
    while (cin>>s){
        print(root);
        if (s[0] == 'I'){
            ll needl, needr, value;
            cin>>needl>>needr>>value;
            add (root, needl, needr, value);
        } else if (s[0] == 'Q'){
            ll h;
            cin>>h;
            //if (h >= root -> maxi){
              //  cout<<n<<"\n";
            //} else {
                cout<<ans(root, h)<<"\n";
            //}
        } else {
            return 0;
        }
    }
}
