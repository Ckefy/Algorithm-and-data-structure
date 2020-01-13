#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int x = 911;
vector <ll> hashes;
vector <ll> powers;
string s;

int main()
{
    cin>>s;
    int n;
    cin>>n;
    powers.resize(s.length());
    hashes.resize(s.length());
    powers[0] = 1;
    hashes[0] = int(s[0]);
    for (int i = 1; i < powers.size(); i++){
        powers[i] = powers[i - 1] * x;
        hashes[i] = hashes[i - 1] + powers[i] * int(s[i]);
    }
    int s1, f1, s2, f2;
    for (int i = 0; i < n; i++){
        cin>>s1>>f1>>s2>>f2;
        s1--; f1--; s2--; f2--;
        ll hash1 = hashes[f1] - (s1 == 0 ? 0 : hashes[s1 - 1]);
        ll hash2 = hashes[f2] - (s2 == 0 ? 0 : hashes[s2 - 1]);
        if (hash1 * powers[s2] == hash2 * powers[s1]){
            cout<<"Yes"<<endl;
        } else {
            cout<<"No"<<endl;
        }
    }
}
