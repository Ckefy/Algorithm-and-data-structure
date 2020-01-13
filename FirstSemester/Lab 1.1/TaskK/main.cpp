#include <bits/stdc++.h>
#define ll long long

using namespace std;

struct kbest{
    ll v, w, index;
    double coef;
};

vector <kbest> a;
double e = 0.000001;
int n, k;

//дихотоми€

void mergesort (int n)
{
    int i1, i2;
    int step=1; //какой длины сейчас массивчики
    vector <kbest> temp;
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
                if (a[i1].coef<a[i2].coef)
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

double check (double m){
    for (int i = 0; i < n; i++){
        a[i].coef = m*a[i].w - a[i].v;
    }
    mergesort (n);
    double ans = 0;
    for (int i = 0; i < k; i++){
        ans+=a[i].coef;
    }
    return ans;
}

int main()
{
    ifstream f1 ("kbest.in");
    f1>>n>>k;
    a.resize (n);
    for (int i = 0; i < n; i++){
        f1>>a[i].v>>a[i].w;
        a[i].index = i;
    }
    double l = 0, r = 1e8;
    while (r - l > e){
        double m = l + (r - l)/2;
        if (check (m) > 0){
            r = m;
        } else {
            l = m;
        }
    }
    ofstream f2 ("kbest.out");
    for (int i = 0; i < k; i++){
        f2<<a[i].index+1<<endl;
    }
}
