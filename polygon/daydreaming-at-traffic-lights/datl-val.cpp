#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

struct DSU {
    using vi = vector<int>;
	vi e; void init(int N) { e = vi(N,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union by size
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int N = inf.readInt(2, 200'000, "N");
    inf.readSpace();
    int E = inf.readInt(1, 200'000, "E");
    inf.readSpace();
    int D = inf.readInt(1, 1'000'000'000, "D");
    inf.readEoln();

    // Read N integers into a vector called green. Then read N more integers into a vector called red.
    vector<int> green = inf.readInts(N, D+1, 1'000'000'000, "green");
    inf.readEoln();
    vector<int> red = inf.readInts(N, 1, 1'000'000'000, "red");
    inf.readEoln();

    // Read E lines of 3 integers each.
    using t3 = tuple<int, int, int>;
    vector<t3> edges;
    DSU dsu; dsu.init(N);
    for (int k = 0; k < E; k++) {
        int a = inf.readInt(1, N, format("a[%d]", k+1));
        inf.readSpace();
        int b = inf.readInt(1, N, format("b[%d]", k+1));
        inf.readSpace();
        int w = inf.readInt(1, 1'000'000'000, format("w[%d]", k+1));
        inf.readEoln();
        ensuref(a != b, "a[%d] = b[%d] = %d", k+1, k+1, a);
        edges.emplace_back(a, b, w);
        dsu.unite(a-1, b-1);
    }
    ensuref(dsu.sameSet(0, N-1), "Vertex N is not reachable from vertex 1.");

    inf.readEof();
    return 0;
}
