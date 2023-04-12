#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool legal(ll a, ll b) {
    return a <= b;
}

ll tax(ll a) {return 4*a*a;}
ll tax(ll a, ll b) {return 2*(a+b)*(a+b);}

void brute() {
    ll nA, nB; cin >> nA >> nB;
    vector<ll> A(nA), B(nB);
    for(auto& a : A) {cin >> a;}
    for(auto& b : B) {cin >> b;}
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    ll best = 0;
    for(auto& a : A) {best += tax(a);}
    for(auto& b : B) {best += tax(b);}

    vector<bool> used(nB);

    // For each element in A, try all possible elements in B as potential matches.
    auto dfs = [&](auto&& self, ll ai, ll cost) -> void {
        if (ai == nA) {
            ll leftover_b_cost = 0;
            for (int bi = 0; bi < nB; ++bi) {
                if (!used[bi]) {leftover_b_cost += tax(B[bi]);}
            }
            best = min(best, cost + leftover_b_cost);
            return;
        }
        for (int bi = 0; bi < nB; ++bi) {
            if (!legal(A[ai], B[bi])) {continue;}
            if (used[bi]) {continue;}
            used[bi] = true;
            self(self, ai+1, cost + tax(A[ai], B[bi]));
            used[bi] = false;
        }
        // Also try leaving ai unpaired.
        self(self, ai+1, cost + tax(A[ai]));
    };
    dfs(dfs, 0, 0);

    cout << best << endl;
    return;
}


void solve() {
    ll nA, nB; cin >> nA >> nB;
    vector<ll> A(nA), B(nB);
    for(auto& a : A) {cin >> a;}
    for(auto& b : B) {cin >> b;}
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    ll out = 0;
    for(auto& a : A) {out += tax(a);}
    for(auto& b : B) {out += tax(b);}

    for ( int k = 0 ; k < min(nA, nB) ; ++k ) {
        if (!legal(A[k], B[nB-1-k])) {break;}
        out -= tax(A[k]);
        out -= tax(B[nB-1-k]);
        out += tax(A[k], B[nB-1-k]);
    }

    cout << out << endl;
    return;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
    return 0;
}
