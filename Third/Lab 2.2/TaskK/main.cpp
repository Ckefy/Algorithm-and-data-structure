#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector < vector < ll > > g;
vector <ll> parent;
vector <ll> answer;
vector <bool> was;
ll n, root;
vector < pair <ll,ll>  > edges2;


ll recMex(int now, int from){
    if (!was[now]){
        parent[now] = from;
        was[now] = 1;
        for (int i = 0; i < g[now].size(); i++){
                if (g[now][i] != from)
                    answer[now] ^= (recMex(g[now][i], now) + 1);
        }
        return answer[now];
    } else {
        return answer[now];
    }
}

ll check (ll now, ll old, ll sum){
  if (now == root) return sum;
sum = (sum+1) ^ answer[parent [now]] ^ (old+1);
return check(parent [now], answer[parent[now]], sum);
}

int main()
{
    cin>>n>>root;
    root--;
    g.resize(n);
    parent.resize(n);
    for (int i = 0; i < n - 1; i++){
        int a, b;
        cin>>a>>b;
        a--; b--;
        edges2.push_back(make_pair(a, b));
        g[a].push_back(b);
        g[b].push_back(a);
    }
    was.resize(n, 0);
    answer.resize(n, 0);

    recMex(root, -1);

    if (answer[root]==0) {
        cout<<2<<endl;
        return 0;
    }

    random_device rd;
    mt19937 g(rd ());
    vector <ll> number;
    for (int i = 0; i < n - 1; i ++){
        number.push_back(i);
    }
    shuffle (number.begin(), number.end(), g);
    for (int j = 0; j < n - 1; j++){
        int i = number[j];
        ll now;
        pair <ll, ll> nowedge = edges2[i];
        if (nowedge.first == parent[nowedge.second]){
            now = nowedge.second;
        } else {
            now = nowedge.first;
        }
        ll answ = check(now, answer[now], -1);
            if (answ==0){
                    cout<<1<<endl;
                    cout<<i + 1;
                    return 0;
            }
    }
}
