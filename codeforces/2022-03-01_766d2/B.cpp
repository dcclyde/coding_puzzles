
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
    int R, C;
    cin >> R >> C;
    db(R, C);

    vector<int> dist_from_center_counts( R*C , 0 );
    for ( int r = 0 ; r < R ; ++r ) {
        for ( int c = 0 ; c < C ; ++c ) {
            int dr = min(abs(r-(R/2)), abs(r-((R-1)/2)));
            int dc = min(abs(c-(C/2)), abs(c-((C-1)/2)));
            dist_from_center_counts[ dr+dc ] += 1;
        }
    }
    db( dist_from_center_counts );
    int curr = (R/2) + (C/2);
    int idx = 0;
    for ( int k = 0 ; k < R*C ; ++k ) {
        while ( dist_from_center_counts[idx] == 0 ) {
            ++idx;
            ++curr;
        }
        cout << curr << ' ';
        --dist_from_center_counts[idx];
    }
    cout << '\n';
    return;

    int total = 0;
    int prefix_total = 0;
    vector<int> diag_lengths;
    int smaller = min(R, C);
    for ( int k = 1 ; k < smaller ; ++k ) {
        diag_lengths.push_back( k );
        prefix_total += k;
        total += k;
    }
    db(diag_lengths);
    assert((R*C - 2*prefix_total) % smaller == 0);
    for ( int k = 0 ; k < (R*C - 2*prefix_total) / smaller ; ++k ) {
        diag_lengths.push_back( smaller );
        total += smaller;
    }
    for ( int k = smaller-1 ; k >= 1 ; --k ) {
        diag_lengths.push_back( k );
        total += k;
    }
    assert( total == R*C );

    for ( int k = 1 ; k < diag_lengths.size() ; ++k ) {
        for ( int rep = 0 ; rep < diag_lengths[k] ; ++rep ) {
            cout << k << ' ';
        }
    }
    cout << '\n';

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
