
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define MP make_pair
#define MT make_tuple

// use these if I steal data structures from benq
// https://github.com/bqi343/USACO
#if 1
#define tcT template<class T
#define tcTU tcT, class U
#define V vector
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
using vl = V<ll>;
using vi = V<int>;
#define sz(x) int((x).size())
tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
#endif

#ifdef DCCLYDE_LOCAL
    #include "/home/dcclyde/puzzles/code/codeforces/cftemplate_local.h"
#else
    #define dbc(...) ;
    #define db(...) ;
    #define el
#endif

////////////////////////////////////////////////////////////////////////////////



/**
 * Description: All-Pairs Shortest Path
 * Source: KACTL
 * Verification:
    * https://open.kattis.com/problems/allpairspath
    * https://cses.fi/problemset/task/1672/
 */

int INF = 1e9;

void floydWarshall(V<vi>& m) {
    int n = sz(m);
    F0R(i,n) ckmin(m[i][i], 0);
    F0R(k,n) F0R(i,n) F0R(j,n)
        if (m[i][k] != INF && m[k][j] != INF) {
            auto newDist = max(m[i][k]+m[k][j],-INF);
            ckmin(m[i][j],newDist);
        }
    F0R(k,n) if (m[k][k] < 0) F0R(i,n) F0R(j,n)
        if (m[i][k] != INF && m[k][j] != INF) m[i][j] = -INF;
}


void solve() {
    int N; cin >> N;  // N <= 500
    vector<vector<int>> dat( N );
    vector<vector<int>> graph( N , vector<int>(N, INF) );
    for ( int cow = 0 ; cow < N ; ++cow ) {
        int num_to_read = N;
        bool seen_my_num = false;
        while ( num_to_read > 0 ) {
            int dummy;
            cin >> dummy;
            --dummy;
            if ( dummy == cow ) {
                seen_my_num = true;
            }
            if ( ! seen_my_num ) {
                dat[cow].push_back( dummy );
                graph[cow][dummy] = 1;
            }
            --num_to_read;
        }
    }

    floydWarshall( graph );
    for ( int cow = 0 ; cow < N ; ++cow ) {
        bool done = false;
        for ( auto& gift : dat[cow] ) {
            if ( graph[gift][cow] < INF ) {
                cout << gift+1 << '\n';
                done = true;
                break;
            }
        }
        if ( !done ) {
            cout << cow+1 << '\n';
        }
    }

    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    // // test floyd-warshall.
    // vector<vector<int>> graph( 4 , vector<int>( 4 , INF ) );
    // graph[0][1] = 1;
    // graph[1][2] = 1;
    // graph[2][3] = 1;
    // // graph[3][0] = 1;
    // graph[3][1] = 1;
    // for ( int k = 0 ; k < graph.size() ; ++k ) {
    //     db( k , graph[k] );
    // }
    // el;
    // floydWarshall( graph );
    // for ( int k = 0 ; k < graph.size() ; ++k ) {
    //     db( k , graph[k] );
    // }
    // return 0;

    int T = 1;
    // std::cin >> T;  // just comment this for one-case problems.
    for ( int k = 1 ; k <= T ; ++k ) {
        el; dbc("CASE" , k ); el;
        solve();
    }

    return 0;
}
