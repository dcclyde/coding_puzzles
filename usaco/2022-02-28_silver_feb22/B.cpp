
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



vector<pair<pll, ll>> dp_helper(
    vector<pll>::iterator start,
    vector<pll>::iterator end
) {
    int N = end - start;
    auto it = start;

    vector<pair<pll, ll>> prev;
    vector<pair<pll, ll>> curr;  // pos, k
    prev.reserve(1<<N);
    curr.reserve(1<<N);

    curr.emplace_back(MP<ll,ll>(0,0), 0);

    for ( int n = 1 ; n <= N ; ++n ) {
        swap(curr, prev);
        curr.clear();
        auto curr_step = *it;
        for ( auto& [pos, k] : prev ) {
            curr.emplace_back(pos, k);
            curr.emplace_back(
                MP(pos.first + curr_step.first, pos.second + curr_step.second),
                k+1
            );
        }
        ++it;
        db(n, curr);
    }

    return curr;
}

template<class T>
struct PAIRHASH{
    size_t operator()(const pair<T,T>&x)const{
        return hash<ll>()(((ll)x.first)^(((ll)x.second)<<32));
    }
};

void solve() {
    int N; cin >> N;
    pll goal; cin >> goal.first >> goal.second;
    vector<pll> dat( N );
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> dat[k].first >> dat[k].second;
    }

    vector<vector<map<pll, ll>>> dpA;
    vector<vector<map<pll, ll>>> dpB;
    int cutoff = N / 2;
    db(cutoff);

    dbc("building outA");
    auto outA = dp_helper( dat.begin() , dat.begin() + cutoff );
    el;
    dbc("building outB");
    auto outB = dp_helper( dat.begin() + cutoff , dat.end() );
    el;

    db(outA);

    // pos -> (k -> count)
    unordered_map<pll, unordered_map<ll, ll>, PAIRHASH<ll>> structA;
    for ( auto& [pos, k] : outA ) {
        ++structA[pos][k];
    }
    db(structA);

    vector<ll> out_final( N+1 , 0 );
    out_final.front() = -14;  // make it obvious if I accidentally print this
    for ( auto& [posB, kB] : outB ) {
        pll needed = MP(goal.first - posB.first, goal.second - posB.second);
        if ( ! structA.count(needed) ) {
            continue;
        }
        auto& optionsA = structA[needed];
        for ( auto& [kA, countA] : optionsA ) {
            out_final[kA + kB] += countA;
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
