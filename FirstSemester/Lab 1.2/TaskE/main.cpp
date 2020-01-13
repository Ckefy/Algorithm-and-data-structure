#include <bits/stdc++.h>

using namespace std;

struct List{
    long long value;
    List* next;
};

int main()
{
    /*ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);*/
    string s;
    getline(cin, s);
    List* top = new List;
    long long a1 = 0;
    int j = 0;
    char c;
    for (int i = 0; i < s.length(); i++){
        if (s[i] ==' '){
            j = i;
            break;
        } else {
           a1 = a1 * 10 + int (s[i]) - 48;
        }
    }
    top->value = a1;
    top->next = NULL;
    for (int i = j + 1; i < s.length(); i++){
        c = s[i];
        if (c == ' '){
            continue;
        } else if (c == '+'){
            long long a = top->value;
            top = top->next;
            long long b = top->value;
            top->value = a + b;
            List* now = top;
        } else if (c == '*'){
            long long a = top->value;
            top = top->next;
            long long b = top->value;
            top->value = a * b;
        } else if (c == '-'){
            long long a = top->value;
            top = top->next;
            long long b = top->value;
            top->value = b - a;
        } else {
            long long a = int (c) - 48;
            i++;
            while (i < s.length() && s[i] != ' '){
                c = s[i];
                a = a*10 + int (c) - 48;
                i++;
            }
            List* now = new List;
            now->value = a;
            now->next = top;
            top = now;
        }
    }
    cout<<top->value;
}
