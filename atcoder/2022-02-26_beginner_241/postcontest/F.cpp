
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
    // cout << "-1\n"; return;
    int H, W, num_obstacles;
    cin >> H >> W >> num_obstacles;

    map<int, set<int>> obs_horiz;  // obstacles we see when looking horizontally along a certain line
    map<int, set<int>> obs_vert;   // same but looking vertically

    int start_h, start_w;
    cin >> start_h >> start_w;
    // --start_h;
    // --start_w;

    int goal_h, goal_w;
    cin >> goal_h >> goal_w;
    // --goal_h;
    // --goal_w;
    for ( int k = 0 ; k < num_obstacles ; ++k ) {
        int obs_h, obs_w;
        cin >> obs_h >> obs_w;
        // --obs_h;
        // --obs_w;
        obs_horiz[ obs_h ].insert( obs_w );
        obs_vert[  obs_w ].insert( obs_h );
    }

    db(obs_horiz);
    db(obs_vert);

    set<pair<int, int>> seen;
    deque<tuple<int, int, int>> todo;
    seen.emplace( start_h , start_w );
    todo.emplace_back( start_h , start_w , 0 );

    string dirs = "NSEW";

    auto it = obs_vert[0].begin();
    dbc("Start BFS.");
    while ( todo.size() > 0 ) {
        auto curr = todo.front();
        todo.pop_front();
        int curr_h, curr_w, curr_steps;
        tie( curr_h , curr_w , curr_steps ) = curr;

        if ( curr_h == goal_h && curr_w == goal_w ) {
            cout << curr_steps << '\n';
            return;
        }

        db(curr, todo);
        // try each direction.
        for ( char& dir : dirs ) {
            if ( dir == 'N' ) {
                // H gets smaller.
                if ( !obs_vert.count( curr_w ) ) {
                    continue;
                }
                auto& axis = obs_vert[ curr_w ];
                it = axis.lower_bound( curr_h );  // *it is slightly bigger than curr pos.
                if ( it == axis.begin() ) {
                    continue;
                }
                --it;
                int new_h = (*it) + 1;
                if ( seen.count( {new_h , curr_w} ) ) {
                    continue;
                }
                seen.emplace( new_h , curr_w );
                todo.emplace_back( new_h , curr_w , curr_steps + 1 );
                dbc("np" , dir , MP(new_h, curr_w) , todo.back() );
            }
            if ( dir == 'S' ) {
                // H gets larger.
                if ( !obs_vert.count( curr_w ) ) {
                    continue;
                }
                auto& axis = obs_vert[ curr_w ];
                it = axis.lower_bound( curr_h );
                if ( it == axis.end() ) {
                    continue;
                }
                int new_h = (*it) - 1;
                if ( seen.count( MP(new_h , curr_w) ) ) {
                    continue;
                }
                seen.emplace( new_h , curr_w );
                todo.emplace_back( new_h , curr_w , curr_steps + 1 );
                dbc("np" , dir , MP(new_h, curr_w) , todo.back() );
            }
            if ( dir == 'W' ) {
                // W gets smaller.
                if ( !obs_horiz.count( curr_h ) ) {
                    continue;
                }
                auto& axis = obs_horiz[ curr_h ];
                it = axis.lower_bound( curr_w );
                if ( it == axis.begin() ) {
                    continue;
                }
                --it;
                int new_w = (*it) + 1;
                if ( seen.count( MP(curr_h , new_w) ) ) {
                    continue;
                }
                seen.emplace( curr_h , new_w );
                todo.emplace_back( curr_h , new_w , curr_steps + 1 );
                dbc("np" , dir , MP(curr_h, new_w) , todo.back() );
            }
            if ( dir == 'E' ) {
                // W gets larger.
                dbc("a");
                if ( !obs_horiz.count( curr_h ) ) {
                    continue;
                }
                dbc("b");
                auto& axis = obs_horiz[ curr_h ];
                it = axis.lower_bound( curr_w );
                if ( it == axis.end() ) {
                    continue;
                }
                dbc("c");
                int new_w = (*it) - 1;
                if ( seen.count( MP(curr_h , new_w) ) ) {
                    continue;
                }
                dbc("d");
                seen.emplace( curr_h , new_w );
                todo.emplace_back( curr_h , new_w , curr_steps + 1 );
                dbc("np" , dir , MP(curr_h, new_w) , todo.back() );
            }
        }

    }

    cout << -1 << '\n';
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
