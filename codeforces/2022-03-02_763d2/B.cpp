
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define MP make_pair
#define MT make_tuple

// use these if I steal data structures from benq
// https://github.com/bqi343/USACO
#if 0
#define tcT template<class T
#define tcTU tcT, class U
#define V vector
#endif

#ifdef DCCLYDE_LOCAL
    #include "/home/dcclyde/puzzles/code/codeforces/cftemplate_local.h"
#else
    #define dbc(...) ;
    #define db(...) ;
    #define el
#endif

////////////////////////////////////////////////////////////////////////////////






void solve() {
    int N; cin >> N;
    vector<pair<int,int>> dat( N );
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> dat[k].first >> dat[k].second;
    }
    for ( auto& [L, R] : dat ) {
        int best_R = L-1;
        int best_L = R+1;
        for ( auto& [L2, R2] : dat ) {
            if ( L == L2 && R2 < R ) {
                best_R = max(best_R, R2);
            }
            if ( R == R2 && L2 > L ) {
                best_L = min( best_L , L2 );
            }
        }
        assert( best_R + 2 == best_L );
        cout << L << ' ' << R << ' ' << best_R + 1 << '\n';
    }


    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    int T = 1;
    std::cin >> T;  dbc("loading num cases!!!")  // just comment this for one-case problems.
    for ( int k = 1 ; k <= T ; ++k ) {
        el; dbc("CASE" , k ); el;
        solve();
    }

    return 0;
}
