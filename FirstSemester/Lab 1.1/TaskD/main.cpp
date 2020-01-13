#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector <ll> a;
ll n=0;

void insert (ll x){
    n++;
    if (a.size()==0 || n - 1 > a.size() - 1){
        a.push_back(x);
    } else{
        a[n-1] = x;
    }
    int i = n - 1;
    while (i > 0 && a[(i - 1)/2] < a[i]){
        swap (a[i], a[(i - 1)/2]);
        i = (i - 1)/2;
    }
}

ll extract (){
    ll ans = a[0];
    swap (a[0], a[n - 1]);
    n--;
    int i = 0, j;
    while (2*i +1 < n){
        j = 2*i+1;
        if (j+1 < n && a[j + 1] > a [j]){
            j++;
        } //есди есть ребенок еще одиг и он больше, то берем его
        if (a[j] > a[i]){
            swap (a[j], a[i]);
            i = j;
        } else {
            break;
        }
    }
    return ans;
}

int main()
{
    int count_of_oper, oper, x;
    cin>>count_of_oper;
    for (int i = 0; i < count_of_oper; i++){
        cin>>oper;
        if (oper == 0){
            cin>>x;
            insert (x);
        } else {
            cout<<extract()<<endl;
        }
    }
}
