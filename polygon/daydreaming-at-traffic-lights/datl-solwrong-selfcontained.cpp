
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);

    ll N, E, D;
    cin >> N >> E >> D;

    vector<ll> green(N); for(auto& x : green) cin >> x;
    vector<ll> red(N); for(auto& x : red) cin >> x;

    vector<vector<pll>> G(N);
    for(int k = 0; k < E; k++) {
        ll a, b, w; cin >> a >> b >> w;
        --a; --b;
        G[a].emplace_back(b, w);
        G[b].emplace_back(a, w);
    }

    vector<ll> cost(N, 1e18);

    // Solve using a modified Dijkstra.
    // "todo" is a min-heap storing pairs (t, v) where we can *depart from* vertex v at time t.
    // Notice that the departure time depends on arrival time but also on green/red and D.
    priority_queue<pll, vector<pll>, greater<pll>> todo;
    ll START = 0;
    ll GOAL = N-1;
    todo.emplace(0, START);
    while (!todo.empty()) {
        auto [t, v] = todo.top();
        todo.pop();
        if (t >= cost[v]) continue;
        cost[v] = t;
        for (auto [u, w] : G[v]) {
            ll arrival_time = t + w;
            ll light_check_time = arrival_time % (green[u] + red[u]);
            if (u == GOAL) {
                // We don't care about the traffic light at the goal intersection.
                light_check_time = 0;
            }

            // WRONG VERSION: Just use the arrival time.
            // if (light_check_time < green[u]) {
            //     // We can depart from u at arrival_time.
            //     todo.emplace(arrival_time, u);
            // } else {
            //     ll cycle_time = green[u] + red[u];
            //     ll next_green = (arrival_time / cycle_time + 1) * cycle_time;

            //     // We can depart from u at next_green + D.
            //     todo.emplace(next_green + D, u);
            // }
            todo.emplace(arrival_time, u);
        }
    }

    cout << cost[GOAL] << endl;
    return 0;
}
