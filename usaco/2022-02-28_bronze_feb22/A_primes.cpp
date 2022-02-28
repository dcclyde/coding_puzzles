// partial code before I realized that I shouldn't need to bother with primes
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

vector<int> precompute() {
    // grab all primes up to 1e6.
    int N = 1e6 + 1;
    vector<bool> is_prime( N , true );
    vector<int> primes;
    for ( int p = 2 ; p < N ; ++p ) {
        if ( !p ) {
            primes.push_back( p );
            continue;
        }
        for ( int m = 2 ; m*p < N ; ++m ) {
            is_prime[ m*p ] = false;
        }
    }
    return primes;
}




void solve(vector<int>& primes) {
    int N; cin >> N;
    vector<int> dat( N );
    int sum = 0;
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> dat[k];
        sum += dat[k];
    }
    map<int,int> prime_factorization;
    int pidx = 0;
    int sum_working = sum;
    while ( sum_working > 1 ) {

    }




    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    auto primes = precompute();

    int T = 1;
    std::cin >> T;  // just comment this for one-case problems.
    for ( int k = 1 ; k <= T ; ++k ) {
        el; dbc("CASE" , k ); el;
        solve(primes);
    }

    return 0;
}
