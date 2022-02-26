
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

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
    #define dbc(...) 43
    #define db(...) 45
    #define el
#endif

////////////////////////////////////////////////////////////////////////////////






void solve() {
    multiset<ll> A;
    int Q; cin >> Q;
    std::multiset<ll>::iterator it;
    for ( int qid = 0 ; qid < Q ; ++qid ) {
        int qtype; cin >> qtype;
        if ( qtype == 1 ) {
            ll x; cin >> x;
            A.insert( x );

        } else if ( qtype == 2 ) {
            // need Kth biggest that doesn't go above X.
            ll x, steps; cin >> x >> steps;
            it = A.upper_bound( x );  // first element that DOES go above x.
            bool printed = false;
            for ( int k = 0 ; k < steps ; ++k ) {
                if ( it == A.begin() ) {
                    cout << -1 << '\n';
                    printed = true;
                    break;
                }
                --it;
            }
            if ( printed ) {
                continue;
            }
            cout << *it << '\n';

        } else {  // qtype == 3
            // need Kth smallest that doesn't go below X.
            ll x, steps; cin >> x >> steps;
            it = A.lower_bound( x );  // first element that's X or above.
            --steps;
            bool printed = false;
            for ( int k = 0 ; k < steps ; ++k ) {
                if ( it == A.end() ) {
                    cout << -1 << '\n';
                    printed = true;
                    break;
                }
                ++it;
            }
            if ( printed ) {
                continue;
            }
            if ( it == A.end() ) {
                cout << -1 << '\n';
                printed = true;
                continue;
            }
            cout << *it << '\n';
        }
    }
    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    int T = 1;
    // std::cin >> T;  // just comment this for one-case problems.
    for ( int k = 0 ; k < T ; ++k ) {
        solve();
    }

    return 0;
}
