#include <bits/stdc++.h>
#define ll long long

using namespace std;

struct myType{
    ll value;
    ll delay0;
    ll delay1;
};

ll peace = LONG_LONG_MAX;//нейтральный

ll n;
vector <myType> t;
vector <ll> a;

void makeTree (long long l, long long r, long long v){
    if (r - l == 1){
        t[v].value = a[l];
        t[v].delay0 = peace;
        t[v].delay1 = peace;
    } else {
        long long m = (l + r) / 2;
        makeTree(l, m, 2 * v + 1);
        makeTree(m, r, 2 * v + 2);
        t[v].value = min(t[v * 2 + 1].value, t[v * 2 + 2].value);
        t[v].delay0 = peace;
        t[v].delay1 = peace;
    }
}

void push (ll v){
    if (t[v].delay0 != peace){
            t[2 * v + 1].delay0 = t[v].delay0;
            t[2 * v + 1].delay1 = peace;
    } else {
        if (t[2 * v + 1].delay0 != peace){
            if (t[v].delay1 != peace){
                    t[2 * v + 1].delay0 += t[v].delay1;
            }
        } else if (t[v].delay1 != peace){
            if (t[2 * v + 1].delay1 != peace){
                t[2 * v + 1].delay1 += t[v].delay1;
            } else {
                t[2 * v + 1].delay1 = t[v].delay1;
            }
        }
    }

    if (t[v].delay0 != peace){
            t[2 * v + 2].delay0 = t[v].delay0;
            t[2 * v + 2].delay1 = peace;
    } else {
        if (t[2 * v + 2].delay0 != peace){
            if (t[v].delay1 != peace){
                    t[2 * v + 2].delay0 += t[v].delay1;
            }
        } else if (t[v].delay1 != peace){
            if (t[2 * v + 2].delay1 != peace){
                t[2 * v + 2].delay1 += t[v].delay1;
            } else {
                t[2 * v + 2].delay1 = t[v].delay1;
            }
        }
    }

    t[v].delay0 = peace;
    t[v].delay1 = peace;
}

void update(ll v, ll l, ll r, ll needl, ll needr, ll value, bool mode){ //0 - set, 1 - add
    if (!mode){
        if (needr <= l || needl >= r){
            return;
        }
        if (l >= needl && r <= needr){
            t[v].delay0 = value;
            t[v].delay1 = peace;
            return;
        }
        push (v);
        ll m = (l + r) / 2;
        update (2 * v + 1, l, m, needl, needr, value, mode);
        update (2 * v + 2, m, r, needl, needr, value, mode);
        ll trueValueLeft, trueValueRight;
        if (t[2 * v + 1].delay0 == peace){
            if (t[2 * v + 1].delay1 == peace){
                    trueValueLeft = t[2 * v + 1].value;
            } else {
                trueValueLeft = t[2 * v + 1].value + t[2 * v + 1].delay1;
            }
        } else {
            trueValueLeft = t[2 * v + 1].delay0;
        }
        if (t[2 * v + 2].delay0 == peace){
            if (t[2 * v + 2].delay1 == peace){
                    trueValueRight = t[2 * v + 2].value;
            } else {
                trueValueRight = t[2 * v + 2].value + t[2 * v + 2].delay1;
            }
        } else {
            trueValueRight = t[2 * v + 2].delay0;
        }
        t[v].value = min(trueValueLeft, trueValueRight);
    } else {
        if (needr <= l || needl >= r){
            return;
        }
        if (l >= needl && r <= needr){
            if (t[v].delay0 != peace){
                    t[v].delay0 += value;
            } else {
                if (t[v].delay1 != peace){
                        t[v].delay1 += value;
                } else {
                    t[v].delay1 = value;
                }
            }
            return;
        }
        push (v);
        ll m = (l + r) / 2;
        update (2 * v + 1, l, m, needl, needr, value, mode);
        update (2 * v + 2, m, r, needl, needr, value, mode);
        //Пересчет
        ll trueValueLeft, trueValueRight;
        if (t[2 * v + 1].delay0 == peace){
            if (t[2 * v + 1].delay1 == peace){
                    trueValueLeft = t[2 * v + 1].value;
            } else {
                trueValueLeft = t[2 * v + 1].value + t[2 * v + 1].delay1;
            }
        } else {
            trueValueLeft = t[2 * v + 1].delay0;
        }

        if (t[2 * v + 2].delay0 == peace){
            if (t[2 * v + 2].delay1 == peace){
                    trueValueRight = t[2 * v + 2].value;
            } else {
                trueValueRight = t[2 * v + 2].value + t[2 * v + 2].delay1;
            }
        } else {
            trueValueRight = t[2 * v + 2].delay0;
        }
        t[v].value = min(trueValueLeft, trueValueRight);
    }
}

ll answer (ll v, ll l, ll r, ll needl, ll needr){
    if (needr <= l || needl >= r){
            return peace;
        }
    if (l >= needl && r <= needr){
        if (t[v].delay0 == peace){
            if (t[v].delay1 == peace){
                return t[v].value;
            } else {
                return (t[v].value + t[v].delay1);
            }
        } else {
                return t[v].delay0;
        }
    }
    ////
    push (v);
    ////
    ll m = (l + r) / 2;
    ll ans = min (answer(2 * v + 1, l, m, needl, needr), answer(2 * v + 2, m, r, needl, needr));
    //Пересчет
    ll trueValueLeft, trueValueRight;
        if (t[2 * v + 1].delay0 == peace){
            if (t[2 * v + 1].delay1 == peace){
                    trueValueLeft = t[2 * v + 1].value;
            } else {
                trueValueLeft = t[2 * v + 1].value + t[2 * v + 1].delay1;
            }
        } else {
            trueValueLeft = t[2 * v + 1].delay0;
        }
        if (t[2 * v + 2].delay0 == peace){
            if (t[2 * v + 2].delay1 == peace){
                    trueValueRight = t[2 * v + 2].value;
            } else {
                trueValueRight = t[2 * v + 2].value + t[2 * v + 2].delay1;
            }
        } else {
            trueValueRight = t[2 * v + 2].delay0;
        }
        t[v].value = min(trueValueLeft, trueValueRight);
    return ans;
}

int main()
{
    cin>>n;
    a.resize(n);
    t.resize(4 * n);
    for (int i = 0; i < n; i++){
        cin>>a[i];
    }
    makeTree(0, n, 0);
    string s;
    while(cin>>s){
        long long first, second, third;
        cin>>first>>second;
        first--;
        second--;
        if (s[1] != 'i'){
            cin>>third;
        }
        if (s[1] == 'e'){
            update(0, 0, n, first, second + 1, third, 0);
        } else if (s[1] == 'd'){
            update(0, 0, n, first, second + 1, third, 1);
        } else {
            cout<<answer(0, 0, n, first, second + 1)<<endl;
        }
    }
}


