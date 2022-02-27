
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
    string dat; cin >> dat;

    int num_b = 0;
    // for ( int k = 0 ; k < N ; ++k ) {

    // }

    for ( const auto& c : dat ) {
        if ( c == 'C' ) {
            cout << string( num_b/2 , 'A' );
            if ( num_b % 2 == 1 ) {
                cout << 'B';
            }
            cout << 'C';
            num_b = 0;
        } else if ( c == 'A' ) {
            num_b += 2;
        } else {
            num_b += 1;
        }
    }
    cout << string( num_b/2 , 'A' );
    if ( num_b % 2 == 1 ) {
        cout << 'B';
    }
    cout << '\n';

    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    int T = 1;
    // std::cin >> T;  // just comment this for one-case problems.
    for ( int k = 1 ; k <= T ; ++k ) {
        el; dbc("CASE" , k ); el;
        solve();
    }

    return 0;
}
