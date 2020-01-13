#include <bits/stdc++.h>
#define inf 1000000
using namespace std;

int main()
{
    string s1, s2;
    cin>>s1>>s2;
    int n = s1.length(), m = s2.length();
    vector < vector < int > > d (n + 1, vector <int> (m + 1));
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            if (i == 0 && j == 0){
                d[i][j] = 0;
                continue;
            }
            d[i][j] = inf;
            if (i > 0 && j > 0 && s1[i - 1] == s2[j - 1]){
                d[i][j] = d[i - 1][j - 1];
            }
            if (i > 0 && j > 0){
                d[i][j] = min (1 + d[i - 1][j - 1], d[i][j]);
            }
            if (i > 0){
                d[i][j] = min (d[i][j], 1 + d[i - 1][j]);
            }
            if (j > 0){
                d[i][j] = min (d[i][j], 1 + d[i][j - 1]);
            }
        }
    }
    cout<<d[n][m]<<endl;
}
