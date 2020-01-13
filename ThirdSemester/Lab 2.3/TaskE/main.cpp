#include <bits/stdc++.h>

using namespace std;

int main()
{
    string str;
    cin>>str;
    vector <int> p (str.length(), 0);
    for (int i = 1; i < str.length(); i++){
        int j = p[i - 1];
        while (j > 0 && str[i] != str[j]){
            j = p[j - 1];
        }
        if (str[i] == str[j]) j++;
        p[i] = j;
    }
    int k = str.length() - p[str.length() - 1];
    if (str.length() % k){
        k = str.length();
    }
    cout<<k<<endl;
}
