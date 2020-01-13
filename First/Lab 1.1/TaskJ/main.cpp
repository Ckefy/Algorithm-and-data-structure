#include <bits/stdc++.h>
#define ll long long
#define double long double

using namespace std;

double vp, vf;
double a, old = -1, e = 0.0001;;

double times (double m){
    double field, forest;
    forest = pow(pow (m - 1, 2) + pow (a, 2), 0.5);
    field = pow(pow (m, 2) + pow (1 - a, 2), 0.5);
    return (field/vp + forest/vf);
}

double binSearch (double l, double r){
    while (r - l > e){
        double m1 = (2*l + r)/3, m2 = (l + 2*r)/3;
        if (times (m1) < times (m2)) {
            r = m2;
        }   else {
            l = m1;
        }
    }
    return (times (l) < times (r) ? l : r);
}

int main()
{
   cin>>vp>>vf>>a;
   double l = 0, r = 1;
   setprecision(4);
   cout<<fixed<<binSearch (l, r);
}
