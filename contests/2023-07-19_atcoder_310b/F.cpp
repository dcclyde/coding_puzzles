#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <assert.h>
using namespace std;

/*
    N <= 100
    A_k <= 1e6

    *****

    I only care about summing to 10.
    Almost could be some very fancy FFT variant stuff...
    Never mind that here though.

    dp[n][t] = probability that first n dice can sum to t.

    dp[n][t] = ?
        if dp[n-1][t] works out, we're good.
        Otherwise,


    ~~~~~

    There really aren't that many interesting partitions of stuff < 10.

    I could think about just
    dp[n][mask] = prob that first n dice give exactly mask.

    That's N * 2^11 dp states
    each one costs like 10 time?
    should be fine?
*/

using ll = long long;

const ll MOD = 998'244'353;

ll powmod(ll b, ll e, ll mod) {
    ll out = 1;
    while (e > 0) {
        if (e % 2 == 1) {
            out *= b;
            out %= mod;
        }
        b *= b; b %= mod;
        e /= 2;
    }
    return out;
}

int main() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(auto& x : A) {cin >> x;}

    // probability of rolling any fixed value.
    // rp[k] = 1/A[k] mod MOD.
    vector<ll> roll_prob(N);
    for(int k = 0; k < N; ++k) {
        roll_prob[k] = powmod(A[k], MOD-2, MOD);
        assert((roll_prob[k] * A[k]) % MOD == 1);
    }

    ll MASK_END = (1 << 11);  // 0 through 10. Could save a bit if I wanted.

    vector<vector<ll>> dp(N+1, vector<ll>(MASK_END, 0));

    /*
        base case:
        dp[0][0] = 1
        dp[0][mask] = 0 otherwise
    */
    dp[0][1] = 1;

    for(int n = 1; n <= N; ++n) {
        for(int mask = 0; mask < MASK_END; ++mask) {
            if (dp[n-1][mask] == 0) {continue;}
            for(int roll = 1; roll <= 10; ++roll) {
                if (roll > A[n-1]) {break;}
                ll new_mask = mask | (mask << roll);
                new_mask &= (MASK_END - 1);  // discard sums above 10
                dp[n][new_mask] += dp[n-1][mask] * roll_prob[n-1];
                dp[n][new_mask] %= MOD;
                // cerr << '\t' << mask << '\t' << roll << '\t' << new_mask << '\t' << dp[n-1][mask] << '\t' << dp[n][new_mask] << endl;
            }
        }
    }

    ll out = 0;
    for(int mask = 0; mask < MASK_END; ++mask) {
        if ((mask & (1<<10)) == 0) {continue;}
        out += dp[N][mask];
        out %= MOD;
    }

    cout << out << endl;
    return 0;
}
