#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::vector<int> siz(n);
    std::vector<i64> sum(n);

    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> parent(n, -1);

    std::vector<std::set<std::pair<int, int>>> s(n);
    std::function<void(int)> dfs = [&](int x) {
        siz[x] = 1;
        sum[x] = a[x];
        for (auto y : adj[x]) {
            if (y == parent[x]) {
                continue;
            }
            parent[y] = x;
            dfs(y);
            sum[x] += sum[y];
            siz[x] += siz[y];
            s[x].emplace(-siz[y], y);
        }
    };
    dfs(0);

    while (m--) {
        int t, x;
        std::cin >> t >> x;
        x--;
        if (t == 1) {
            std::cout << sum[x] << "\n";
        } else {
            if (s[x].empty()) {
                continue;
            }
            if (parent[x] == -1) {
                continue;
            }
            int y = s[x].begin()->second;
            s[parent[x]].erase({-siz[x], x});
            s[x].erase({-siz[y], y});
            siz[x] -= siz[y];
            siz[y] += siz[x];
            sum[x] -= sum[y];
            sum[y] += sum[x];
            s[y].emplace(-siz[x], x);
            s[parent[x]].emplace(-siz[y], y);
            parent[y] = parent[x];
            parent[x] = y;
        }
    }

    return 0;
}
