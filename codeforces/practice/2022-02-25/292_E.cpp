
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

// use these if I steal data structures from benq
// https://github.com/bqi343/USACO
#if 1
#define tcT template<class T
#define tcTU tcT, class U
#define V vector
#endif

#ifdef DCCLYDE_LOCAL
    #include "/home/dcclyde/puzzles/code/codeforces/cftemplate_local.h"
#else
    #define dbc(...) 43
    #define db(...) 45
    #define el
#endif

////////////////////////////////////////////////////////////////////////////////


tcT> struct SegTree { // cmb(ID,b) = b
	const T ID = -1;
    T cmb(T a, T b) { return a+b; }
	int n; V<T> seg;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2;
		seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = cmb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) { // set val at position p
		seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p);
    }
	T query(int l, int r) {	// associative op on [l, r]
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = cmb(ra,seg[l++]);
			if (r&1) rb = cmb(seg[--r],rb);
		}
		return cmb(ra,rb);
	}

    void upd_custom(int p, int l, int r) {
        // this should look like "query", but instead of aggregating,
        // we'll just drop `p` in all those slots.

		// T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) {
                // ra = cmb(ra,seg[l++]);
                seg[l++] = p;
            }
			if (r&1) {
                // rb = cmb(seg[--r],rb);
                seg[--r] = p;
            }
		}
		// return cmb(ra,rb);
    }

    T query_custom(int p) {
        // this should look like upd, but instead of changing values,
        // we'll just return max over those values.

		// seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p);
        p += n;
        T out = seg[p];
        for (p /= 2; p; p /= 2) {
            out = max( out , seg[p] );
        }
        return out;
    }


	/// int first_at_least(int lo, int val, int ind, int l, int r) { // if seg stores max across range
	/// 	if (r < lo || val > seg[ind]) return -1;
	/// 	if (l == r) return l;
	/// 	int m = (l+r)/2;
	/// 	int res = first_at_least(lo,val,2*ind,l,m); if (res != -1) return res;
	/// 	return first_at_least(lo,val,2*ind+1,m+1,r);
	/// }
};

struct Query {
    int idxA;
    int idxB;
    int len;
};

void solve() {

    int N, Q;
    cin >> N >> Q;
    vector<ll> A( N ), B( N );
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> A[k];
    }
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> B[k];
    }

    // initialize a segtree.
    SegTree<int> st;
    st.init( N );  // all values initially set to -1.

    vector<Query> queries( Q );
    for ( int qid = 0 ; qid < Q ; ++qid ) {
        int qtype; cin >> qtype;
        if ( qtype == 1 ) {
            cin >> queries[qid].idxA >> queries[qid].idxB >> queries[qid].len;
            --queries[qid].idxA;
            --queries[qid].idxB;
            int L = queries[qid].idxB;
            int R = queries[qid].idxB + queries[qid].len - 1;
            st.upd_custom( qid , L , R );

            dbc("type 1" , qid , qtype , L , R );

        } else {
            int p;
            cin >> p;
            --p;  // zero based
            int op_idx = st.query_custom( p );

            dbc("type 2", qid , qtype, p, op_idx);

            if ( op_idx == -1 ) {
                cout << B[p] << '\n';
            } else {
                Query &op = queries[op_idx];
                int offset = p - op.idxB;
                int out = A[op.idxA + offset];
                cout << out << '\n';
            }
        }
    }


    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    int T = 1;
    // std::cin >> T;  // just comment this for one-case problems.
    for ( int k = 0 ; k < T ; ++k ) {
        solve();
    }

    return 0;
}
