/*
    dcclyde's implementation of Mo's Algorithm.
    See also Benq's code in 1D Range Queries (9.2)/Mo (15.1).h
*/

#pragma region  // Mo's Algorithm
struct Mo {
    using t3 = tuple<ll, ll, ll>;
    ll N = -1; ll Q = -1;
    V<ll> A;
    V<t3> queries;
    V<ll> out;
    ll BLOCK = -1;

    // ! State to be updated
    ll l, r;
    ll ans;
    V<ll> cnt;

    void init(ll N_, ll Q_) {
        N = N_;
        Q = Q_;
        A.rsz(N);
        queries.rsz(Q);
        out.rsz(Q);
        BLOCK = sqrt(N);  // ! Tune as needed.

        // ! Initial state
        l = 0; r = -1;
        ans = 0;
        cnt.assign(2'000'001, 0);
    }

    void modify(ll idx, ll c) {
        // ! Update state when we add/remove idx.
        ll v = A[idx];
        if (cnt[v] == 0) { ++ans; }
        cnt[v] += c;
        if (cnt[v] == 0) { --ans; }
    }
    void solve_one(ll L, ll R) {
        while (l > L) {
            --l;
            modify(l, 1);
        }
        while (r < R) {
            ++r;
            modify(r, 1);
        }
        while (l < L) {
            modify(l, -1);
            ++l;
        }
        while (r > R) {
            modify(r, -1);
            --r;
        }
    }
    void solve() {
        auto cmp = [&](const t3& a, const t3& b) -> bool {
            const auto& [la, ra, qa] = a;
            const auto& [lb, rb, qb] = b;
            if (la / BLOCK != lb / BLOCK) return la < lb;
            return la / BLOCK % 2 ? ra < rb : ra > rb;
        };
        sort(all(queries), cmp);
        for (auto& [L, R, qid] : queries) {
            solve_one(L, R);
            out[qid] = ans;
        }
    }
};
#pragma endregion  // Mo's Algorithm


// Typical solve() for Mo's
void solve() {
    lls(N, Q);
    V<ll> dat;
    rv(N, dat);

    Mo mo;
    mo.init(N, Q);
    swap(dat, mo.A);
    dbgR(N, Q, mo.A);
    el;
    FOR(qid, 0, Q) {
        ll1(L, R);
        mo.queries[qid] = MT(L, R, qid);
    }
    mo.solve();
    return pvn(mo.out);
}
