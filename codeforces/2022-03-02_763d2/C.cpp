
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


ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down




void solve() {
    int N; cin >> N;
    vector<ll> dat( N );
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> dat[k];
    }

    // just binary search I guess?

    /*
        Strategy:
        Always give enough to save the k-2 slot.
        If I have more than S, might as well at least go down to S.

        Say k-1 slot has A and I have B. I'm going to pass k more times.
        Then it'll be ( A+k , B-3k ).

        Next guy is going to pass at least (S-(A+k)) / 2 times.
        Then it'll be ( S , B - 3k + (S-A-k) / 2 ).
        OK, so I think I should only give away "surplus"
            so that formula spits out S.

    */

    ll lo = 0;  // obviously possible
    ll hi = 2e9;  // definitely not possible
    vector<ll> working( N );
    while ( hi - lo > 1 ) {
        ll S = (lo + hi) / 2;

        // // give[k] = num times we apply the operation on k.
        // // that means slot k loses 3*give[k] stones.
        // // slot k-1 adds h
        // // slot k-2 adds 2h
        // bool ok = true;
        // el;dbc( "start" , S );
        // for ( int k = 2 ; k < N ; ++k ) {
        //     give[k] = 0;
        //     ll curr_k = dat[k];
        //     ll curr_km2 = dat[k-2] - 3*give[k-2] + give[k-1];
        //     ll curr_km1 = dat[k-1] - 3*give[k-1];
        //     if ( curr_km2 < S ) {
        //         int local = cdiv( S - curr_km2 , 2 );
        //         give[k] += local;
        //         curr_km2 += local * 2;
        //         curr_km1 += local;
        //         curr_k -= local * 3;
        //     }
        //     if ( curr_k < 0 ) {
        //         ok = false;
        //         break;
        //     }
        //     if ( curr_k > S ) {
        //         int local = (curr_k - S) / 3;
        //         give[k] += local;
        //         curr_km1 += local;
        //         curr_k -= 3*local;
        //     }
        //     if ( curr_km1 >= S ) {
        //         continue;
        //     }

        //     /*
        //         I want cdiv(S-A-x, 2) ~ S-B+3x.
        //         S/2 - A/2 - x/2 = S - B + 3x
        //         S/2 - A/2 + B = 3.5x
        //     */
        //     ll A = curr_km1;
        //     ll B = curr_k;
        //     ll x_approx = ( S/2. - A / 2. + B ) / 3.5;
        //     ll best_x = -1e18;
        //     ll best_result = 1e18;
        //     for ( int offset = -5 ; offset <= 5 ; ++offset ) {
        //         ll x_local = x_approx + offset;
        //         ll curr = max(
        //             cdiv(S - A - x_local, 2),
        //             S - B - 3*x_local
        //         );
        //         if ( curr < best_result ) {
        //             best_result = curr;
        //             best_x = x_local;
        //         }
        //     }
        //     give[k] += best_x;

        // }
        // if ( dat[N-1] - 3*give[N-1] < S ) {
        //     ok = false;
        // }
        // if ( dat[N-2] - 3*give[N-2] + give[N-1] < S ) {
        //     ok = false;
        // }

        // dbc("HARDCODING");
        // S = 3;

        copy( dat.begin() , dat.end() , working.begin() );

        bool ok = true;
        el;dbc( "start" , S );
        for ( int k = N-1 ; k >= 2 ; --k ) {
            db( k , working );
            if ( working[k] < S ) {
                ok = false;
                break;
            }
            if ( working[k] > S ) {
                int steps = min(
                    (working[k] - S) / 3,
                    dat[k] / 3
                );
                working[k] -= 3*steps;
                working[k-1] += steps;
                working[k-2] += 2*steps;
            }
        }
        db( ok , working );
        if ( working[1] < S || working[0] < S ) {
            ok = false;
        }

        if ( ok ) {
            lo = S;
            dbc("GOOD" , S );
        } else {
            hi = S;
            dbc("BAD" , S );
        }
        // exit(1);
    }

    cout << lo << '\n';
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
