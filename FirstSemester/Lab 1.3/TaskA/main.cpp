#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, k;
    ifstream f1 ("input.txt");
    ofstream f2 ("output.txt");
    f1>>n>>k;
    vector <int> a (n);
    for (int i = 1; i < n - 1; i++){
        f1>>a[i];
    }
    a[0] = 0;
    a[n - 1] = 0;
    vector <long long> dp (n, -10e9);
    dp[0] = 0;
    vector <int> path (n);
    for (int i = 1; i < n; i++){
        for (int j = 1; j <= k; j++){
            if (i - j < 0){
                break;
            }
            if (dp[i] < dp [i - j]){
                dp[i] = dp [i - j];
                path[i] = i - j;
            }
        }
        dp[i] += a[i];
    }
    vector <int> ans;
    int i = n - 1;
    while (i != 0){
        ans.push_back(i + 1);
        i = path [i];
    }
    ans.push_back(i + 1);
    f2<<dp[n - 1]<<endl;
    f2<<ans.size() - 1<<endl;
    for (int i = ans.size() - 1; i >= 0; i--){
        f2<<ans[i]<<' ';
    }
    f1.close();
    f2.close();
}
