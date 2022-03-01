
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
    vector<vector<pair<int, int>>> graph( N );
    for ( int k = 0 ; k < N-1 ; ++k ) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        graph[a].emplace_back( b , k );
        graph[b].emplace_back( a , k );
    }
    db(graph);
    int leaf_pos = -1;
    for ( int k = 0 ; k < N ; ++k ) {
        if ( graph[k].size() > 2 ) {
            cout << "-1\n";
            return;
        }
        if ( graph[k].size() == 1 ) {
            leaf_pos = k;
        }
    }
    db(leaf_pos);

    // now just traverse the tree I guess.
    deque<int> todo;
    vector<bool> seen( N , false );
    vector<int> out( N-1 , -1 );

    todo.push_back( leaf_pos );
    seen[ leaf_pos ] = true;
    bool two_next = true;

    while ( todo.size() > 0 ) {
        db(todo);
        auto curr = todo.front();
        seen[curr] = true;
        todo.pop_front();
        for ( auto& [proposed, eidx] : graph[curr] ) {
            if ( seen[proposed] ) {
                continue;
            }
            out[ eidx ] = (two_next ? 2 : 3);
            two_next = ! two_next;
            todo.push_front( proposed );
        }
    }

    for ( int k = 0 ; k < out.size() ; ++k ) {
        cout << out[k] << ' ';
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
