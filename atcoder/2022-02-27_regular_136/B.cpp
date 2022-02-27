
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



pair<int, int> helper(vector<int>& X, const vector<int>& X_sorted) {
    int N = X.size();
    for ( int j = 0 ; j < N-2 ; ++j ) {
        db( j , X );
        int pos = j;
        while ( X[pos] != X_sorted[j] ) {
            ++pos;
        }
        while ( pos >= j+2 ) {
            swap( X[pos] , X[pos-1] );
            swap( X[pos-1] , X[pos-2] );
            pos -= 2;
        }
        if ( pos == j+1 ) {
            swap( X[pos] , X[pos-1] );
            swap( X[pos] , X[pos+1] );
            pos -= 1;
        }
        assert( pos == j );
    }
    return { X[N-2] , X[N-1] };
}


void solve() {
    int N; cin >> N;
    vector<int> A( N ), B( N );
    map<int,int> A_counts, B_counts;
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> A[k];
        A_counts[A[k]] += 1;
    }
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> B[k];
        B_counts[A[k]] += 1;
    }

    db();
    auto A_sorted = A;
    auto B_sorted = B;
    sort(A_sorted.begin(), A_sorted.end());
    sort(B_sorted.begin(), B_sorted.end());
    for ( int k = 0 ; k < N ; ++k ) {
        if ( A_sorted[k] != B_sorted[k] ) {
            cout << "No\n";
            return;
        }
    }

    db();
    for ( auto& pr : A_counts ) {
        if ( pr.second > 1 ) {
            cout << "Yes\n";
            return;
        }
    }

    db();
    auto pa = helper( A , A_sorted );
    auto pb = helper( B , B_sorted );

    db();
    if ( pa == pb ) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

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
