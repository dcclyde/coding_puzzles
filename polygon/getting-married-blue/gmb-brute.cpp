#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

// Is (a, b) a legal pairing?
bool legal(ll a, ll b) {
    return a <= 2*b && b <= 2*a;
}

ll tax(ll a) {return 4*a*a;}
ll tax(ll a, ll b) {return 2*(a+b)*(a+b);}

void brute() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(auto& a : A) {cin >> a;}
    sort(A.begin(), A.end());

    ll best = 0;
    for(auto& a : A) {best += tax(a);}

    vector<bool> used(N);

    // For each element in A, try all possible later elements as potential matches.
    auto dfs = [&](auto&& self, ll ai, ll cost) -> void {
        if (ai == N) {
            best = min(best, cost);
            return;
        }
		if (used[ai]) {return self(self, ai+1, cost);}
        for (int bi = ai+1; bi < N; ++bi) {
            if (!legal(A[ai], A[bi])) {continue;}
            if (used[bi]) {continue;}
            used[bi] = true;
            self(self, ai+1, cost + tax(A[ai], A[bi]));
            used[bi] = false;
        }
        // Also try leaving ai unpaired.
        self(self, ai+1, cost + tax(A[ai]));
    };
    dfs(dfs, 0, 0);
    cout << best << endl;
    return;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    brute();
    return 0;
}
