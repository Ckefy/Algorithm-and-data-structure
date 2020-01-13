#include <bits/stdc++.h>

using namespace std;

const long long inf = 1000000000;
vector < vector < double > > g;
vector <bool> color;
vector <double> mini;
vector < pair < int, int > > vert;

double calc (int x1, int y1, int x2, int y2){
    return pow((pow(x1 - x2, 2) + pow(y1 - y2, 2)), 0.5);
}

double replaceg (int now, int j){
    pair <int, int> nowp = vert[now];
    pair <int, int> jp = vert[j];
    return calc(nowp.first, nowp.second, jp.first, jp.second);
}

int main()
{
    int n;
    cin>>n;
    //g.resize(n, vector <double> (n));
    for (int i = 0; i < n; i++){
        int x, y;
        cin>>x>>y;
        x+=10000;
        y+=10000;
        vert.push_back(make_pair(x, y));
    }
    /*for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            g[i][j]=calc(vert[i].first, vert[i].second, vert[j].first, vert[j].second);
        }
    }*/
    mini.resize(n, inf);
    color.resize(n);
    mini[0] = 0;
    double ans = 0;
    for (int i = 0; i < n; i++){
        int now = -1;
        for (int j = 0; j < n; j++){
            if (!color[j] && (mini[j] < mini[now] || now == -1)){
                now = j;
            }
        }
        color[now] = 1;
        ans += mini[now];
        for (int j = 0; j < n; j++){
            if (replaceg(now, j) < mini[j]){
                mini[j] = replaceg(now, j);
            }
        }
    }
    cout<<ans;
}
