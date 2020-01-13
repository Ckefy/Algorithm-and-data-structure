#include <bits/stdc++.h>

using namespace std;

struct List{
    long long value;
    long long minim;
    List* next;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    List* top = new List;
    long long n;
    cin>>n;
    long long smth = 0;
    long long smthval = 0;
    cin>>smth;
    cin>>smthval;
    top->value = smthval;
    top->minim = smthval;
    top->next = NULL;
    for (int i = 1; i < n; i++){
        cin>>smth;
        if (smth == 1){
            List* now = new List;
            cin>>smthval;
            now->value = smthval;
            now->next = top;
            if (top!=NULL){
                    now->minim = min(smthval, now->next->minim);
            } else {
                now->minim = smthval;
            }
            top = now;
        } else if (smth == 2) {
            top = top->next;
        } else {
            cout<<top->minim<<endl;
        }
    }
}
