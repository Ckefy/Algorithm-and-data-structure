#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct quartet{
    quartet(): first(1), second(0), third(0), fourth(1){};
    int first;
    int second;
    int third;
    int fourth;
};
quartet natural;
int r, n, m;
vector <quartet> t;
vector <quartet> a;

quartet mulMatrix (quartet firstArg, quartet secondArg){
    quartet result;
    result.first = ((firstArg.first * secondArg.first) % r + (firstArg.second * secondArg.third) % r) % r; //1.1
    result.second = ((firstArg.first * secondArg.second) % r + (firstArg.second * secondArg.fourth) % r) % r; //1.2
    result.third = ((firstArg.third * secondArg.first) % r + (firstArg.fourth * secondArg.third) % r) % r; //2.1
    result.fourth = ((firstArg.third * secondArg.second) % r + (firstArg.fourth * secondArg.fourth) % r) % r; //2.2
    return result;
}

void makeTree (int l, int r, int v){
    if (r - l == 1){
        t[v] = a[l];
    } else {
        int m = (l + r)/2;
        makeTree(l, m, 2 * v + 1);
        makeTree(m, r, 2 * v + 2);
        t[v] = mulMatrix(t[v * 2 + 1], t[v * 2 + 2]);
    }
}

quartet getMultiply (int l, int r, int needl, int needr, int v){
    if (needr <= l || needl >= r){
        return natural;
    }
    if (l >= needl && r <= needr){
        return t[v];
    }
    int m = (l + r) / 2;
    return mulMatrix(getMultiply(l, m, needl, needr, 2 * v + 1), getMultiply (m, r, needl, needr, 2 * v + 2));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream f1 ("crypto.in");
    ofstream f2 ("crypto.out");
    f1>>r>>n>>m;
    a.resize(n);
    t.resize(4 * n, natural);
    for (int i = 0; i < n; i++){
        quartet now;
        f1>>now.first>>now.second>>now.third>>now.fourth;
        a[i] = now;
    }
    makeTree(0, n, 0);
    int kek, kek2;
    for (int i = 0; i < m; i++){
        f1>>kek>>kek2;
        quartet ans = getMultiply (0, n, kek - 1, kek2, 0);
        f2<<ans.first<<" "<<ans.second<<"\n";
        f2<<ans.third<<" "<<ans.fourth<<"\n";
        f2<<"\n";
    }
    f1.close();
    f2.close();
    return 0;
}
