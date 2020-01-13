#include <bits/stdc++.h>
#define ll long long

using namespace std;

struct myType{
    ll sum;
    ll counts;
    ll delay;
    ll pre;
    ll post;
};

ll peace = -1;//нейтральный

ll n;
vector <myType> t;

void makeTree (long long l, long long r, long long v){
    if (r - l == 1){
        t[v].sum = 0; //белая
        t[v].counts = 0;
        t[v].delay = peace;
        t[v].pre = 0;
        t[v].post = 0;
    } else {
        long long m = (l + r) / 2;
        makeTree(l, m, 2 * v + 1);
        makeTree(m, r, 2 * v + 2);
        t[v].sum = 0;
        t[v].counts = 0;
        t[v].delay = peace;
        t[v].pre = 0;
        t[v].post = 0;
    }
}

void push (ll v, ll l, ll r){
    if (t[v].delay != peace){
            t[2 * v + 1].delay = t[v].delay;
            t[2 * v + 2].delay = t[v].delay;
            t[2 * v + 1].pre = t[v].delay;
            t[2 * v + 1].post = t[v].delay;
            t[2 * v + 1].counts = t[v].delay;
            t[2 * v + 2].pre = t[v].delay;
            t[2 * v + 2].post = t[v].delay;
            t[2 * v + 2].counts = t[v].delay;
            t[v].pre = t[v].delay;
            t[v].post = t[v].delay;
            t[v].counts = t[v].delay;
    } else {
        if (t[2 * v + 1].delay != peace){
            t[2 * v + 1].counts = t[2 * v + 1].delay;
            t[2 * v + 1].pre = t[2 * v + 1].delay;
            t[2 * v + 1].post = t[2 * v + 1].delay;
        }
        if (t[2 * v + 2].delay != peace){
            t[2 * v + 2].counts = t[2 * v + 2].delay;
            t[2 * v + 2].pre = t[2 * v + 2].delay;
            t[2 * v + 2].post = t[2 * v + 2].delay;
        }
        t[v].pre = t[2 * v + 1].pre;
        t[v].post = t[2 * v + 2].post;
            t[v].counts = t[2 * v + 1].counts + t[2 * v + 2].counts;
            if (t[2 * v + 1].post == t[2 * v + 2].pre){
                if (t[2 * v + 1].post == 1){
                    t[v].counts--;
                }
            }
    }

    t[v].delay = peace;

    ll m = (l + r) / 2;
    ll trueValueLeft, trueValueRight;
        if (t[2 * v + 1].delay == peace){
            trueValueLeft = t[2 * v + 1].sum;
        } else{
            trueValueLeft = (m - l) * t[2 * v + 1].delay; //количество элементов
        }
        if (t[2 * v + 2].delay == peace){
            trueValueRight = t[2 * v + 2].sum;
        } else{
            trueValueRight = (r - m) * t[2 * v + 2].delay; //количество элементов
        }
        t[v].sum = trueValueLeft + trueValueRight;
}

void update(ll v, ll l, ll r, ll needl, ll needr, ll value){
     if (needr <= l || needl >= r){
            return;
        }
        if (l >= needl && r <= needr){
            t[v].delay = value;
            t[v].sum = (r - l) * value;
            t[v].counts = value;
            t[v].pre = value;
            t[v].post = value;
            return;
        }
        push(v, l, r);
        ll m = (l + r) / 2;
        update (2 * v + 1, l, m, needl, needr, value);
        update (2 * v + 2, m, r, needl, needr, value);
        ll trueValueLeft, trueValueRight;
        if (t[2 * v + 1].delay == peace){
            trueValueLeft = t[2 * v + 1].sum;
        } else{
            trueValueLeft = (m - l) * t[2 * v + 1].delay; //количество элементов
        }
        if (t[2 * v + 2].delay == peace){
            trueValueRight = t[2 * v + 2].sum;
        } else{
            trueValueRight = (r - m) * t[2 * v + 2].delay; //количество элементов
        }
        t[v].sum = trueValueLeft + trueValueRight;

        if (t[v].delay == peace) {
            if (t[2 * v + 1].delay != peace){
                t[2 * v + 1].counts = t[2 * v + 1].delay;
                t[2 * v + 1].pre = t[2 * v + 1].delay;
                t[2 * v + 1].post = t[2 * v + 1].delay;
            }
            if (t[2 * v + 2].delay != peace){
                t[2 * v + 2].counts = t[2 * v + 2].delay;
                t[2 * v + 2].pre = t[2 * v + 2].delay;
                t[2 * v + 2].post = t[2 * v + 2].delay;
            }
                t[v].counts = t[2 * v + 1].counts + t[2 * v + 2].counts;
                if (t[2 * v + 1].post == t[2 * v + 2].pre){
                    if (t[2 * v + 1].post == 1){
                        t[v].counts--;
                    }
                }
            t[v].pre = t[2 * v + 1].pre;
            t[v].post = t[2 * v + 2].post;
        } else {
            t[v].counts = t[v].delay;
            t[v].pre = t[v].delay;
            t[v].post = t[v].delay;
        }
}

ll answerSum (ll v, ll l, ll r, ll needl, ll needr){
    if (needr <= l || needl >= r){
            return 0;
        }
    if (l >= needl && r <= needr){
        if (t[v].delay == peace){
            return t[v].sum;
        } else{
            return ((r - l) * t[v].delay); //количество элементов
        }
    }
    push(v, l, r);
    ll m = (l + r) / 2;
    ll ans = answerSum(2 * v + 1, l, m, needl, needr) + answerSum(2 * v + 2, m, r, needl, needr);
    return ans;
}

ll answerCounts (ll v, ll l, ll r, ll needl, ll needr){
    if (needr <= l || needl >= r){
            return 0;
        }
    if (l >= needl && r <= needr){
        if (t[v].delay == peace){
            return t[v].counts;
        } else{
            return t[v].delay;
        }
    }
    push(v, l, r);
    ll m = (l + r) / 2;
    ll ans = answerCounts(2 * v + 1, l, m, needl, needr) + answerCounts(2 * v + 2, m, r, needl, needr);
     if (t[2 * v + 1].post == t[2 * v + 2].pre){
        if (t[2 * v + 1].post == 1)
            ans--;
    }
    return ans;
}

int main()
{
    n = 1000002;
    t.resize(4 * n);
    makeTree(0, n, 0);
    int k;
    cin>>k;
    char c;
    long long first, second;
    for (int i = 0; i < k; i++){
        cin>>c;
        cin>>first>>second;
        first += 500000;
        if (c == 'W'){
            update (0, 0, n, first, first + second, 0);
            cout<<answerCounts(0, 0, n, 0, n)<<' '<<answerSum(0, 0, n, 0, n)<<endl;
        } else {
            update (0, 0, n, first, first + second, 1);
            cout<<answerCounts(0, 0, n, 0, n)<<' '<<answerSum(0, 0, n, 0, n)<<endl;
        }
    }
}


