#include <bits/stdc++.h>
#define ll long long

using namespace std;

double c, e = 0.0000001;

double f (double x){
    return (pow(x,2)+pow(x,0.5)-c);
}

double findRight(){
    double r = 1;
    while (f(r) < 0){
        r*=2;
    }
    return r;
}

int main()
{
    cin>>c;
    double l = 0, r = findRight();
    double m = (l + r)/2;
    setprecision (6);
    while (abs(f(m)) > e){
        if (f(r) == 0 || f(l) == 0){
            cout<<fixed<<(f(r) == 0 ? r : l)<<endl;
            return 0;
        }
        if (f(l)*f(m) < 0){
            r = m;
        } else if (f(r)*f(m) < 0) {
            l = m;
        }
        m = (l + r)/2;
    }
    cout<<fixed<<m<<endl;
}
