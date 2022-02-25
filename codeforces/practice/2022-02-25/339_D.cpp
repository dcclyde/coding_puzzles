
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


tcT> struct SegTree { // cmb(ID,b) = b
	const T ID = 0;
    T cmb(int level, T a, T b) {
        if ( level % 2 == 0 ) {
            return a ^ b;
        } else {
            return a | b;
        }
    }
	int n; V<T> seg;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2;
		seg.assign(2*n,ID); }
	void pull(int p, int level) { seg[p] = cmb(level, seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) { // set val at position p
		seg[p += n] = val;
        int level = 0;
        for (p /= 2; p; p /= 2) {
            ++level;
            pull(p, level);
        }
    }

    T query() {
        return seg[1];
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
    ll pow, Q;
    cin >> pow >> Q;

    ll N = 1 << pow;
    vector<ll> dat( N );
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> dat[k];
    }

    SegTree<ll> st;
    st.init( N );
    for ( int k = 0 ; k < N ; ++k ) {
        st.upd( k , dat[k] );
    }

    for ( int qid = 0 ; qid < Q ; ++qid ) {
        int pos, val;
        cin >> pos >> val;
        st.upd( pos-1 , val );
        db(st.seg);
        ll result = st.query();
        cout << result << '\n';
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
