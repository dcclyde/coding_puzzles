
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




void helper(
    const vector<string>& blocks,
    unordered_set<string>& words_created,
    const vector<int>& blocks_local,
    string& sofar
) {
    if ( sofar.size() == blocks_local.size() ) {
        words_created.insert(sofar);
        return;
    }
    sofar.push_back(' ');
    // db(blocks, blocks_local, sofar);
    for ( int k = 0 ; k < 6 ; ++k ) {
        // auto local_block_num = sofar.size() - 1;
        // db(local_block_num);
        // auto block_data = blocks_local[ local_block_num ];
        // db(block_data);
        // auto char_extracted = blocks[ block_data ][ k ];
        // db(char_extracted);
        // el;
        sofar.back() = blocks[ blocks_local[ sofar.size()-1 ] ][ k ];
        helper(blocks, words_created, blocks_local, sofar);
    }
    sofar.pop_back();
    return;
}

void solve() {
    int N; cin >> N;
    vector<string> blocks( 4 );
    for ( int k = 0 ; k < 4 ; ++k ) {
        cin >> blocks[k];
    }
    vector<string> desired_words( N );
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> desired_words[k];
    }
    db(blocks);
    db(desired_words);

    // just make all possible words.
    unordered_set<string> words_created;
    vector<int> blocks_local;
    string sofar;
    for ( int blocks_used_mask = 1 ; blocks_used_mask < (1<<4) ; ++blocks_used_mask ) {
        blocks_local.clear();
        for ( int bid = 0 ; bid < 4 ; ++bid ) {
            if ( (blocks_used_mask >> bid) & 1 ) {
                blocks_local.push_back( bid );
            }
        }
        do {
            sofar.clear();
            helper( blocks , words_created , blocks_local , sofar );
        } while ( next_permutation( blocks_local.begin() , blocks_local.end() ) );
    }

    for ( auto& word : desired_words ) {
        if ( words_created.count( word ) ) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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
