
// ! ---------------------------------------------------------------------------

#include <bits/stdc++.h>
using ll = long long;
using namespace std;
template<class T> using V = vector<T>;



struct TwoFairDice {

    ll finish(vector<int>& A, vector<int>& B) {
        vector<ll> helper(13);  // h[k] = num ways to have 2*W + Draws add up to k.

        auto get_score = [&](int k) {
            int score = 0;
            for ( int idx = 0 ; idx < 6 ; ++idx ) {
                if ( k > A[idx] ) {
                    score += 2;
                } else if ( k == A[idx] ) {
                    score += 1;
                }
            }
            return score;
        };

        for ( int k = 0 ; k <= 1000 ; ++k ) {
            int score = get_score(k);
            ++helper[score];
        }

        V<V<ll>> dp(7, V<ll>(73));
        // insert the faces we're already given.
        int score_already = 0;
        int faces_already = 0;
        for ( auto& x : B ) {
            int score = get_score(x);
            score_already += score;
            ++faces_already;
        }
        dp[faces_already][score_already] = 1;

        for ( int face = faces_already ; face < 6 ; ++face ) {
            for ( int score = 0 ; score <= 12 ; ++score ) {
                ll ways = helper[score];
                for ( int prev_score = 0 ; prev_score <= 36 ; ++prev_score ) {
                    dp[face + 1][prev_score + score] += dp[face][prev_score] * ways;
                }
            }
        }

        return dp[6][36];
    }
};

