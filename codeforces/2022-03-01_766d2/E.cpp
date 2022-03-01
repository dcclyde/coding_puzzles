
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


ll INF = 2e18;

struct Ladder {
    int r1; int c1;
    int r2; int c2;
    int hp;
};

void solve() {
    int R, C, num_ladders;
    cin >> R >> C >> num_ladders;
    vector<int> horiz_cost_per_floor( R );
    for ( int k = 0 ; k < R ; ++k ) {
        cin >> horiz_cost_per_floor[k];
    }
    db( horiz_cost_per_floor );

    vector<tuple<int, int, int, int, int>> ladders;
    for ( int k = 0 ; k < num_ladders ; ++k ) {
        int r1, c1, r2, c2, hp;
        cin >> r1 >> c1 >> r2 >> c2 >> hp;
        --r1; --c1; --r2; --c2;
        ladders.emplace_back( r1, c1, r2, c2, hp );
    }
    sort( ladders.begin() , ladders.end() );
    for ( int k = 0 ; k < ladders.size() ; ++k ) {
        db( k , ladders[k] );
    }

    // invent an extra ladder to help with extraction.
    ladders.emplace_back( R-1 , C-1 , R , 0 , 0 );

    vector<map<int, ll>> dp( R+1 );
    dp[0][0] = 0;
    dp[R][0] = INF;
    int lidx = 0;

    // avoid realloc
    // todo test whether this actually helps
    auto it1 = dp[0].begin();
    auto it2 = dp[0].begin();
    auto rit1 = dp[0].rbegin();
    auto rit2 = dp[0].rbegin();

    for ( int r = 0 ; r < R ; ++r ) {
        el; dbc("START ROW" , r ); el;
        while ( get<0>( ladders[lidx] ) < r ) {
            ++lidx;
        }
        if ( get<0>( ladders[lidx] ) != r ) {
            dbc("no ladder starts");
            continue;
        }
        auto& dprow = dp[r];
        it1 = dprow.begin();
        if ( it1 == dprow.end() ) {
            dbc("no ladder ends");
            continue;
        }

        /*
            Do some DP stuff to build the best cost
            at each ladder END on floor r.
        */
        it2 = dprow.begin();
        ++it2;
        dbc("pre update" , dprow );
        db();
        while ( it2 != dprow.end() ) {
            db();
            it2->second = min(
                it2->second,
                it1->second + horiz_cost_per_floor[r] * (it2->first - it1->first)
            );
            ++it1; ++it2;
        }
        db();
        rit1 = dprow.rbegin();
        rit2 = dprow.rbegin();
        ++rit2;
        while ( rit2 != dprow.rend() ) {
            // db();
            // db(*rit1, *rit2);
            // db(it2->second);
            // db(it1->second);
            // db(horiz_cost_per_floor[r]);
            // db(it2->first);
            // db(it1->first);
            rit2->second = min(
                rit2->second,
                rit1->second + horiz_cost_per_floor[r] * (rit2->first - rit1->first)
            );
            ++rit1; ++rit2;
            db();
        }
        dbc("post update" , dprow );

        // now find costs at ladder bases, and update costs at their ends.
        while ( true ) {
            if ( lidx >= ladders.size() ) {
                break;
            }
            auto& [lr1, lc1, lr2, lc2, lhp] = ladders[lidx];
            if ( lr1 != r ) {
                break;
            }
            ++lidx;
            // find cheapest way to get to (r, lc1).
            auto& dpout = dp[lr2][lc2];
            dpout = INF;
            it1 = dprow.lower_bound( lc1 );
            dbc("dp ladder" , lr1 , lc1 );
            if ( it1 != dprow.end() ) {
                ll option = -lhp + it1->second + (it1->first - lc1) * horiz_cost_per_floor[r];
                dpout = min(
                    dpout,
                    option
                );
                dbc("update R" , option , -lhp , it1->second , (it1->first - lc1) , horiz_cost_per_floor[r] );
            }
            if ( it1 != dprow.begin() ) {
                --it1;
                ll option = -lhp + it1->second + (lc1 - it1->first) * horiz_cost_per_floor[r];
                dpout = min(
                    dpout,
                    option
                );
                dbc("update L" , option , -lhp , it1->second , (lc1 - it1->first) , horiz_cost_per_floor[r] );
            }
            dbc("dpout" , lr1, lc1, lr2, lc2, dpout);
        }

    }
    dbc("main loop done");
    if ( dp[R][0] == INF ) {
        cout << "NO ESCAPE\n";
    } else {
        cout << dp[R][0] << '\n';
    }

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
