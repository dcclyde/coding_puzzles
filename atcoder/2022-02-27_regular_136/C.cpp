
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

////////////////////////////////////////////////////////////////////////////////



/**
 * Description: 1D point update, range query where \texttt{cmb} is
 	* any associative operation. If $N=2^p$ then \texttt{seg[1]==query(0,N-1)}.
 * Time: O(\log N)
 * Source:
	* http://codeforces.com/blog/entry/18051
	* KACTL
 * Verification: SPOJ Fenwick
 */

const int INF = 2e9;

tcT> struct SegTree { // cmb(ID,b) = b
	const T ID = MP( INF , vector<int>() );
    T cmb(T& a, T& b) {
        if ( a.first < b.first ) {
            return a;
        }
        if ( b.first < a.first ) {
            return b;
        }
        vector<int>& A = a.second;
        vector<int>& B = b.second;
        vector<int> out( A.size() + B.size() );
        int idxA = 0;
        int idxB = 0;
        int idxOut = 0;
        db( A , B );
        while ( idxA < A.size() && idxB < B.size() ) {
            db( idxA , idxB , out );
            if ( A[idxA] <= B[idxB] ) {
                out[idxOut] = A[idxA];
                ++idxA;
                ++idxOut;
            } else {
                out[idxOut] = B[idxB];
                ++idxB;
                ++idxOut;
            }
        }
        db( idxA , idxB , out );
        while ( idxA < A.size() ) {
            out[idxOut] = A[idxA];
            ++idxA;
            ++idxOut;
        }
        while ( idxB < B.size() ) {
            out[idxOut] = B[idxB];
            ++idxB;
            ++idxOut;
        }
        db( out ); el;
        return MP( a.first , out );
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

ll helper(
    SegTree<pair<int, vector<int>>>& st,
    vector<int>& B,
    int l, int r,
    int offset
) {
    if ( l > r ) {
        return 0;
    }
    // auto&[min_value, min_positions] = st.query( l , r );
    auto pr = st.query( l , r );
    int min_value = pr.first;
    vector<int>& min_positions = pr.second;
    ll out = min_value - offset;
    for ( int k = 0 ; k < min_positions.size() - 1 ; ++k ) {
        out += helper( st , B , min_positions[k]+1 , min_positions[k+1]-1 , min_value );
    }
    out += helper( st , B , l , min_positions[0]-1 , min_value );
    out += helper( st , B , min_positions.back()+1 , r , min_value );
    dbc( "hout", l , r , out );
    return out;
}

void solve() {
    int N; cin >> N;
    vector<int> A( N );
    int min_pos = 0;
    for ( int k = 0 ; k < N ; ++k ) {
        cin >> A[k];
        if ( A[k] < A[min_pos] ) {
            min_pos = k;
        }
    }
    vector<int> B;
    B.insert( B.end() , A.begin() + min_pos , A.end() );
    B.insert( B.end() , A.begin() , A.begin() + min_pos );

    SegTree<pair<int, vector<int>>> st;
    st.init( N );
    for ( int k = 0 ; k < N ; ++k ) {
        st.upd( k , MP( A[k] , vector<int>( 1 , k ) ) );
    }

    db( B );
    db( st.seg );
    ll out = helper( st , B , 0 , N-1 , 0 );
    cout << out << '\n';

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
