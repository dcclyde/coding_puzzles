
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define MP make_pair

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
    #define dbc(...) 43;
    #define db(...) 45;
    #define el
#endif

////////////////////////////////////////////////////////////////////////////////






void solve() {

    int H, W, num_obstacles;
    cin >> H >> W >> num_obstacles;

    vector<set<int>> obs_horiz( H );
    vector<set<int>> obs_vert( W );

    int start_h, start_w;
    cin >> start_h >> start_w;
    --start_h;
    --start_w;

    int goal_h, goal_w;
    cin >> goal_h >> goal_w;
    --goal_h;
    --goal_w;
    for ( int k = 0 ; k < num_obstacles ; ++k ) {
        int obs_h, obs_w;
        cin >> obs_h >> obs_w;
        --obs_h;
        --obs_w;
        obs_horiz[ obs_h ].insert( obs_w );
        obs_vert[  obs_w ].insert( obs_h );
    }
    db(obs_horiz);
    db(obs_vert);

    set<pair<int, int>> seen;
    queue<pair<pair<int,int>, int>> todo;
    seen.emplace( start_h , start_w );
    todo.push( MP( MP(start_h, start_w) , 0 ) );

    string dirs = "NSEW";

    auto it = obs_vert[0].begin();
    dbc("Start BFS.");
    while ( todo.size() > 0 ) {
        auto curr = todo.front();
        todo.pop();
        auto curr_pos = curr.first;
        int curr_h = curr_pos.first;
        int curr_w = curr_pos.second;
        int curr_steps = curr.second;

        if ( curr_h == goal_h && curr_w == goal_w ) {
            cout << curr_steps << '\n';
            return;
        }

        db(curr, todo);
        // try each direction.
        for ( char& dir : dirs ) {
            if ( dir == 'N' ) {
                // H gets smaller.
                auto& axis = obs_vert[ curr_w ];
                it = axis.lower_bound( curr_h );
                if ( it == axis.begin() ) {
                    continue;
                }
                --it;
                int new_h = (*it) + 1;
                if ( seen.count( MP(new_h , curr_w) ) ) {
                    continue;
                }
                seen.emplace( new_h , curr_w );
                todo.push( MP( MP(new_h, curr_w) , curr_steps + 1 ) );
                dbc("np" , dir , MP(new_h, curr_w) , todo.back() );
            }
            if ( dir == 'S' ) {
                // H gets larger.
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
                todo.push( MP( MP(new_h, curr_w) , curr_steps + 1 ) );
                dbc("np" , dir , MP(new_h, curr_w) , todo.back() );
            }
            if ( dir == 'W' ) {
                // W gets smaller.
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
                todo.push( MP( MP(curr_h, new_w) , curr_steps + 1 ) );
                dbc("np" , dir , MP(curr_h, new_w) , todo.back() );
            }
            if ( dir == 'E' ) {
                // W gets larger.
                auto& axis = obs_horiz[ curr_h ];
                it = axis.lower_bound( curr_w );
                if ( it == axis.end() ) {
                    continue;
                }
                int new_w = (*it) - 1;
                if ( seen.count( MP(curr_h , new_w) ) ) {
                    continue;
                }
                seen.emplace( curr_h , new_w );
                todo.push( MP( MP(curr_h, new_w) , curr_steps + 1 ) );
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
