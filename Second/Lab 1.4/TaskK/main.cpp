#include <bits/stdc++.h>

using namespace std;

int n;
int peace = INT_MAX;
vector <int> t, pos;

void makeTree (int l, int r, int v){
    if (r - l == 1){
        t[v] = 0;
        pos[v] = l;
    } else {
        int m = (l + r)/2;
        makeTree(l, m, 2 * v + 1);
        makeTree(m, r, 2 * v + 2);
        t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
    }
}

void setValue (int l, int r, int v, int need, int value){
    if (r - l == 1){
        t[v] = value;
        return;
    }
    int m = (l + r)/ 2;
   (need < m) ? setValue (l, m, 2 * v + 1, need, value) : setValue (m, r, 2 * v + 2, need, value);
    t[v] = min(t[2 * v + 1], t[2 * v + 2]);
}

int lfs (int l, int r, int needl, int needr, int v){
    if (needr <= l || needl >= r || t[v] == 1){
        return peace;
    }
    if (r - l == 1){
        return pos[v];
    }
    int m = (l + r) / 2;
    int ans = lfs(l, m, needl, needr, 2 * v + 1);
    return (ans == peace ? lfs(m, r, needl, needr, 2 * v + 2) : ans);
}

int main()
{
    ifstream f1("parking.in");
    ofstream f2("parking.out");
    f1>>n;
    pos.resize(4 * n);
    t.resize(4 * n, peace);
    makeTree(0, n, 0);
    int m;
    f1>>m;
    string s;
    int place;
    for (int i = 0; i < m; i++){
        f1>>s>>place;
        place--;
        if (s[1] == 'n'){
            int ans = lfs (0, n, place, n, 0);
            ans = (ans == peace ? lfs(0, n, 0, place, 0) + 1 : ans + 1);
            f2<<ans<<"\n";
            setValue(0, n, 0, ans - 1, 1);
        } else {
            setValue(0, n, 0, place, 0);
        }
    }
    f1.close();
    f2.close();
}
