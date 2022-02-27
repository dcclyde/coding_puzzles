
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
    map<int, int> counts;
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> dat[k];
        ++counts[ dat[k] ];
    }

    // is it doable?
    for ( auto& pr : counts ) {
    // for ( const auto& pr : counts ) {  // seems not necessary
    // for ( const auto& [key, val] : counts ) {  // doesn't work I think
        if ( pr.second % 2 == 1 ) {
            cout << "-1\n";
            return;
        }
    }

    int start_idx = 0;
    int offset = 0;
    vector<pair<int, int>> ops_out;
    vector<int> lens_out;
    vector<int> new_front;
    while ( start_idx < dat.size() ) {
        int prev_start_idx = start_idx;
        int start_val = dat[ start_idx ];
        ++start_idx;
        while ( dat[start_idx] != start_val ) {
            ++start_idx;
        }
        db( prev_start_idx , start_idx , offset , dat );
        /*
        Example: We have [3, 5, 8, 2, 4, 3, ...].
        Insert 5 just after the 3, then 8 one position later than that, etc.
        dist is 5 and we'll insert 4 things.
        */
        int dist = start_idx - prev_start_idx;
        lens_out.push_back( dist * 2 );
        new_front.clear();
        db()

        for ( int k = 0 ; k < start_idx - 1 ; ++k ) {
            new_front.push_back( dat[ prev_start_idx + 1 + k ] );
            ops_out.emplace_back( offset + dist + 1 + k , new_front.back() );
        }
        db()
        // start_idx = prev_start_idx + 1;
        start_idx = 0;
        reverse( new_front.begin() , new_front.end() );
        new_front.insert( new_front.end() , dat.begin() + dist + 1 , dat.end() );
        dat = new_front;

        offset += 2 * dist;
        db( start_idx , dat );

    }
    cout << ops_out.size() << '\n';
    for ( auto& pr : ops_out ) {
        cout << pr.first << ' ' << pr.second << '\n';
    }
    cout << lens_out.size() << '\n';
    for ( auto& x : lens_out ) {
        cout << x << ' ';
    }
    cout << '\n';
    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    int T = 1;
    std::cin >> T;  // just comment this for one-case problems.
    for ( int k = 1 ; k <= T ; ++k ) {
        dbc("CASE" , k );
        solve();
    }

    return 0;
}
