// https://atcoder.jp/contests/abc241/submissions/29716400

#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<set>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int maxn = 1e5 + 5, INF = 0x3f3f3f3f;

PII q[maxn * 4];

int main(){

#ifdef LOCAL
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
#endif

    int h, w, n;
    cin >> h >> w >> n;
    int sx, sy, gx, gy;
    cin >> sx >> sy >> gx >> gy;
    map<int, set<int>> row, col;
    map<PII, int> d;
    for(int i = 1; i <= n; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        row[y].insert(x);
        col[x].insert(y);
    }
    int hh = 0, tt = -1;
    d[{sx, sy}] = 0;
    q[++tt] = {sx, sy};
    while(hh <= tt){
        auto t = q[hh++];
        int x = t.first, y = t.second, dist = d[t];
        if (col.count(x)){
            auto it = col[x].upper_bound(y);
            if (it != col[x].end())
                if (!d.count({x, (*it) - 1})){
                    q[++tt] = {x, (*it) - 1};
                    d[{x, (*it) - 1}] = dist + 1;
                }
            if (it != col[x].begin()){
                --it;
                if (!d.count({x, (*it) + 1})){
                    q[++tt] = {x, (*it) + 1};
                    d[{x, (*it) + 1}] = dist + 1;
                }
            }
        }
        if (row.count(y)){
            auto it = row[y].upper_bound(x);
            if (it != row[y].end()){
                if (!d.count({(*it) - 1, y})){
                    q[++tt] = {(*it) - 1, y};
                    d[{(*it) - 1, y}] = dist + 1;
                }
            }
            if (it != row[y].begin()){
                --it;
                if (!d.count({(*it) + 1, y})){
                    q[++tt] = {(*it) + 1, y};
                    d[{(*it) + 1, y}] = dist + 1;
                }
            }
        }

    }
    if (d.count({gx, gy})) cout << d[{gx, gy}] << '\n';
    else puts("-1");

}