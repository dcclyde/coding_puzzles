#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <assert.h>
using namespace std;

/*
    N nodes, <= 10
    E bad pairs
    T colors.

    Note - renaming the colors does NOT count as a new coloring here.

    **********

    There are only 10 nodes.
    Maybe I could just brute force carefully?
    10^10 is too much, but 10^10 / 10! is probably fine.
        Yeah, it's no problem.

    So - I guess just full bruteforce, but only trying
        already-used colors or the smallest unused color in each slot?
*/

int main() {
    int N, COLORS, E;
    cin >> N >> COLORS >> E;
    vector<vector<int>> G(N);
    for(int k = 0; k < E; ++k) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        assert(a < b);
        G[b].push_back(a);
    }

    int out = 0;
    vector<int> wip;
    auto rec = [&](auto&& self, int colors_used) -> void {
        if (wip.size() == N) {
            if (colors_used == COLORS) {++out;}
            return;
        }

        // color the next node.
        int pos = wip.size();
        for(int color = 1; color <= COLORS; ++color) {
            if (color > colors_used + 1) {break;}
            // is this choice banned by some edge?
            bool ok = true;
            for(auto& x : G[pos]) {
                if (wip[x] == color) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {continue;}
            wip.push_back(color);
            self(self, max(colors_used, color));
            wip.pop_back();
        }
        return;
    };
    rec(rec, 0);

    cout << out << endl;
    return 0;
}
