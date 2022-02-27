
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define MP make_pair
#define MT make_tuple

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
    #define dbc(...) ;
    #define db(...) ;
    #define el
#endif

const int INF = 2e9;

////////////////////////////////////////////////////////////////////////////////

tcT> struct SegTree { // cmb(ID,b) = b
	const T ID = INF; T cmb(T a, T b) { return min(a, b); }
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

template<class T, bool MERGE_ADJACENT = true>
struct IntervalUnion {
    set<pair<T, T>> x;
    set<pair<T, T>>::iterator it;  // avoid reallocating.

    // internal helper
    pair<T, T> merge_intervals(const pair<T,T>& a, const pair<T,T>& b) {
        return { min(a.first, b.first) , max(a.second, b.second) };
    }

    void insert(pair<T, T> pr) {
        while ( true ) {
            it = x.lower_bound( pr );
            if ( it != x.end() && it->first <= pr.second + MERGE_ADJACENT ) {
                // found an adjacent interval that's ">=" mine.
                pr = merge_intervals(pr, *it);
                x.erase( it );
                continue;
            }
            if ( it == x.begin() ) {
                break;
            }
            --it;
            if ( it->second >= pr.first - MERGE_ADJACENT ) {
                pr = merge_intervals(pr, *it);
                x.erase(it);
                continue;
            }
            break;
        }
        x.insert( pr );
    }

    set<pair<T,T>>::const_iterator query(T p) {
        it = x.lower_bound(MP(p,p));
        if ( it != x.end() && it->first == p ) {
            return it;
        }
        if ( it == x.begin() ) {
            return x.end();
        }
        --it;
        if ( it->second >= p ) {
            return it;
        }
        return x.end();
    }
};

void solve() {

    int N, num_queries;
    cin >> N >> num_queries;
    ++N;  // let's just stay 1-indexed.
    IntervalUnion<int> safe;
    SegTree<int> st;
    st.init( N );

    for ( int qid = 0 ; qid < num_queries ; ++qid ) {
        int t; cin >> t;
        if ( t == 0 ) {
            int l, r, x;
            cin >> l >> r >> x;
            dbc( "got data" , MP(l, r) , x==1 );
            if ( x == 0 ) {
                // safe interval
                safe.insert(MP(l, r));
                dbc( "updated safe" , safe.x );
            } else {
                int rr = st.query(l, l);
                if ( r < rr ) {
                    st.upd( l , r );
                }
            }
        } else {
            int p; cin >> p;
            // Is this person sick?
            // First check if they're known safe.
            dbc( "testing" , p );
            auto it = safe.query( p );
            if ( it != safe.x.cend() ) {
                cout << "NO\n";
                continue;
            }

            // find the biggest known-safe intervals right next to my point.
            auto ext_interval = MP(p, p);
            it = safe.query( p+1 );
            if ( it != safe.x.cend() ) {
                ext_interval = safe.merge_intervals( ext_interval , *it );
            }
            it = safe.query( p-1 );
            if ( it != safe.x.cend() ) {
                ext_interval = safe.merge_intervals( ext_interval , *it );
            }

            int best_endpoint = st.query( ext_interval.first , ext_interval.second );
            db( ext_interval , best_endpoint );
            if ( best_endpoint <= ext_interval.second ) {
                cout << "YES\n";
                continue;
            } else {
                cout << "N/A\n";
                continue;
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
    for ( int k = 1 ; k <= T ; ++k ) {
        el; dbc("CASE" , k ); el;
        solve();
    }

    return 0;
}
