
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
    int num_folders; cin >> num_folders;
    int N; cin >> N;  // num emails
    int S; cin >> S;  // screen size
    vector<int> dat( N );
    vector<pair<int,int>> bounds_per_folder( num_folders + 1 , MP(-1,-1) );
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> dat[k];
        if ( bounds_per_folder[dat[k]].first == -1 ) {
            bounds_per_folder[dat[k]].first = k;  // first occurrence
        }
        bounds_per_folder[dat[k]].second = k;  // last occurrence
    }

    int fidx = 1;  // folders are 1-indexed.
    int start = 0;
    int end = 0;
    int visible = 0;  // num unfiled emails in [start, end)
    vector<int> visible_per_folder( num_folders + 1 , 0 );

    db( num_folders , N , S );
    db( dat );
    db( bounds_per_folder );
    el; el;
    while ( true ) {
        el; dbc("step 0", fidx , start , end , visible , visible_per_folder );
        // Step 0: increment end or decrement start until visible == S.
        while ( visible < S && end < N ) {
            if ( dat[end] >= fidx + S ) {
                ++visible;
                ++visible_per_folder[ dat[end] ];
            }
            ++end;
        }
        while ( visible < S && start >= 1 ) {
            --start;
            if ( dat[start] >= fidx + S ) {
                ++visible;
                ++visible_per_folder[ dat[start] ];
            }
        }
        if ( visible < S ) {
            // we can see all remaining emails.
            cout << "YES\n";
            return;
        }

        dbc("step 1", fidx , start , end , visible , visible_per_folder );
        // Step 1: Scroll down until we can file all emails for folder fidx.
        auto&[lower, upper] = bounds_per_folder[fidx];
        if ( lower != -1 ) {
            // this folder is relevant.
            if ( lower < start ) {
                cout << "NO\n";
                return;
            }
            while ( true ) {
                // move end as far forward as we can file.
                while ( end <= upper && dat[end] < fidx + S ) {
                    ++end;
                }
                if ( end > upper ) {
                    break;
                }

                // move start forward one "real" step.
                while ( dat[start] < fidx + S ) {
                    ++start;
                }
                --visible;
                --visible_per_folder[ dat[start] ];
                ++start;

                // move end forward accordingly.
                while ( visible < S && end <= upper ) {
                    if ( dat[end] < fidx + S ) {
                        ++visible;
                        ++visible_per_folder[ dat[end] ];
                    }
                    ++end;
                }
            }
        }

        dbc("step 2", fidx , start , end , visible , visible_per_folder );
        // Step 2: scroll fidx down by 1.
        if ( fidx + S <= num_folders ) {
            visible -= visible_per_folder[ fidx + S ];
        }
        ++fidx;
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
