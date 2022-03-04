#pragma region
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = long double; // or double, if TL is tight
using str = string; // yay python!

// pairs
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using pd = pair<db,db>;
///// I'm not used to the defs above.
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
#define mp make_pair
#define MP make_pair /////
#define f first
#define s second

#define tcT template<class T
#define tcTU tcT, class U
// ^ lol this makes everything look weird but I'll try it
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

// vectors
// oops size(x), rbegin(x), rend(x) need C++17
#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define pb push_back
#define eb emplace_back
#define ft front()
#define bk back()

#define lb lower_bound
#define ub upper_bound
tcT> int lwb(V<T>& a, const T& b) { return int(lb(all(a),b)-bg(a)); }
tcT> int upb(V<T>& a, const T& b) { return int(ub(all(a),b)-bg(a)); }

// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353;
const int MX = 2e5+5;
const ll BIG = 1e18; // not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1}; // for every grid problem!!
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>;

// bitwise ops
// also see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) { // assert(x >= 0); // make C++11 compatible until USACO updates ...
	return x == 0 ? 0 : 31-__builtin_clz(x); } // floor(log2(x))
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }

ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

tcTU> T fstTrue(T lo, T hi, U f) {
	++hi; assert(lo <= hi); // assuming f is increasing
	while (lo < hi) { // find first index such that f is true
		T mid = lo+(hi-lo)/2;
		f(mid) ? hi = mid : lo = mid+1;
	}
	return lo;
}
tcTU> T lstTrue(T lo, T hi, U f) {
	--lo; assert(lo <= hi); // assuming f is decreasing
	while (lo < hi) { // find first index such that f is true
		T mid = lo+(hi-lo+1)/2;
		f(mid) ? lo = mid : hi = mid-1;
	}
	return lo;
}
tcT> void remDup(vector<T>& v) { // sort and remove duplicates
	sort(all(v)); v.erase(unique(all(v)),end(v)); }
tcTU> void erase(T& t, const U& u) { // don't erase
	auto it = t.find(u); assert(it != end(t));
	t.erase(it); } // element that doesn't exist from (multi)set

#define tcTUU tcT, class ...U

inline namespace Helpers {
	//////////// is_iterable
	// https://stackoverflow.com/questions/13830158/check-if-a-variable-type-is-iterable
	// this gets used only when we can call begin() and end() on that type
	tcT, class = void> struct is_iterable : false_type {};
	tcT> struct is_iterable<T, void_t<decltype(begin(declval<T>())),
	                                  decltype(end(declval<T>()))
	                                 >
	                       > : true_type {};
	tcT> constexpr bool is_iterable_v = is_iterable<T>::value;

	//////////// is_readable
	tcT, class = void> struct is_readable : false_type {};
	tcT> struct is_readable<T,
	        typename std::enable_if_t<
	            is_same_v<decltype(cin >> declval<T&>()), istream&>
	        >
	    > : true_type {};
	tcT> constexpr bool is_readable_v = is_readable<T>::value;

	//////////// is_printable
	// // https://nafe.es/posts/2020-02-29-is-printable/
	tcT, class = void> struct is_printable : false_type {};
	tcT> struct is_printable<T,
	        typename std::enable_if_t<
	            is_same_v<decltype(cout << declval<T>()), ostream&>
	        >
	    > : true_type {};
	tcT> constexpr bool is_printable_v = is_printable<T>::value;
}

inline namespace Input {
	tcT> constexpr bool needs_input_v = !is_readable_v<T> && is_iterable_v<T>;
	tcTUU> void re(T& t, U&... u);
	tcTU> void re(pair<T,U>& p); // pairs

	// re: read
	tcT> typename enable_if<is_readable_v<T>,void>::type re(T& x) { cin >> x; } // default
	tcT> void re(complex<T>& c) { T a,b; re(a,b); c = {a,b}; } // complex
	tcT> typename enable_if<needs_input_v<T>,void>::type re(T& i); // ex. vectors, arrays
	tcTU> void re(pair<T,U>& p) { re(p.f,p.s); }
	tcT> typename enable_if<needs_input_v<T>,void>::type re(T& i) {
		each(x,i) re(x); }
	tcTUU> void re(T& t, U&... u) { re(t); re(u...); } // read multiple

	// rv: resize and read vectors
	void rv(size_t) {}
	tcTUU> void rv(size_t N, V<T>& t, U&... u);
	template<class...U> void rv(size_t, size_t N2, U&... u);
	tcTUU> void rv(size_t N, V<T>& t, U&... u) {
		t.rsz(N); re(t);
		rv(N,u...); }
	template<class...U> void rv(size_t, size_t N2, U&... u) {
		rv(N2,u...); }

	// dumb shortcuts to read in ints
	void decrement() {} // subtract one from each
	tcTUU> void decrement(T& t, U&... u) { --t; decrement(u...); }
	#define ints(...) int __VA_ARGS__; re(__VA_ARGS__);
	#define int1(...) ints(__VA_ARGS__); decrement(__VA_ARGS__);
}

inline namespace ToString {
	tcT> constexpr bool needs_output_v = !is_printable_v<T> && is_iterable_v<T>;

	// ts: string representation to print
	tcT> typename enable_if<is_printable_v<T>,str>::type ts(T v) {
		stringstream ss; ss << fixed << setprecision(15) << v;
		return ss.str(); } // default
	tcT> str bit_vec(T t) { // bit vector to string
		str res = "{"; F0R(i,sz(t)) res += ts(t[i]);
		res += "}"; return res; }
	str ts(V<bool> v) { return bit_vec(v); }
	template<size_t SZ> str ts(bitset<SZ> b) { return bit_vec(b); } // bit vector
	tcTU> str ts(pair<T,U> p); // pairs
	tcT> typename enable_if<needs_output_v<T>,str>::type ts(T v); // vectors, arrays
	tcTU> str ts(pair<T,U> p) { return "("+ts(p.f)+", "+ts(p.s)+")"; }
	tcT> typename enable_if<is_iterable_v<T>,str>::type ts_sep(T v, str sep) {
		// convert container to string w/ separator sep
		bool fst = 1; str res = "";
		for (const auto& x: v) {
			if (!fst) res += sep;
			fst = 0; res += ts(x);
		}
		return res;
	}
	tcT> typename enable_if<needs_output_v<T>,str>::type ts(T v) {
		return "{"+ts_sep(v,", ")+"}"; }

	// for nested DS
	template<int, class T> typename enable_if<!needs_output_v<T>,vs>::type
	  ts_lev(const T& v) { return {ts(v)}; }
	template<int lev, class T> typename enable_if<needs_output_v<T>,vs>::type
	  ts_lev(const T& v) {
		if (lev == 0 || !sz(v)) return {ts(v)};
		vs res;
		for (const auto& t: v) {
			if (sz(res)) res.bk += ",";
			vs tmp = ts_lev<lev-1>(t);
			res.ins(end(res),all(tmp));
		}
		F0R(i,sz(res)) {
			str bef = " "; if (i == 0) bef = "{";
			res[i] = bef+res[i];
		}
		res.bk += "}";
		return res;
	}
}

inline namespace Output {
	template<class T> void pr_sep(ostream& os, str, const T& t) { os << ts(t); }
	template<class T, class... U> void pr_sep(ostream& os, str sep, const T& t, const U&... u) {
		pr_sep(os,sep,t); os << sep; pr_sep(os,sep,u...); }
	// print w/ no spaces
	template<class ...T> void pr(const T&... t) { pr_sep(cout,"",t...); }
	// print w/ spaces, end with newline
	void ps() { cout << "\n"; }
	template<class ...T> void ps(const T&... t) { pr_sep(cout," ",t...); ps(); }
    // ! Remove debug code; I'll use the tourist+me amalgamation instead.

	const clock_t beg = clock();
	#define dbg_time() dbg((db)(clock()-beg)/CLOCKS_PER_SEC)
}

inline namespace FileIO {
	void setIn(str s)  { freopen(s.c_str(),"r",stdin); }
	void setOut(str s) { freopen(s.c_str(),"w",stdout); }
	void setIO(str s = "") {
		cin.tie(0)->sync_with_stdio(0); // unsync C / C++ I/O streams
		cin.exceptions(cin.failbit);
		// throws exception when do smth illegal
		// ex. try to read letter into int
		if (sz(s)) setIn(s+".in"), setOut(s+".out"); // for old USACO
	}
}

// * debug setup mostly stolen from tourist. https://codeforces.com/contest/1540/submission/120602670
// * dcclyde added line numbers, colors, probably some other stuff.

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

template <typename A, typename B, typename C, typename D, typename E>
string to_string(tuple<A, B, C, D, E> p);

string to_string(const string& s) {
    return '"' + s + '"';
}

string to_string(char c) {
    return "'" + string(1, c) + "'";
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template <size_t N>
string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

template <typename A, typename B, typename C, typename D, typename E>
string to_string(tuple<A, B, C, D, E> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ", " + to_string(get<4>(p)) + ")";
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << to_string(H) << "   ";
    debug_out(T...);
}

// #define BOLD_MAYBE ""    // NOT bold
#define BOLD_MAYBE ";1"  // YES bold

#define OUT_RESET   "\033[0m"
#define OUT_BOLD    "\033[" << BOLD_MAYBE << "m"
#define OUT_RED     "\033[31" << BOLD_MAYBE << "m"
#define OUT_CYAN    "\033[36" << BOLD_MAYBE << "m"
// #define OUT_GREEN   "\033[32" << BOLD_MAYBE << "m"
#define OUT_GREEN   "\033[32" << "m"
#define OUT_BLUE    "\033[34" << BOLD_MAYBE << "m"


#ifdef DCCLYDE_LOCAL
    #define el cerr << '\n';  // in my head I say "error line"
    // dbgc = "debug with comment"
    #define dbgcbase(A, ...) cerr << OUT_RED \
        << right << setw(20) << A \
        << right << setw(8) << __LINE__        \
        << OUT_BOLD << " : " << OUT_RESET \
        << OUT_GREEN << "[ " << #__VA_ARGS__ << " ]" \
        << OUT_BOLD << " :    " << OUT_RESET \
        << OUT_CYAN, debug_out(__VA_ARGS__); \
        cerr << OUT_RESET;
    #define dbgbase(...) dbgc("", __VA_ARGS__)
    // #define dbg(...) ;
    // #define dbgc(...) ;
    #define dbg(...) dbgbase(__VA_ARGS__)
    #define dbgc(...) dbgcbase(__VA_ARGS__)
    // useful as a second distinct "log level"
    #define dbg2(...) dbgbase(__VA_ARGS__)
    #define dbgc2(...) dbgcbase(__VA_ARGS__)
#else
    #define dbgc(...) ;
    #define dbg(...) ;
    #define dbg2(...) ;
    #define dbgc2(...) ;
    #define el ;
#endif

#pragma endregion

// /**
//  * Description: 1D range increment and sum query.
//  * Source: USACO Counting Haybales
//  	* https://codeforces.com/blog/entry/82400
//  * Verification: USACO Counting Haybales
//  */

// struct LazySeg {
// 	struct F { // lazy update
// 		ll inc = 0;
// 		F() {}
// 		F(int x) { inc = x; }
// 		F& operator*=(const F& a) { inc += a.inc; return *this; }
// 	}; V<F> lazy;
// 	struct T { // data you need to store for each interval
// 		ll sz = 1, mn = 1e18, sum = 0;
// 		T() {}
// 		T(int x) { mn = sum = x; }
// 		friend T operator+(const T& a, const T& b) {
// 			T res; res.sz = a.sz+b.sz;
// 			res.mn = min(a.mn,b.mn), res.sum = a.sum+b.sum;
// 			return res;
// 		}
// 		T& operator*=(const F& a) {
// 			mn += a.inc; sum += (ll)sz*a.inc; return *this; }
// 	}; V<T> seg;
// 	int SZ = 1;
// 	void init(const V<T>& _seg) {
// 		while (SZ < sz(_seg)) SZ *= 2;
// 		seg.rsz(2*SZ); lazy.rsz(2*SZ);
// 		F0R(i,SZ) seg[SZ+i] = _seg[i];
// 		ROF(i,1,SZ) pull(i);
// 	}
// 	void push(int ind) { /// modify values for current node
// 		seg[ind] *= lazy[ind];
// 		if (ind < SZ) F0R(i,2) lazy[2*ind+i] *= lazy[ind];
// 		lazy[ind] = F();
// 	} // recalc values for current node
// 	void pull(int ind) { seg[ind] = seg[2*ind]+seg[2*ind+1]; }
// 	void upd(int lo, int hi, F inc, int ind, int L, int R) {
// 		push(ind); if (hi < L || R < lo) return;
// 		if (lo <= L && R <= hi) {
// 			lazy[ind] = inc; push(ind); return; }
// 		int M = (L+R)/2; upd(lo,hi,inc,2*ind,L,M);
// 		upd(lo,hi,inc,2*ind+1,M+1,R); pull(ind);
// 	}
// 	void upd(int lo, int hi, int inc) { upd(lo,hi,{inc},1,0,SZ-1); }
// 	T query(int lo, int hi, int ind, int L, int R) {
// 		push(ind); if (lo > R || L > hi) return T();
// 		if (lo <= L && R <= hi) return seg[ind];
// 		int M = (L+R)/2;
// 		return query(lo,hi,2*ind,L,M)+query(lo,hi,2*ind+1,M+1,R);
// 	}
// 	T query(int lo, int hi) { return query(lo,hi,1,0,SZ-1); }
// };



// /*
//     Track a collection of intervals.
//     Example usage: codeforces/2022-02-23/E_working_on_data_structure.cpp
// */

// template<class T, bool MERGE_ADJACENT = false>
// struct IntervalUnion {
// 	using interval = pair<pair<T, T>, ll>;
//     set<interval> x;

//     // internal helper
//     vector<interval> merge_intervals(const interval& a, const interval& b) {
// 		vector<interval> out;
// 		if ( a.f.f <= b.f.f ) {
// 			out.emplace_back( MP(a.f.f , b.f.f-1) , a.s );
// 		} else {
// 			out.emplace_back( MP(b.f.f , a.f.f-1) , b.s );
// 		}
// 		out.emplace_back(
// 			MP(
// 				max(a.f.f, b.f.f),
// 				min(a.f.s, b.f.s)
// 			),
// 			a.s & b.s
// 		);
// 		if ( a.f.s <= b.f.s ) {
// 			out.emplace_back( MP(a.f.s+1 , b.f.s) , b.s );
// 		} else {
// 			out.emplace_back( MP(b.f.s+1 , a.f.s) , a.s );
// 		}
// 		vector<interval> outReal;
// 		each( t , out ) {
// 			if ( t.f.f <= t.f.s ) {
// 				outReal.push_back( t );
// 			}
// 		}
// 		return outReal;
//     }

//     void insert(interval& pr) {
//         while ( true ) {
//             auto it = x.lower_bound( pr );
//             if ( it != x.end() && it->f.first <= pr.f.second + MERGE_ADJACENT ) {
//                 // found an adjacent interval that's ">=" mine.
//                 pr = merge_intervals(pr, *it);
//                 x.erase( it );
//                 continue;
//             }
//             if ( it == x.begin() ) {
//                 break;
//             }
//             --it;
//             if ( it->second >= pr.first - MERGE_ADJACENT ) {
//                 pr = merge_intervals(pr, *it);
//                 x.erase(it);
//                 continue;
//             }
//             break;
//         }
//         x.insert( pr );
//     }

//     set<pair<T,T>>::const_iterator query(T p) {
//         it = x.lower_bound(MP(p,p));
//         if ( it != x.end() && it->first == p ) {
//             return it;
//         }
//         if ( it == x.begin() ) {
//             return x.end();
//         }
//         --it;
//         if ( it->second >= p ) {
//             return it;
//         }
//         return x.end();
//     }
// };

/**
 * Description: 1D point update, range query where \texttt{cmb} is
 	* any associative operation. If $N=2^p$ then \texttt{seg[1]==query(0,N-1)}.
 * Time: O(\log N)
 * Source:
	* http://codeforces.com/blog/entry/18051
	* KACTL
 * Verification: SPOJ Fenwick
 */

constexpr int NUM_BITS = 30;
// constexpr int NUM_BITS = 3;

tcT> struct SegTree { // cmb(ID,b) = b
	const T ID{(1<<NUM_BITS)-1}; T cmb(T a, T b) { return a+b; }
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

	void upd_custom(int l, int r, T val) {
		// T ra = ID, rb = ID;
		dbgc( "upd start" , l , r , val , seg );
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			// if (l&1) ra = cmb(ra,seg[l++]);
			// if (r&1) rb = cmb(seg[--r],rb);
			if (l&1) {
				seg[l] = seg[l] & val;
				++l;
			}
			if (r&1) {
				--r;
				seg[r] = seg[r] & val;
			}
		}
		dbgc( "upd end" , l , r , val , seg );
		el;
		// return cmb(ra,rb);
	}
	T query_custom(int p) {
		// seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
		dbgc( "query start" , p , seg );
		T out = seg[p += n];
		for ( p /= 2 ; p ; p /= 2 ) {
			out &= seg[ p ];
			dbg( out , p );
		}
		dbgc( "query end" , p , out ); el;
		return out;
	}
};


template<int MOD, int RT> struct mint {
	static const int mod = MOD;
	static constexpr mint rt() { return RT; } // primitive root for FFT
	int v; explicit operator int() const { return v; } // explicit -> don't silently convert to int
	mint():v(0) {}
	mint(ll _v) { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
		if (v < 0) v += MOD; }
	bool operator==(const mint& o) const {
		return v == o.v; }
	friend bool operator!=(const mint& a, const mint& b) {
		return !(a == b); }
	friend bool operator<(const mint& a, const mint& b) {
		return a.v < b.v; }
	friend void re(mint& a) { ll x; re(x); a = mint(x); }
	friend str ts(mint a) { return ts(a.v); }

	mint& operator+=(const mint& o) {
		if ((v += o.v) >= MOD) v -= MOD;
		return *this; }
	mint& operator-=(const mint& o) {
		if ((v -= o.v) < 0) v += MOD;
		return *this; }
	mint& operator*=(const mint& o) {
		v = int((ll)v*o.v%MOD); return *this; }
	mint& operator/=(const mint& o) { return (*this) *= inv(o); }
	friend mint pow(mint a, ll p) {
		mint ans = 1; assert(p >= 0);
		for (; p; p /= 2, a *= a) if (p&1) ans *= a;
		return ans; }
	friend mint inv(const mint& a) { assert(a.v != 0);
		return pow(a,MOD-2); }

	mint operator-() const { return mint(-v); }
	mint& operator++() { return *this += 1; }
	mint& operator--() { return *this -= 1; }
	friend mint operator+(mint a, const mint& b) { return a += b; }
	friend mint operator-(mint a, const mint& b) { return a -= b; }
	friend mint operator*(mint a, const mint& b) { return a *= b; }
	friend mint operator/(mint a, const mint& b) { return a /= b; }
};

using mi = mint<MOD,5>; // 5 is primitive root for both common mods
using vmi = V<mi>;
using pmi = pair<mi,mi>;
using vpmi = V<pmi>;

V<vmi> scmb; // small combinations
void genComb(int SZ) {
	scmb.assign(SZ,vmi(SZ)); scmb[0][0] = 1;
	FOR(i,1,SZ) F0R(j,i+1)
		scmb[i][j] = scmb[i-1][j]+(j?scmb[i-1][j-1]:0);
}

//////////////////////////////////////////////////////////////////////////

void solve() {
    ints(N, Q);
	vector<tuple<ll,ll,ll>> dat( Q );
	F0R( k , Q ) {
		ints(L, R, val);
		dat[k] = {L-1, R-1, val};
		// cin >> get<0>(dat[k]) >> get<1>(dat[k]) >> get<2>(dat[k]);
	}
    dbg(Q, dat);

	SegTree<ll> st;
	st.init( N );
	F0R( k , Q ) {
		/*
			Array starts as all 2^31-1.
			Every time I receive a query result with 0s, I should remove those entry bits.
			In other words I will & the given region by the query result?
		*/
		auto& [L, R, val] = dat[k];
		st.upd_custom( L , R , val );
	}
	vector<ll> out_vector;
	F0R( k , N ) {
		out_vector.push_back( st.query_custom( k ) );
	}
	dbg( out_vector );

	///// Part 2: do the XOR sum stuff.
	vector<int> count_per_bit( NUM_BITS , 0 );
	each( x , out_vector ) {
		for ( int bit = 0 ; bit < NUM_BITS ; ++bit ) {
			if ( (x>>bit) & 1 ) {
				++count_per_bit[ bit ];
			}
		}
	}
	dbg( count_per_bit );
	mi out = 0;
	for ( int bit = 0 ; bit < NUM_BITS ; ++bit ) {
		int num_ones = count_per_bit[ bit ];
		int num_zeros = N - num_ones;
		if ( num_ones == 0 ) {
			continue;
		}
		mi contribution = pow( mi(2) , num_ones + num_zeros - 1 );
		dbg( bit , num_ones , num_zeros , (int)contribution );
		contribution *= (1<<bit);
		out += contribution;
	}
	cout << (int)out << '\n';

	return;
}

// ! Read the sample cases before writing code!
#pragma region
int main() {
	setIO();

    int T = 1;
    std::cin >> T;  dbgc("loading num cases!!!")  // comment this out for one-case problems.
    for ( int k = 1 ; k <= T ; ++k ) {
        el; dbgc("CASE" , k ); el;
        solve();
    }

    return 0;
}
#pragma endregion
