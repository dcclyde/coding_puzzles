
/*
The first line contains three integers $N, E, D$ ($2 \le N \le 2 \cdot 10^5$; $1 \le E \le 2 \cdot 10^5$; $1 \le D \le 10^9$) --- the number of intersections, the number of roads, and the extra time Christine loses by daydreaming after hitting a red light.

The second line contains $N$ integers $g_1, g_2, \cdots, g_N$ ($D+1 \le g_k \le 10^9$) --- the length of the intervals for which each traffic light is green.

The third line contains $N$ integers $r_1, r_2, \cdots, r_N$ ($1 \le g_k \le 10^9$) --- the length of the intervals for which each traffic light is red.

Then $E$ lines follow. The $j$th of them contains three integers $a_j$, $b_j$, $w_j$ ($1 \le a_j, b_j \le N$, $a_j \not = b_j$; $1 \le w_j \le 10^9$) --- the two intersections connected by road $j$, and the cost in seconds of driving on this road. It is guaranteed that vertex $N$ is reachable from vertex $1$.
*/

#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

template<class T, class U> bool ckmin(T& a, const U& b) {
    return (T)b < a ? a = (T)b, 1 : 0; } // set a = min(a,b)
template<class T, class U> bool ckmax(T& a, const U& b) {
    return a < (T)b ? a = (T)b, 1 : 0; } // set a = max(a,b)


using ll = long long;

const ll MAX_EDGES = 200'000;

vector<pair<int,int>> gen_tree(int N, int weight) {
    vector<int> p(N);

    /* setup parents for vertices 1..N-1 */
    for(int i = 0; i < N; ++i)
        if (i > 0)
            p[i] = rnd.wnext(i, weight);

    // printf("%d\n", N);

    /* shuffle vertices 1..N-1 */
    vector<int> perm(N);
    for(int i = 0; i < N; ++i)
        perm[i] = i;
    shuffle(perm.begin() + 1, perm.end());

    /* put edges considering shuffled vertices */
    vector<pair<int,int> > edges;
    for (int i = 1; i < N; i++)
        if (rnd.next(2))
            edges.push_back(make_pair(perm[i]+1, perm[p[i]]+1));
        else
            edges.push_back(make_pair(perm[p[i]]+1, perm[i]+1));

    /* shuffle edges */
    shuffle(edges.begin(), edges.end());
    return edges;
}

vector<pair<int,int>> gen_graph(int N, int E, bool force_connected) {
    set<pair<int,int> > edges;
    if (force_connected) {
        assert(E >= N - 1);
        auto tree_edges = gen_tree(N, 0);
        edges.insert(tree_edges.begin(), tree_edges.end());
    }
    while((int)edges.size() < E){
        int u = rnd.next(1,N); // generates a random number between 1 and n, inclusive
        int v = rnd.next(1,N);
        if(u == v) continue; // Can't have a self loop
        if(edges.count(make_pair(u,v)) != 0) continue; // We already have this edge already
        if(edges.count(make_pair(v,u)) != 0) continue; // We have the "backwards edge" already
        edges.emplace(u,v); // This is equivalent to "edges.insert(make_pair(u,v));"
    }

    // In the set, the edges are sorted. Let's shuffle the order.
    vector<pair<int,int> > edges_vector(edges.begin(),edges.end()); // This copies the set<> into a vector<>
    shuffle(edges_vector.begin(), edges_vector.end()); // Shuffles edges2 randomly.
    return edges_vector;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    // parameters: N_MIN, N_MAX, N_WEIGHT, E_DENSITY_MIN, E_DENSITY_MAX, E_WEIGHT, D_MIN, D_MAX, GR_MAX, W_MAX, weight
    int ctr = 1;
    int N_MIN = opt<int>("nmin");
    int N_MAX = opt<int>("nmax");
    int N_WEIGHT = opt<int>("nweight");
    double E_DENSITY_MIN = opt<double>("densemin");
    double E_DENSITY_MAX = opt<double>("densemax");
    int E_WEIGHT = opt<int>("eweight");
    int D_MIN = opt<int>("dmin");
    int D_MAX = opt<int>("dmax");
    int G_MAX = opt<int>("gmax");
    int R_MAX = opt<int>("rmax");
    int W_MAX = opt<int>("wmax");
    int weight = opt<int>("weight");

    int N = rnd.wnext(N_MIN, N_MAX, N_WEIGHT);
    int D = rnd.next(D_MIN, min(D_MAX, G_MAX-1));
    vector<int> green(N), red(N);
    for (int i = 0; i < N; i++) {
        green[i] = rnd.wnext(D+1, G_MAX, weight);
        red[i] = rnd.wnext(1, R_MAX, weight);
    }

    ll edges_upper = N * (N - 1) / 2;
    ckmin(edges_upper, MAX_EDGES);
    ll edges_lower = N - 1;

    double E_dbl = rnd.wnext(E_DENSITY_MIN, E_DENSITY_MAX, E_WEIGHT);

    ll E = edges_lower + E_dbl * (edges_upper - edges_lower);
    ckmin(E, edges_upper);
    ckmax(E, edges_lower);

    auto edges = gen_graph(N, E, true);

    vector<int> w(E);
    for (int i = 0; i < E; i++) {
        w[i] = rnd.wnext(1, W_MAX, weight);
    }

    // now start outputting stuff.
    cout << N << " " << E << " " << D << '\n';

    for (int i = 0; i < N; i++) {
        cout << green[i];
        if (i == N - 1) {cout << '\n';}
        else {cout << " ";}
    }

    for (int i = 0; i < N; i++) {
        cout << red[i];
        if (i == N - 1) {cout << '\n';}
        else {cout << " ";}
    }

    for (int i = 0; i < E; i++) {
        cout << edges[i].first << " " << edges[i].second << " " << w[i] << '\n';
    }

    return 0;
}
