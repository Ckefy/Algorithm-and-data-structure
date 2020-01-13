#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin>>n;
    vector <long long> a (n);
    for (int i = 0; i < n; i++){
        cin>>a[i];
    }
    vector <int> way (n, -1);
    vector <int> dp (n, 1); //сам элемент берется
    for (int i = 0; i < n; i++){
        for (int j = 0; j < i; j++){
            if (a[j] < a[i] && dp[j] >= dp[i] - 1){
                dp[i] = dp[j] + 1;
                way[i] = j;
            }
        }
    }
    int j = -1;
    vector <long long> anss;
    long long ans = 0;
    for (int i = 0; i < n; i++){
        if (dp[i] >= ans){
            j = i;
            ans = dp[i];
        }
    }
    while (j != -1){
        anss.push_back(a[j]);
        j = way[j];
    }
    cout<<ans<<endl;
    for (int i = anss.size() - 1; i >= 0; i--){
        cout<<anss[i]<<' ';
    }
}
