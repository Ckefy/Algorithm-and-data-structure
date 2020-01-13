#include <bits/stdc++.h>

using namespace std;

struct List{
    int id;
    List* next;
    List* prev;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, nowid;
    cin>>n;
    char c;
    List* tail = new List;
    List* head = new List;
    List* mid = new List;
    tail = NULL;
    head = NULL;
    mid = NULL; //need to insert before mid
    int size = 0;
    for (int i = 0; i < n; i++){
       cin>>c;
       if (c == '+'){
            cin>>nowid;
            List* now = new List;
            now->id = nowid;
            if (tail == NULL){
                head = now;
                head->next = NULL;
                tail = now;
                tail->prev = NULL;
                mid = head;
            } else if (tail == head){
                now->next = head;
                now->prev = NULL;
                head->prev = now;
                tail = now;
                mid = head;
            } else {
                now->next = tail;
                now->prev = NULL;
                tail->prev = now;
                tail = now;
                if (size % 2 == 0){
                        mid = mid->prev; //было 2 элемента, mid на 2 (между 1 и 2), нужно сделать на новом 2 (между 1 и 2 новыми)
                }
            }
            size++;
       } else if (c == '*'){
            cin>>nowid;
            List* now = new List;
            now->id = nowid;
            if (tail == NULL){
                head = now;
                head->next = NULL;
                tail = now;
                tail->prev = NULL;
                mid = head;
            } else if (tail == head){
                now->next = head;
                now->prev = NULL;
                head->prev = now;
                tail = now;
                mid = head;
            } else {
                now->next = mid;
                now->prev = mid->prev;
                mid->prev->next = now;
                mid->prev = now;
                if (size % 2 ==0){
                    mid = now;
                }
            }
            size++;
       } else {
           cout<<head->id<<endl;
            if (head != tail){
                if (size % 2 == 0){
                    mid = mid->prev;
                }
                head->prev->next = NULL;
                head = head->prev;
            } else {
                head = NULL;
                tail = NULL;
                mid = NULL;
            }
            size--;
       }
    }
}
