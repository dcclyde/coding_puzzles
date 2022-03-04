
// SLST = Sparse Lazy Segment Tree.
// Based on benq's LazySeg and SparseSeg.

// T = data, F = functional
template<class T, class U>
struct SLSTnode {
    static const int SUGGESTED_MAX_VAL = 1<<30-1;  // ~ 1.07e9
	struct F { // lazy update
		ll fdat = 0;
		F() {}  //! default/identity state
		F(int x) { fdat = x; }
		F& operator*=(const F& a) { fdat += a.fdat; return *this; }  //! FoF
	};
	struct T { // data you need to store for each interval
		ll val = 0;
		T() {}  //! default/identity state
		T(int x) { val = x; }
		friend T operator+(const T& a, const T& b) { return T(a.val + b.val); }  //! T+T
		T& operator*=(const F& a) { val += a.fdat; return *this; }  //! F(T)
	};
    T val; F lazy;
    int L, R;
    // subtrees
    SLSTnode<T,F>* c[2];

    SLSTnode(int L_, int R_) L(L_), R(R_) {c[0] = c[1] = nullptr;}

	void push() { /// modify values for current node
        val *= lazy;
        if (L < R) {
            int M = (L+R)/2;
            if (!c[0]) c[0] = new SLSTnode(L, M-1); c[0]->lazy *= lazy;
            if (!c[1]) c[1] = new SLSTnode(M, R  ); c[1]->lazy *= lazy;
        }
        lazy = F();
	} // recalc values for current node
	void pull() {
        val = T();
        F0R(i,2) if (c[i]) val = val + c[i]->val;
    }

    void upd(int lo, int hi, const F& f) {
		// spend O(1) time to un-lazy this node.
        push(ind);
        // quit if this subtree needs no update.
        if (hi < L || R < lo) return;
        // if this subtree is fully contained in [lo, hi] then Just Do It and quit.
		if (lo <= L && R <= hi) {
			lazy[ind] = inc; push(ind); return; }
        // recursion
		int M = (L+R)/2; upd(lo,hi,inc,2*ind,L,M);
		upd(lo,hi,inc,2*ind+1,M+1,R); pull(ind);

        push();
        if ( hi < L || R < lo ) return;
        if ( lo <= L && R <= hi ) {
            lazy = f; push(); return;
        }
        int M = (L+R)/2;
        if (!c[0]) c[0] = new SLSTNode(L, M-1); c[0]->upd(lo,hi,f);
        if (!c[1]) c[1] = new SLSTNode(M, R  ); c[1]->upd(lo,hi,f);
        pull();
    }

	T query(int lo, int hi) {
		push();
        if (lo > R || L > hi) return T();
		if (lo <= L && R <= hi) return val;

        T result();
		int M = (L+R)/2;
        return (c[0]?c[0]->query(lo,hi):T()) + (c[1]?c[1]->query(lo,hi):T());
	}

};
