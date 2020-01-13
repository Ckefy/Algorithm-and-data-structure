#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s, t;
    cin>>s>>t;
    int n = s.length();
    string str = s + '$' + t;
    vector <int> p (str.length(), 0);
    for (int i = 1; i < str.length(); i++){
        int j = p[i - 1];
        while (j > 0 && str[i] != str[j]){
            j = p[j - 1];
        }
        if (str[i] == str[j]) j++;
        p[i] = j;
    }
    int counter = 0;
    vector <int> answer;
    for (int i = n + 1; i < str.length(); i++){
        if (p[i] == n){
            counter++;
            answer.push_back(i - 2 * n + 1);
        }
    }
    cout<<counter<<endl;
    for (int i = 0; i < answer.size(); i++){
        cout<<answer[i]<<' ';
    }
}
