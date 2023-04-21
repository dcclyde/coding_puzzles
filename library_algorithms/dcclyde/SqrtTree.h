/**
    Similar interface to SegTree.
    This version costs sqrt(N) per query and 1 per update.
 */

tcT> struct SqrtTree { // cmb(ID,b) = b
	const T ID{};  // ! identity
    void cmbeq(T& a, T b, ll inc=1) { a += b*inc; }  // ! seg * seg
	int n;
    V<T> blockseg; V<T> seg;
    int orig_n;
    int BLOCK; int NUM_BLOCKS;
	void init(int _n) { // upd, query also work if n = _n
        orig_n = _n;
        BLOCK = sqrt(_n);
        NUM_BLOCKS = cdiv(_n + BLOCK - 1, BLOCK);
        n = NUM_BLOCKS * BLOCK;
        seg.assign(n, ID); blockseg.assign(NUM_BLOCKS, ID); }
    void build() {
        blockseg.assign(NUM_BLOCKS, ID);
        FOR(k,0,n) {ll b = k/BLOCK; cmbeq(blockseg[b], seg[k]);} }
	void upd(int p, T val) { // set val at position p
        cmbeq(blockseg[p/BLOCK], seg[p], -1)
        seg[p] = val;
        cmbeq(blockseg[p/BLOCK], val); }
    void inc(int p, T val) {
        cmbeq(seg[p], val);
        cmbeq(blockseg[p/BLOCK], val); }
	T query(int l, int r) {	// associative op on [l, r]
        if (l > r) {return ID;}
		T out = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) cmbeq(out, seg[l++]);
			if (r&1) cmbeq(out, seg[--r]);
		}
		return out;
	}
#if 0
    #pragma region  // first_satisfying
    // // return smallest x s.t. query(base, x) satisfies some criterion
	// int first_satisfying_R(int base, int val, int ind=1, int l=0, int r=-1) {
	// 	if (r == -1) {r = n-1;}
    //     // ! is there a good idx in [l, r]?
    //     bool ok = (seg[ind] >= val);
	// 	if (r < base || !ok) return -1;
	// 	if (l == r) return l;
	// 	int m = (l+r)/2;
	// 	int res = first_satisfying_R(base,val,2*ind,l,m); if (res != -1) return res;
    //     // ! Look for something different in other child if needed (e.g. if we want sum >= X)
	// 	return first_satisfying_R(base,val,2*ind+1,m+1,r);
	// }
    // // return largest x s.t. query(x, base) satisfies some criterion
	// int first_satisfying_L(int base, int val, int ind=1, int l=0, int r=-1) {
	// 	if (r == -1) {r = n-1;}
    //     // ! is there a good idx in [l, r]?
    //     bool ok = (seg[ind] >= val);
	// 	if (l > base || !ok) return -1;
	// 	if (l == r) return l;
	// 	int m = (l+r)/2;
	// 	int res = first_satisfying_L(base,val,2*ind+1,m+1,r); if (res != -1) return res;
    //     // ! Look for something different in other child if needed (e.g. if we want sum >= X)
	// 	return first_satisfying_L(base,val,2*ind,l,m);
	// }
    #pragma endregion
    void detailed_printouts() {
        #pragma region
        dbg_only(
        int ST_SIZE = n;
        int ST_PRINT_SIZE = orig_n;
        // ST_PRINT_SIZE = ST_SIZE;  // toggle whether to print irrelevant suffix
        el;
        dbgc("SegTree DETAILS");
        FOR(k, 1, ST_SIZE + ST_PRINT_SIZE) {
            if ( k >= ST_SIZE) {
                int p = k - ST_SIZE;
                dbgP(k, p, seg[k]);
            } else {
                vector<int> binary_digits;
                int temp = k;
                while ( temp > 0 ) {
                    binary_digits.push_back( temp % 2 );
                    temp /= 2;
                }
                reverse(all(binary_digits));
                int L = 0; int R = ST_SIZE-1;
                for ( int didx = 1 ; didx < binary_digits.size() ; ++didx ) {
                    int M = (L+R) / 2;
                    if ( binary_digits[didx] == 1 ) {
                        L = M+1;
                    } else {
                        R = M;
                    }
                }
                if ( L < ST_PRINT_SIZE ) {
                    dbgY(k, MP(L,R), seg[k]);
                }
            }
        }
        el;
        );  // end dbg_only
        #pragma endregion
    }
#endif
};
template<class T>
string tsdbg(SegTree<T> st) {
    vector<T> out;
    FOR(k, st.n, st.n + st.orig_n) { out.push_back( st.seg[k] ); }
    return tsdbg( out );
}


#pragma region  // range updates, point queries
tcT> struct SegTree { // cmb(ID,b) = b
	const T ID{};  // ! identity
    T cmb(T a, T b) { return a+b; }  // ! seg * seg
	int n; V<T> seg; int orig_n;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2;
		seg.assign(2*n,ID); orig_n = _n;}
	void pull(int p) { seg[p] = cmb(seg[2*p],seg[2*p+1]); }
    void build() { ROF(i,1,n) pull(i); }
	T query(int p) { // set val at position p
        T out = seg[p += n]; for (p /= 2; p; p /= 2) out = cmb(out, seg[p]); }
	void upd(int l, int r, T val) {	// associative op on [l, r]
        if (l > r) {return;}
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) {seg[l] = cmb(seg[l], val); ++l;}
			if (r&1) {--r; seg[r] = cmb(seg[r], val);}
		}
	}
    void detailed_printouts() {
        #pragma region
        dbg_only(
        int ST_SIZE = n;
        int ST_PRINT_SIZE = orig_n;
        // ST_PRINT_SIZE = ST_SIZE;  // toggle whether to print irrelevant suffix
        el;
        dbgc("SegTree DETAILS");
        FOR(k, 1, ST_SIZE + ST_PRINT_SIZE) {
            if ( k >= ST_SIZE) {
                int p = k - ST_SIZE;
                dbgP(k, p, seg[k]);
            } else {
                vector<int> binary_digits;
                int temp = k;
                while ( temp > 0 ) {
                    binary_digits.push_back( temp % 2 );
                    temp /= 2;
                }
                reverse(all(binary_digits));
                int L = 0; int R = ST_SIZE-1;
                for ( int didx = 1 ; didx < binary_digits.size() ; ++didx ) {
                    int M = (L+R) / 2;
                    if ( binary_digits[didx] == 1 ) {
                        L = M+1;
                    } else {
                        R = M;
                    }
                }
                if ( L < ST_PRINT_SIZE ) {
                    dbgY(k, MP(L,R), seg[k]);
                }
            }
        }
        el;
        );  // end dbg_only
        #pragma endregion
    }
};
template<class T>
string tsdbg(SegTree<T> st) {
    vector<T> out;
    FOR(k, st.n, st.n + st.orig_n) { out.push_back( st.seg[k] ); }
    return tsdbg( out );
}

