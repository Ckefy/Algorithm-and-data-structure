#include <bits/stdc++.h>

using namespace std;

struct List{
    int color;
    List* next;
    List* prev;
};

int main()
{
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    //cout.tie(NULL);
    List* first = new List;
    List* last = new List;
    first->prev = NULL;
    first->next = last;
    last->next = NULL;
    last->prev = first;
    int n;
    cin>>n;
    if (n <=2){
        int kost;
        for (int i = 0; i < n; i++)
            cin>>kost;
        cout<<0;
        return 0;
    }
    int nowc;
    cin>>nowc;
    first->color = nowc;
    cin>>nowc;
    last->color = nowc;
    for (int i = 2; i < n; i++){
        cin>>nowc;
        List* now = new List;
        now->color = nowc;
        last->next = now;
        now->prev = last;
        now->next = NULL;
        last = now;
    }
    int counter = 1;
    int ans = 0;
    List* now = first->next;
    List* start = first;
    List* after = NULL;
    while (true){
        if (now == NULL || now->color != now->prev->color){
            if (counter >=3){
                after = now;
                break;
            } else {
                counter = 1;
                start = now;
                if (now != NULL) {
                        now = now->next;
                } else{
                    break;
                }
            }
        } else {
            counter++;
            now = now->next;
        }
    }
    if (start == NULL){
        cout<<0<<endl;
        return 0;
    }
    if (start == first || after == NULL){
        ans+=counter;
        cout<<ans<<endl;
        return 0;
    }
    List* before = start->prev;
    before->next = after;
    after->prev = before;
    ans+=counter;
    /////
    /*List* now1 = first;
    while (now1!=NULL){
        cout<<now1->color<<' ';
        now1=now1->next;
    }
    cout<<endl;
    cout<<ans<<endl*/
    ////
    while (true){
        if (before->color != after->color){
            cout<<ans;
            return 0;
        }
        start = before;
        before = before->prev;
        counter = 2;
        while (true){
            if (before == NULL || before->color != before->next->color){
                if (before == NULL){
                    start = first;
                } else {
                    start = before->next;
                }
                break;
            } else {
                counter++;
                before = before->prev;
            }
        }
        after = after->next;
        while (true){
            if (after == NULL || after->color != after->prev->color){
                break;
            } else {
                counter++;
                after = after->next;
            }
        }
        if (counter >= 3){
                ans+=counter;
                if (before!=NULL) before->next = after;
                if (after!=NULL) after->prev = before;
        } else {
            cout<<ans<<endl;
            return 0;
        }
        if (before == NULL || after == NULL){
            cout<<ans<<endl;
            return 0;
        }
    }
}
