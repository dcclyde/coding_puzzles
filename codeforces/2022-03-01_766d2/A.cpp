
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
    int R, C, rtarg, ctarg;
    cin >> R >> C >> rtarg >> ctarg;
    --rtarg; --ctarg;
    vector<string> dat( R , string( C , '?' ) );
    bool has_black = false;
    for ( int r = 0 ; r < R ; ++r ) {
        for ( int c = 0 ; c < C ; ++c ) {
            cin >> dat[r][c];
            if (dat[r][c] == 'B') {
                has_black = true;
            }
        }
    }
    db(dat);

    if ( ! has_black ) {
        cout << "-1\n";
        return;
    }
    if ( dat[rtarg][ctarg] == 'B' ) {
        cout << "0\n";
        return;
    }
    for ( int c = 0 ; c < C ; ++c ) {
        if ( dat[rtarg][c] == 'B' ) {
            cout << "1\n";
            return;
        }
    }
    for ( int r = 0 ; r < R ; ++r ) {
        if ( dat[r][ctarg] == 'B' ) {
            cout << "1\n";
            return;
        }
    }
    cout << "2\n";
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
