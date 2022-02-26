
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
    int N; cin >> N;
    ll steps; cin >> steps;
    vector<int> A( N );
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> A[k];
    }

    ll out = 0;
    // residue --> (steps remaining, value so far)
    map<int, std::pair<ll, ll>> seen;
    seen[ 0 ] = make_pair( steps , 0 );
    db(
        seen.count( 0 ),
        seen.find( 0 ) != seen.end()
    );

    // Run normally unless we find an already-seen value.
    while ( true ) {
        db( N , steps , out , out%N , seen );
        out += A[ out % N ];
        --steps;
        if ( steps > N && seen.count( out%N ) ) {
            // handle a bunch of multiples at once.
            ll steps_past = seen[ out%N ].first;
            ll out_past = seen[ out%N ].second;

            ll delta_steps = steps_past - steps;
            ll delta_out = out - out_past;

            ll multiplier = steps / delta_steps;
            steps -= multiplier * delta_steps;
            out += multiplier * delta_out;
            dbc( "handle multiple steps at once." , delta_steps , multiplier , steps , out );
        }
        if ( steps == 0 ) {
            cout << out << '\n';
            return;
        }
        if ( steps > N ) {
            seen[ out%N ] = make_pair( steps , out );
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
