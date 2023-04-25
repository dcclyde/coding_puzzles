#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int mul(int a, int b) { return (1LL * a * b)%MOD; }

int binpow(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = mul(res,a);
        a = mul(a,a);
        b >>= 1;
    }
    return res;
}

const int N = 2e5;
int h, ans[N];
vector<array<int, 2>> e[N];
bool ok;

void dfs(int c, int x) {
    ans[c] = x;
    for (auto i : e[c]) {
        if (ans[i[0]] == -1)
            dfs(i[0], (x + i[1]) % h);
        else if ((x + i[1]) % h != ans[i[0]])
            ok = false;
    }
}

void solve() {
    int n, m, cmp = 0, emp_cnt = 0;
    cin >> n >> m >> h;
    vector<vector<int>> a(n, vector<int>(m));
    ok = true;
    for (int i = 0; i < n; ++i) {
        e[i].clear();
        ans[i] = -1;
        for (int j = 0; j < m; ++j)
            cin >> a[i][j];
    }
    for (int j = 0; j < m; ++j) {
        int last = -1;
        bool all_empty = true;
        for (int i = 0; i < n; ++i)
            if (a[i][j] != -1) {
                if (last != -1) {
                    e[last].push_back({i, (a[i][j] - a[last][j] + h) % h});
                    e[i].push_back({last, (a[last][j] - a[i][j] + h) % h});
                }
                last = i;
                all_empty = false;
            }
        emp_cnt += all_empty;
    }
    for (int i = 0; i < n; ++i)
        if (ans[i] == -1) {
            ++cmp;
            dfs(i, 0);
        }
    cout << binpow(h, cmp - 1 + emp_cnt) * ok << "\n";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
