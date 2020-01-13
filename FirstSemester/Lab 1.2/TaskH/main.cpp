#include <bits/stdc++.h>

using namespace std;

struct troi{
    int id;
    int size;
};

vector <troi> p;
vector <long long> xp;
vector <long long> delay;

int getid (int x){
    if (x == p[x].id){
        return x;
    } else {
        return getid (p[x].id);
    }
}

 void add (int x1, int v){
    int adressx = getid(x1);
    delay[adressx] += v;
 }

void join (int x1, int y1){
    int adressy = getid(y1);
    int adressx = getid(x1);
    troi y = p[adressy];
    troi x = p[adressx];
    if (x.id != y.id){
        if (x.size > y.size){
            swap (x, y);
        }
        y.size += x.size;
        p[adressx] = y;
        delay[adressx] = delay[adressx] - delay[adressy];
    }
}

long long getxp (int x1){
    long long ans = 0;
    while (x1 != p[x1].id){
        ans += delay[x1];
        x1 = p[x1].id;
    }
    ans += delay[x1];
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin>>n>>m;
    p.resize(n);
    xp.resize(n);
    delay.resize(n);
    for (int i = 0; i < n; i++){
        troi now;
        now.id = i;
        now.size = 1;
        xp[i] = 0;
        p[i] = now;
        delay[i] = 0;
    }
    string s;
    for (int i = 0; i < m; i++){
        cin>>s;
        if (s == "add"){
            int x;
            long long v;
            cin>>x>>v;
            x--;
            add (x, v);
        } else if (s == "join"){
            int x, y;
            cin>>x>>y;
            x--;
            y--;
            join(x, y);
        } else {
            int x;
            cin>>x;
            x--;
            cout<<getxp(x)<<endl;
        }
    }
}
