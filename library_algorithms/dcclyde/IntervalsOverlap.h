
/*
    Similar to IntervalUnion, but now the underlying data is added when two intervals overlap.
    Basically a sparse dual-segtree with log(SZ) range updates and point queries.
    ! Time complexity is Q * log(SZ).
*/

#pragma region  // IntervalsOverlap (sparse segtree)
template<class T> struct IntervalsOverlap {
	static ll SZ;
    static const T ID = 0;  // ! identity
    T cmb(T a, T b) { return a+b; }  // ! seg * seg
	T val = ID;
    IntervalsOverlap<T>* c[2];
	IntervalsOverlap() { c[0] = c[1] = NULL; dbg_only(assert(SZ != -1);)}
	T query(int ind, int L = 0, int R = -1) { // query value at point
        if (R == -1) {R = SZ-1;}
        // dbgcP("query", ind, MP(L,R), val);
		if (L == ind && R == ind) { return val; }
		int M = (L+R)/2;
		if (ind <= M) {
            if (!c[0]) {return val;}
            return cmb(val, c[0]->query(ind,L,M));
		} else {
			if (!c[1]) {return val;}
            return cmb(val, c[1]->query(ind,M+1,R));
		}
	}
	void upd(int lo, int hi, T v, int L = 0, int R = -1) { // update segment
        if (R == -1) {R = SZ-1;}
        // dbgcB("upd", MP(lo,hi), v, "", MP(L,R));
		if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) {val = cmb(val, v); return;}
		int M = (L+R)/2;
        if (lo <= M) {
            if (!c[0]) c[0] = new IntervalsOverlap();
            c[0]->upd(lo,hi,v,L,M);
        }
        if (M+1 <= hi) {
            if (!c[1]) c[1] = new IntervalsOverlap();
            c[1]->upd(lo,hi,v,M+1,R);
        }
	}
};
template<class T> ll IntervalsOverlap<T>::SZ = -1;  // uninitialized

// Example setup:
// IntervalsOverlap<ll>::SZ = N;
// IntervalsOverlap<ll> st;
#pragma endregion  // IntervalsOverlap
