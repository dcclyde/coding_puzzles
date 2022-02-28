
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define MP make_pair
#define MT make_tuple
#define pii pair<int,int>
#define pll pair<ll, ll>

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

template<class T>
struct HASH{
    size_t operator()(const pair<T,T>&x)const{
        return hash<ll>()(((ll)x.first)^(((ll)x.second)<<32));
    }
};


void dp_helper(
    vector<pll>::iterator start,
    vector<pll>::iterator end,
    vector<vector<unordered_map<pll, ll, HASH<ll>>>>& out
) {
    int N = end - start;
    auto curr = start;
    out.clear();
    out.resize( N+1 );  // 0 <= n <= N

    // base case
    out[0].resize( 1 );
    out[0][0][MP(0,0)] = 1;

    for ( int n = 1 ; n <= N ; ++n ) {
        out[n].resize( n+1 );  // 0 <= k <= n

        // now iterate over all data from n-1.
        for ( int k = 0 ; k <= n-1 ; ++k ) {
            for ( auto& [pos, count] : out[n-1][k] ) {
                out[n][k][pos] += count;
                out[n][k+1][MP(pos.first + curr->first, pos.second + curr->second)] += count;
            }
        }
        ++curr;
    }
    return;
}


void solve() {
    int N; cin >> N;
    pll goal; cin >> goal.first >> goal.second;
    vector<pll> dat( N );
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> dat[k].first >> dat[k].second;
    }

    vector<vector<unordered_map<pll, ll, HASH<ll>>>> dpA;
    vector<vector<unordered_map<pll, ll, HASH<ll>>>> dpB;
    int cutoff = N / 2;
    db(cutoff);

    dp_helper( dat.begin() , dat.begin() + cutoff , dpA );
    dp_helper( dat.begin() + cutoff , dat.end() , dpB );

    auto& outA = dpA.back();
    auto& outB = dpB.back();
    for ( int k = 0 ; k < outA.size() ; ++k ) {
        db(k, outA[k]);
    }
    el;
    for ( int k = 0 ; k < outB.size() ; ++k ) {
        db(k, outB[k]);
    }
    el;

    vector<ll> out_final( N+1 , 0 );
    out_final.front() = -14;  // make it obvious if I accidentally print this
    for ( int kB = 0 ; kB < outB.size() ; ++kB ) {
        for ( auto& [posB, countB] : outB[kB] ) {
            pll needed = {goal.first - posB.first , goal.second - posB.second};
            for ( int kA = 0 ; kA < outA.size() ; ++kA ) {
                if ( outA[kA].count(needed) ) {
                    out_final[ kA + kB ] += outA[kA][needed] * countB;
                }
            }
        }
    }
    for ( int k = 1 ; k <= N ; ++k ) {
        cout << out_final[k] << '\n';
    }

    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    int T = 1;
    // std::cin >> T;  dbc("loading num cases!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")  // just comment this for one-case problems.
    for ( int k = 1 ; k <= T ; ++k ) {
        el; dbc("CASE" , k ); el;
        solve();
    }

    return 0;
}
