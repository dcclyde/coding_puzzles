
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
    vector<int> A(N), B(N), Ainv(N+1);
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> A[k];
        Ainv[A[k]] = k;
    }
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> B[k];
    }

    vector<bool> seen( N+1 , false );
    int out = 0;
    int Aidx = 0;
    for ( int k = 0 ; k < N ; ++k ) {
        // do we need to move cow B[k]?
        // Basically just ask whether B[k] is already at the start.
        // don't count cows we've already seen+processed though.
        db( k , B[k] , Aidx , A[Aidx] , seen );
        while ( seen[A[Aidx]] ) {
            ++Aidx;
        }
        db( k , B[k] , Aidx , A[Aidx] , seen ); el;
        if ( B[k] != A[Aidx] ) {
            ++out;
            db(out);
        }
        seen[B[k]] = true;
    }
    cout << out << '\n';

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
