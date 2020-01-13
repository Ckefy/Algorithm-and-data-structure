#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
   int n, m;
   vector < vector < ll > > reversed;
   vector <bool> victory, defeat;
   vector <ll> children;
    deque <ll> que;
   while (cin>>n>>m){
        reversed.resize(0);
        victory.resize(0);
        defeat.resize(0);
        children.resize(0);
        reversed.resize(n);
        victory.resize(n, 0);
        defeat.resize(n, 0);
        children.resize(n, 0);
        for (int i = 0; i < m; i++){
            ll a, b;
            cin>>a>>b;
            a--; b--;
            children[a]++;
            reversed[b].push_back(a);
        }
        for (int i = 0; i < n; i++){
            if (children[i] == 0){
                defeat[i] = true;
                que.push_back(i);
            }
        }
        while (true){
            if (que.empty()) break;
            ll now = que.front();
            que.pop_front();
            for (int i = 0; i < reversed[now].size(); i++){
                ll parent = reversed[now][i];
                if (defeat[parent] || victory[parent] || !defeat[now] && !victory[now]) continue;
                children[parent]--;
                if (victory[now] && !children[parent]){
                    defeat[parent] = 1;
                } else if (defeat[now]){
                    victory[parent] = 1;
                } else {
                    continue;
                }
                que.push_back(parent);
            }
        }
        for (int i = 0; i < n; i++){
            if (victory[i]){
                 cout<<"FIRST"<<endl;
            } else if (defeat[i]){
                cout<<"SECOND"<<endl;
            } else {
                cout<<"DRAW"<<endl;
            }
        }
        cout<<endl;
   }
}
