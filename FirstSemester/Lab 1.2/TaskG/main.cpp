#include <bits/stdc++.h>

using namespace std;

struct troi{
    int max;
    int min;
    int value;
    int size;
};

vector <troi> p;

int get (int x){
    if (x == p[x].value){
        return x;
    } else {
        return get (p[x].value);
    }
}

void join (int x1, int y1){
    troi now;
    troi y = p[get(y1)];
    troi x = p[get(x1)];
    if (x.value != y.value){
        now.value = y.value;
        now.min = min (y.min, x.min);
        now.max = max (y.max, x.max);
        now.size = y.size + x.size;
        p[x1] = now;
        p[y1] = now;
    }
}

int main()
{
    int n;
    cin>>n;
    p.resize(n);
    for (int i = 0; i < n; i++){
        troi now;
        now.value = i;
        now.min = i + 1;
        now.max = i + 1;
        now.size = 1;
        p[i] = now;
    }
    string s;
    while (cin>>s){
        if (s[0] == 'u'){
            int a, b;
            cin>>a>>b;
            a--; b--;
            join (get(a), get(b));
        } else {
            int a;
            cin>>a;
            a--;
            int y = get(a);
            cout<<p[y].min<<' '<<p[y].max<<' '<<p[y].size<<endl;
        }
    }
}
