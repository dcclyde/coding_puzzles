
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
    vector<int> dat( N );
    int sum = 0;
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> dat[k];
        sum += dat[k];
    }

    vector<int> divisors = {0};  // nice of them to show me this edge case in samples :/
    int sum_working = sum;
    for ( int d = 1 ; d <= sum_working ; ++d ) {
        if ( sum_working % d == 0 ) {
            divisors.push_back( d );
        }
    }

    int out = 1e9;
    for ( auto& d : divisors ) {
        // can this d work?
        int num_blocks = 0;
        int extra = 0;
        for ( int k = 0 ; k < dat.size() ; ++k ) {
            extra += dat[k];
            if ( extra == d ) {
                extra = 0;
                ++num_blocks;
            }
            if ( extra > d ) {
                num_blocks = -1;
                continue;
            }
        }
        out = min( out , N - num_blocks );
    }
    cout << out << '\n';

    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    int T = 1;
    std::cin >> T;  // just comment this for one-case problems.
    for ( int k = 1 ; k <= T ; ++k ) {
        el; dbc("CASE" , k ); el;
        solve();
    }

    return 0;
}
