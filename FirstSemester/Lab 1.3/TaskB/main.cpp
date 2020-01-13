#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    ifstream f1 ("input.txt");
    ofstream f2 ("output.txt");
    f1>>n>>m;
    vector < vector < long long > > a (n, vector <long long> (m));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            f1>>a[i][j];
        }
    }
    vector < vector < long long > > dp (n, vector <long long> (m, -10e9));
    dp[0][0] = a[0][0];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (i > 0 && j > 0){
                dp [i][j] = max (dp[i][j - 1], dp[i - 1][j]) + a[i][j];
            } else if (i > 0){
                dp[i][j] = dp[i - 1][j] + a[i][j];
            } else if (j > 0){
                dp[i][j] = dp[i][j - 1] + a[i][j];
            }
        }
    }
    int i = n - 1;
    int j = m - 1;
    vector <char> ans;
    while (i > 0 || j > 0){
        if (i > 0 && dp[i][j] == dp[i - 1][j] + a[i][j]){
            ans.push_back('D');
            i--;
        } else {
            j--;
            ans.push_back('R');
        }
    }
    f2<<dp[n - 1][m - 1]<<endl;
    for (int i = ans.size() - 1; i >= 0; i--){
        f2<<ans[i];
    }
}
