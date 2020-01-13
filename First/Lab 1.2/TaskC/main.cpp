#include <iostream>

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
    int n;
    cin>>n;
    int type, idnow;
    int size = 0;
    List* head = new List;
    head = NULL;
    List* tail = new List;
    tail = NULL;
    for (int i = 0; i < n; i++){
        cin>>type;
        if (type == 1){
            size++;
            cin>>idnow;
            List* now = new List;
            now->id = idnow;
            if (head == NULL){
                head = now;
                head->next = NULL;
                tail = now;
                tail->prev = NULL;
            } else if (head == tail){
                now->next = head;
                now->prev = NULL;
                tail->prev = now;
                tail = now;
            } else {
                now->next = tail;
                now->prev = NULL;
                tail->prev = now;
                tail = now;
            }
        } else if (type == 2){
            if (head != tail){
                head->prev->next = NULL;
                head = head->prev;
            } else {
                head = NULL;
                tail = NULL;
            }
            size--;
        } else if (type == 3){
            if (head != tail){
                    tail->next->prev = NULL;
                    tail = tail->next;
            } else {
                head = NULL;
                tail = NULL;
            }
            size--;
        } else if (type == 4){
            cin>>idnow;
            List* now = tail;
            int skipped = 0;
            while (now->id != idnow){
                skipped++;
                now = now->next;
            }
            cout<<size - 1 - skipped<<endl;
        } else {
            cout<<head->id<<endl;
        }
    }
}
