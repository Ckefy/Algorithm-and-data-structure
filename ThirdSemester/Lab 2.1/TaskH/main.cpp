#include <bits/stdc++.h>

using namespace std;

int n;
vector <bool> was;
vector < vector < int > > g;
vector <int> dist;
int counter = 0;

void dfs (int now, int curDist, int type){
    counter++;
    was[now] = true;
    for (int i = 0; i < n; i++){
        if (type == 0){ //straight
                if (!was[i] && g[now][i] <= curDist)
                    dfs(i, curDist, type);
        } else {
            if (!was[i] && g[i][now] <= curDist)
                dfs(i, curDist, type);
        }
    }
}

bool isStrong (int curDist){
    for (int i = 0; i < n; i++){
        was[i] = false;
    }
    counter = 0;
    dfs(0, curDist, 0);
    if (counter < n){
        return false;
    }
    for (int i = 0; i < n; i++){
        was[i] = false;
    }
    counter = 0;
    dfs(0, curDist, 1);
    return counter >= n;
}

int binarySearch (){
    int l = -1;
    int r = n * n;
    while (r - l > 1){
        int mid = l + (r - l) / 2;
        if (isStrong(dist[mid])){
            r = mid;
        } else {
            l = mid;
        }
        //cout<<l<<' '<<r<<endl;
    }
    return r;
}

int main()
{
    ifstream f1("avia.in");
    ofstream f2("avia.out");
    f1>>n;
    was.resize(n, false);
    g.resize(n, vector <int> (n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            f1>>g[i][j];
            dist.push_back(g[i][j]);
        }
    }
    sort (dist.begin(), dist.end());
    /*for (int i = 0; i < n * n; i++){
        cout<<dist[i]<<' ';
    }
    cout<<endl;*/
    f2<<dist[binarySearch()];
}
