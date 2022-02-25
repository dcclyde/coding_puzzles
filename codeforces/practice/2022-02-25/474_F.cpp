
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
    #define db(...) 43
    #define dbs(...) 45
    #define el
#endif

////////////////////////////////////////////////////////////////////////////////

struct Node {
    ll min = 1e9 + 1;
    ll gcd = -1;
    int num_with_min = 0;
};

Node basic_node(ll q) {
    return {.min = q, .gcd = q, .num_with_min = 1};
}

tcT> struct SegTree { // cmb(ID,b) = b
	const T ID{};
    T cmb(T a, T b) {
        Node out;
        out.min = min(a.min, b.min);

        if ( a.gcd == -1 || b.gcd == -1 ) {
            out.gcd = max(a.gcd, b.gcd);
        } else {
            out.gcd = __gcd(a.gcd, b.gcd);
        }

        if ( a.min == b.min ) {
            out.num_with_min = a.num_with_min + b.num_with_min;
        } else {
            if ( a.min < b.min ) {
                out.num_with_min = a.num_with_min;
            } else {
                out.num_with_min = b.num_with_min;
            }
        }
        return out;
    }
	int n; V<T> seg;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2;
		seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = cmb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) { // set val at position p
		seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {	// associative op on [l, r]
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = cmb(ra,seg[l++]);
			if (r&1) rb = cmb(seg[--r],rb);
		}
		return cmb(ra,rb);
	}
	/// int first_at_least(int lo, int val, int ind, int l, int r) { // if seg stores max across range
	/// 	if (r < lo || val > seg[ind]) return -1;
	/// 	if (l == r) return l;
	/// 	int m = (l+r)/2;
	/// 	int res = first_at_least(lo,val,2*ind,l,m); if (res != -1) return res;
	/// 	return first_at_least(lo,val,2*ind+1,m+1,r);
	/// }
};




void solve() {
    int N;
    cin >> N;
    vector<ll> dat( N );
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> dat[k];
    }

    // build the segment tree.
    SegTree<Node> st;
    st.init( N );
    for ( int k = 0 ; k < N ; ++k ) {
        st.upd( k , basic_node( dat[k] ) );
    }

    int Q;  // num queries
    cin >> Q;
    for ( int k = 0 ; k < Q ; ++k ) {
        int L, R;
        cin >> L >> R;
        Node curr = st.query( L-1 , R-1 );
        if ( curr.gcd == curr.min ) {
            cout << R-L+1 - curr.num_with_min << '\n';
        } else {
            cout << R-L+1 << '\n';
        }
    }

    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    solve();

    return 0;
}
