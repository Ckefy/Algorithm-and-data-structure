#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector <ll> a;
int n;

void mergesort (int n)
{
    int i1, i2;
    int step=1; //какой длины сейчас массивчики
    vector <ll> temp;
    while (step<n)
    {
        int left=0, mid=left+step, right=left+2*step; //левый край левого, левый край центрального и за правым краем правого
        temp.resize (0);
        while (left<n)
        {
            mid=min(mid,n); //это чтобы крч не выходило за рамки
            right=min(right,n);
            i1=left, i2=mid;
            while (i1<mid && i2<right)
                if (a[i1]<a[i2])
                {
                    temp.push_back (a[i1]);
                    i1++;
                }
                else
                {
                    temp.push_back (a[i2]);
                    i2++;
                }
            while (i1<mid)
            {
                temp.push_back(a[i1]);
                i1++;
            }
            while (i2<right)
            {
                temp.push_back(a[i2]);
                i2++;
            }
            left+=2*step;
            right+=2*step;
            mid+=2*step;
        }
        for (int i=0; i<n; i++)
            a[i]=temp[i];
        step*=2;
    }
}

int funclb (int i, ll x){
    if (a[i] <= x){
        return 0;
    } else {
        return 1;
    }
}

int lower_b (ll x){ //для r
    int l = -1;
    int r = n;
    while (r > l + 1){
        int m = (r + l)/2;
        if (funclb(m, x) == 0){
            l = m;
        } else {
            r = m;
        }
    }
    return (((r < n) && (funclb(r, x) == 0))? r : l);
}


int funcub (int i, ll x){
    if (a[i] < x){
        return 0;
    } else {
        return 1;
    }
}

int upper_b (ll x){ //для l
    int l = -1;
    int r = n;
    while (r > l + 1){
        int m = (r + l)/2;
        if (funcub(m, x) == 0){
            l = m;
        } else {
            r = m;
        }
    }
    if ((l >= 0) && (a[l]==x)){
        return l;
    }
    if ((r < n) && (a[r]==x)){
        return r;
    }
    return (((l >= 0) && (funcub(l,x) == 1))? l : r);
}

int main()
{
    cin>>n;
    a.resize(n);
    for (int i = 0; i < n; i++){
        cin>>a[i];
    }
    mergesort (n);
    int k;
    cin>>k;
    ll a1, b;
    for (int i = 0; i < k; i++){
        cin>>a1>>b;
        cout<<lower_b(b)-upper_b(a1)+1<<endl;
    }
}
