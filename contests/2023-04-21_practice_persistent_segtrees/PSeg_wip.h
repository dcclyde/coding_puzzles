/**
 * Description: Persistent min segtree with lazy updates, no propagation.
 	* If making \texttt{d} a vector then save the results of
 	* \texttt{upd} and \texttt{build} in local variables first to
 	* avoid issues when vector resizes in C++14 or lower.
 * Memory: O(N+Q\log N)
 * Source: CF, Franklyn Wang
 * Verification:
 	* https://codeforces.com/contest/1090/problem/G
 	* https://codeforces.com/gym/102423/submission/70170291

	PSEG_NODES_ALLOCATED sizing:
		(int, 1.25e7) made my code use 220mb here: https://codeforces.com/contest/1771/submission/202989566
		(int, 5e6 barely worked on that problem. 4e6 is too small though.)
 */

// ! Remember to update LIM, SZ using custom invocation.
const int PSEG_NODES_ALLOCATED = 1.25e7;  // ~ TODO tune using custom invocation
const int PSEG_POSITIONS = (1<<18);  // ~ 2^18 = 262144. TODO update using problem constraints

template<class T, class S, int SZ> struct PersistentSegTree {
	static const int LIM = PSEG_NODES_ALLOCATED;
	static const int sz = PSEG_POSITIONS;
	int orig_n = -1;
    const T idT = INF_i;  // ! IDseg
    const S idS = 0;  // ! IDlazy
	struct node {
		int l, r; T val = idT, lazy = idS;  // ! IDlazy  (val is unused)
		void inc(S x) { lazy += x; }  // ! lazy * lazy
		T get() { return val+lazy; }  // ! lazy * seg
	};
	node d[LIM]; int nex = 0;
	int copy(int c) { d[nex] = d[c]; return nex++; }
	T cmb(T a, T b) { return min(a,b); }  // ! seg * seg
	void pull(int c) { d[c].val =
		cmb(d[d[c].l].get(), d[d[c].r].get()); }
	//// MAIN FUNCTIONS
	T query(int c, int lo, int hi, int L, int R) {
		if (lo <= L && R <= hi) return d[c].get();
		if (R < lo || hi < L) return idT;
		int M = (L+R)/2;
		return d[c].lazy+cmb(query(d[c].l,lo,hi,L,M),
							query(d[c].r,lo,hi,M+1,R));  // ! lazy * seg (again)
	}
	int upd(int c, int lo, int hi, S v, int L, int R) {
		if (R < lo || hi < L) return c;
		int x = copy(c);
		if (lo <= L && R <= hi) { d[x].inc(v); return x; }
		int M = (L+R)/2;
		d[x].l = upd(d[x].l,lo,hi,v,L,M);
		d[x].r = upd(d[x].r,lo,hi,v,M+1,R);
		pull(x); return x;
	}
	int build(const auto& arr, int L, int R) {
		int c = nex++;
		if (L == R) {
			if (L < sz(arr)) d[c].val = arr[L];
			return c;
		}
		int M = (L+R)/2;
		d[c].l = build(arr,L,M), d[c].r = build(arr,M+1,R);
		pull(c); return c;
	}

    #pragma region  // lstTrue_from_base. TODO add fstTrue_from_base.
    // ~ lstTrue_from_base(L, check(v,r)) == lstTrue(L, orig_n-1, check(query(L,r), r)).
    int lstTrue_from_base(int L, int time, auto&& check) {
        assert(pct(SZ) == 1);  // SZ should be a power of 2.
        int n = SZ;
        int c = time;
        int l = 0; int r = n-1;
        auto m = [&]() -> int {return (l+r)>>1;};

        // dbgcBold("lsR", L, MT(ind,l,r), *this);
        // Special case: Check if the whole array is valid.
        pull(c);
        V<int> path;  // path holds all ancestors of c.
        if (L == 0 && check(d[c].get(), r)) {return orig_n-1;}

        auto move_DL = [&]() -> void { path.push_back(c); c = d[c].l; pull(c); r=m(); };
        auto move_DR = [&]() -> void { path.push_back(c); c = d[c].r; pull(c); l=m()+1; };
        auto move_U = [&]() -> void {
            int len = r-l+1;
            if (path.back().l == c) { r += len; }
            else { l -= len; }
            c = path.back(); path.pop_back(); pull(c);
        };
        auto move_R = [&]() -> void {
            int steps = 0;
            while (path.back().r == c) { move_U(); ++steps; }
            c = path.back().r; pull(c); len=(r-l+1); l+=len; r+=len;
            rep(steps) { move_DL(); }
        };

        while (l != L) {
            // dbgc("stage 1", ind,l,r, L);
            path.push_back(c);
            if (L <= m()) {move_DL();}
            else {move_DR();}
            pull(c);
        }

        T wip = idT;
        while (true) {
            T fut = cmb(wip, d[c].get());
            // dbgcP("stage 2", ind,l,r, "", fut);
            if (check(fut,r)) {  // If we can safely add this chunk...
                wip = fut;
                if (r == n-1) {
                    // We've reached the end.
                    return orig_n-1;
                } else if (path.back().r == c) {
                    // This was a right child.
                    move_U(); move_R();
                } else {
                    // This was a left child.
                    move_R();
                }
            } else { break; }
        }

        // (ind,l,r) would reach too far.
        while (l != r) {
            // does DL reach too far?
            pull(d[c].l);
            T fut = cmb(wip, d[d[c].l].get());
            if (check(fut,m())) {wip = fut; move_DR();}
            else {move_DL();}
        }
        int out = l-1;
        ckmin(out, orig_n-1);
        // dbgR(out); el;
        return out;
    }
    #pragma endregion  // lstTrue_from_base


	vi loc; //// PUBLIC
	void upd(int lo, int hi, S v) {
		loc.pb(upd(loc.bk,lo,hi,v,0,SZ-1)); }
	T query(int ti, int lo, int hi) {
		return query(loc[ti],lo,hi,0,SZ-1); }

    void clear() { FOR(c, 0, nex) {d[c] = {};} nex = 0; orig_n = -1; loc.clear(); }
	void init(int n_) { clear(); orig_n = n_; build(V<T>(n_)); }
	void build(const auto& arr) {orig_n = arr.size(); loc.pb(build(arr,0,SZ-1));}
};

template<class T, class S, int SZ>
string tsdbg(PersistentSegTree<T, S, SZ> st, int time) {
	assert(st.orig_n != -1);
	V<T> out;
	FOR(k, 0, st.orig_n) { out.pb(st.query(time, k, k)); }
    return tsdbg(out);
}


PersistentSegTree<int, int, PSEG_POSITIONS> pst;
