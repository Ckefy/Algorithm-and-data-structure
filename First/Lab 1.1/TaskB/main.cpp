#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{
    vector <int> a (101);
    int elem;
    while (cin>>elem){
        a[elem]++;
    }
    for (int i = 0; i < 101; i++){
        if  (a[i] == 0){
            continue;
        }
        for (int j = 0; j < a[i]; j++){
            cout<<i<<' ';
        }
    }
}
