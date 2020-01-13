#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin>>n;
    vector <int> mas (n);
    for (int i = 0; i < n; i++){
        cin>>mas[i];
    }
    int minim = 1;
    vector <string> answer;
    for (int i = 0; i < n; i++){
        if (mas[i] < minim){
            continue;
        }
        if (mas[i] == minim){
                answer.push_back("push");
                answer.push_back("pop");
                minim++;
                i--;
                while (i>=0 && mas[i] <= minim){
                    if (mas[i] < minim){
                        i--;
                        continue;
                    }
                    answer.push_back("pop");
                    minim++;
                    i--;
                }
        } else {
            answer.push_back("push");
        }
    }
    if (minim <= n){
        cout<<"impossible"<<endl;
    } else {
        for (int i = 0; i < answer.size(); i++){
            cout<<answer[i]<<endl;
        }
    }
}
