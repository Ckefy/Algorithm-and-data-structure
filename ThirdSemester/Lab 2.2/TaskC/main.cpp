#include <bits/stdc++.h>
#define ll int
using namespace std;
ll inf = 1000000;

int n;
vector < vector < ll > > d;
vector <ll> ans;
vector <ll> dist;
vector <ll> parent;

void findCycle(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (d[i][j] != inf && dist[j] > dist[i] + d[i][j]){
                for (int k = 0; k < n; k++){
                    j = parent[j];
                }
                i = j;
                ans.push_back(j);
                while (i != parent[j]){
                    j = parent[j];
                    ans.push_back(j);
                }
                return;
            }
        }
    }
}

int main()
{
    cin>>n;
    d.resize(n, vector <ll> (n, inf));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            int cost;
            cin>>cost;
            if (cost != 100000){
                d[i][j] = cost;
            }
        }
    }
    dist.resize(n, 0);
    parent.resize(n, -1);

    for (int k=0; k<n; k++)
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                if (d[i][j] != inf && dist[j] > dist[i] + d[i][j]){
                    dist[j] = dist[i] + d[i][j];
                    parent[j] = i;
                }
    findCycle();
    if (!ans.size()){
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;
    cout<<ans.size()<<endl;
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++){
        cout<<ans[i] + 1<<' ';
    }
}
