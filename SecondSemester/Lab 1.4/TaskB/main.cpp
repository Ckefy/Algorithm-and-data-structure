#include <bits/stdc++.h>

using namespace std;

long long n;
vector <long long> t, a;

void makeTree (long long l, long long r, long long v){
    if (r - l == 1){
        t[v] = a[l];
    } else {
        long long m = (l + r)/2;
        makeTree(l, m, 2 * v + 1);
        makeTree(m, r, 2 * v + 2);
        t[v] = t[v * 2 + 1] + t[v * 2 + 2];
    }
}

void setValue (long long l, long long r, long long v, long long need, long long value){
    if (r - l == 1){
        t[v] = value;
        return;
    }
    long long m = (l + r)/ 2;
    (need < m) ? setValue (l, m, 2 * v + 1, need, value) : setValue (m, r, 2 * v + 2, need, value);
    t[v] = t[2 * v + 1] + t[2 * v + 2];
}

long long sum (long long l, long long r, long long needl, long long needr, long long v){
    if (needr <= l || needl >= r){
        return 0;
    }
    if (l >= needl && r <= needr){
        return t[v];
    }
    long long m = (l + r) / 2;
    return (sum(l, m, needl, needr, 2 * v + 1) + sum (m, r, needl, needr, 2 * v + 2));
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
        long long first, second;
        cin>>first>>second;
        if (s[1] == 'e'){
            setValue(0, n, 0, first - 1, second);
        } else {
             cout<<sum (0, n, first - 1, second, 0)<<endl;
        }
    }
}
