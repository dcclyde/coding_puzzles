
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

// because I'd sometimes use data structures from benq and I don't wanna worry about it.
#define tcT template<class T
#define tcTU tcT, class U
#define V vector

#ifdef DCCLYDE_LOCAL
    #include "/home/dcclyde/puzzles/code/codeforces/cftemplate_local.h"
#else
    #define db(...) 43
    #define dbs(...) 45
    #define el
#endif

////////////////////////////////////////////////////////////////////////////////

struct node {
    int num_pairs;
    int leftover_L;
    int leftover_R;
};

tcT> struct SegTree { // cmb(ID,b) = b
	const T ID {
        .num_pairs = 0,
        .leftover_L = 0,
        .leftover_R = 0
    };
	const T base_L {
        .num_pairs = 0,
        .leftover_L = 1,
        .leftover_R = 0
    };
	const T base_R {
        .num_pairs = 0,
        .leftover_L = 0,
        .leftover_R = 1
    };

    T cmb(T a, T b) {
        int new_pairs = min(a.leftover_L, b.leftover_R);
        node out {
            .num_pairs = a.num_pairs + b.num_pairs + new_pairs,
            .leftover_L = a.leftover_L + b.leftover_L - new_pairs,
            .leftover_R = a.leftover_R + b.leftover_R - new_pairs
        };
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

    string parens;
    std::cin >> parens;
    int num_ops;
    std::cin >> num_ops;

    // set up the data structure.
    int N = parens.size();
    SegTree<node> dat;
    dat.init( N );
    for ( int k = 0 ; k < N ; ++k ) {
        dat.upd( k , parens[k] == '(' ? dat.base_L : dat.base_R );
    }

    for ( int _ = 0 ; _ < num_ops ; ++_ ) {
        int L, R;
        cin >> L >> R;
        node result = dat.query( L-1 , R-1 );
        cout << result.num_pairs * 2 << '\n';
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
