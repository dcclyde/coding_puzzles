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
#define MP make_pair
// #define f first
// #define s second

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

// #define lb lower_bound
// #define ub upper_bound
tcT> int lwb(V<T>& a, const T& b) { return int(lb(all(a),b)-bg(a)); }
tcT> int upb(V<T>& a, const T& b) { return int(ub(all(a),b)-bg(a)); }

// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+1; // 998244353;
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
        << std::right << setw(20) << A \
        << std::right << setw(8) << __LINE__        \
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



int nodes_allocated = 0;

int INF = 2e9+5;
// T = data, F = functional
const int SEGTREE_MAX = (1<<30) - 1;  // ~ 1.07e9
// const int SEGTREE_MAX = (1<<8) - 1;  // testing only
const int SEGTREE_MIN = 0;
struct SLSTnode {
	struct F { // lazy update
		int fdat = 0;
		F() {}  //! default/identity state
		F(int x) { fdat = x; }
		F& operator*=(const F& a) { fdat += a.fdat; return *this; }  //! FoF
	};
	struct T { // data you need to store for each interval
		int tmin = INF;
		int tmax = -INF;
		T() {}  //! default/identity state
		T(int min_, int max_) : tmin(min_), tmax(max_) {}
		friend T operator+(const T& a, const T& b) {
			return T(min(a.tmin, b.tmin), max(a.tmax, b.tmax));
		}  //! T+T
		T& operator*=(const F& a) { if (tmin != INF) tmin += a.fdat; if (tmax != -INF) tmax += a.fdat; return *this; }  //! F(T)
	};
	static SLSTnode* new_node(int L_, int R_);
    T t; F f;
    int L, R;
    // subtrees
    SLSTnode* c[2];

	SLSTnode() {}
    SLSTnode(int L_, int R_) : L(L_), R(R_) {
		c[0] = c[1] = nullptr;
		t.tmin = 0; t.tmax = 0;  //! All nodes should initially be 0, even though that is not ID
	}

	void push() { /// modify values for current node
        // dbgc("push START", L, R, MP(t.tmin, t.tmax), f.fdat);
        t *= f;
        if (L < R) {
            int M = (L+R)/2;
            if (!c[0]) {c[0] = new SLSTnode(L  , M); ++nodes_allocated;}
            c[0]->f *= f;
            if (!c[1]) {c[1] = new SLSTnode(M+1, R); ++nodes_allocated;}
            c[1]->f *= f;
        }
        f = F();
	}
    // recalc values for current node
	void pull() {
        // dbgc("pull START", L, R, MP(t.tmin, t.tmax), f.fdat);
        t = T();
        F0R(i,2) if (c[i]) t = t + c[i]->t;
        // dbgc("pull END",L,R,MP(t.tmin, t.tmax),f.fdat);
    }

    void upd(int lo, int hi, const F& fother) {
        // dbgc("upd", lo, hi, L, R, fother.fdat);
		// spend O(1) time to un-lazy this node.
        push();
        // quit if this subtree needs no update.
        if ( hi < L || R < lo ) {
            // dbgc("upd none");
            return;
        }
        // if this subtree is fully contained in [lo, hi] then Just Do It and quit.
        if ( lo <= L && R <= hi ) {
            // dbgc("upd contained");
            f = fother; push(); return;
        }
        // recurse
        int M = (L+R)/2;
        // dbgc("upd recurse", MP(L, M), MP(M+1, R));
        if (!c[0]) {c[0] = /*new SLSTnode*/new_node(L  , M); ++nodes_allocated;}
        c[0]->upd(lo,hi,fother);
        if (!c[1]) {c[1] = /*new SLSTnode*/new_node(M+1, R); ++nodes_allocated;}
        c[1]->upd(lo,hi,fother);
        pull();
    }

	T query(int lo, int hi) {
        // dbgc("query START", MP(lo , hi) , MP(L , R) , MP(t.tmin, t.tmax), f.fdat );
		push();
        if (lo > R || L > hi) {
			// dbgc("query END 0"); el;
			return T();
		}
		if (lo <= L && R <= hi) {
			// dbgc("query END contained" , MP(t.tmin, t.tmax)); el;
			return t;
		}
		T left;
		if ( c[0] ) {
			// dbgc("query RECURSE LEFT" , MP(c[0]->L , c[0]->R));
			left = left + c[0]->query(lo,hi);
		} else {
			// dbgc("query RECURSE LEFT" , "empty" );
		}
		T right;
		if ( c[1] ) {
			// dbgc("query RECURSE RIGHT" , MP(c[1]->L , c[1]->R));
			right = right + c[1]->query(lo,hi);
		} else {
			// dbgc("query RECURSE RIGHT" , "empty" );
		}
		// dbgc("query RECURSE COMB" , L , R );  el;
		return left + right;
        // return (c[0]?c[0]->query(lo,hi):T()) + (c[1]?c[1]->query(lo,hi):T());
	}

	// ! Need seg to store max.
	// ! This version has some jank specific to 757d2-E.
	int first_at_least(int targ) {
		dbgc("f_a_l" , targ , MP(L, R), MP(t.tmin, t.tmax) , f.fdat );
		push();
		if ( targ > R + (t.tmax < -INF/2 ? 0 : t.tmax) ) {
			// targ is above my range, i.e. there is no valid answer.
			return -1;
		}
		if ( targ <= L + (t.tmin > INF/2 ? 0 : t.tmin) ) {
			// targ is below my range.
			return L;
		}
        int M = (L+R)/2;
		int result;
		if ( !c[0] ) c[0] = /*new SLSTnode*/new_node(L  , M);
		dbgc("f_a_l LEFT" , targ , MP(L,R));
		result = c[0]->first_at_least( targ );
		dbgc("f_a_l LEFT DONE" , targ , MP(L,R) , result );
		if ( result != -1 ) {
			return result;
		}
		if ( !c[1] ) c[1] = /*new SLSTnode*/new_node(M+1, R);
		dbgc("f_a_l RIGHT" , targ , MP(L,R));
		result = c[1]->first_at_least( targ );
		dbgc("f_a_l RIGHT DONE" , targ , MP(L,R) , result );
		return result;
	}
};

SLSTnode buffer[20'000'000];

SLSTnode* SLSTnode::new_node(int L, int R) {
	static int pos = -1;
	++pos;
	buffer[pos].L = L;
	buffer[pos].R = R;
	return &buffer[ pos ];
}


bool SPECIAL = false;
void solve() {
    ints(N);
	if ( N == 200'000 ) {
		// SPECIAL = true;
	}
    vector<int> temps( N );
	vector<vector<int>> queries( N );

	F0R( k , N ) {
		cin >> temps[k];
		int num_queries;
		cin >> num_queries;
		queries[k].resize(num_queries);
		F0R( j , num_queries ) {
			cin >> queries[k][j];
		}
		dbg( k , temps[k] , queries[k] );
	}
	dbg(temps);
	el;

	SLSTnode st(0, SEGTREE_MAX);
	// each ( daytemp , temps ) {
	// 	st.upd( daytemp , daytemp , {daytemp} );
	// }

	// now iterate through days.
	ll lastans = 0;
	F0R( day , N ) {
		el; el; el; el; el;
		dbgc("START DAY" , day );
		int temp = temps[day];
		/*
			Need to find the segtree positions [L, R] describing points s.t. k+v = temp.
		*/
		int lb = st.first_at_least( temp );
		el;
		int ub = st.first_at_least( temp+1 );
		dbg( temp , lb , ub );
		if ( lb == - 1 ) {
			lb = SEGTREE_MAX + 1;
		}
		if ( ub == -1 ) {
			ub = SEGTREE_MAX + 1;
		}

		#ifdef DCCLYDE_LOCAL
		{
        el; dbgc("Print segtree");
        deque<SLSTnode> todo;
        todo.push_back( st );
        while ( todo.size() > 0 ) {
            auto& curr = todo.front();
            todo.pop_front();
            dbg( MP(curr.L , curr.R) , MP(curr.t.tmin, curr.t.tmax) , curr.f.fdat );
            F0R(i,2) if ( curr.c[i] ) todo.push_back( *curr.c[i] );
        } el;
        }
		#endif

		st.upd( 0 , lb-1 , {1} );
		st.upd( ub , SEGTREE_MAX , {-1} );

		each( q , queries[day] ) {
			lastans += q;
			lastans %= MOD;
			int qx = lastans;
			int qout = st.query( qx , qx ).tmin;
			int result = qout + qx;
			lastans = result;
			dbg( q , qx , qout , result );
			if ( !SPECIAL ) {
				cout << result << '\n';
			}
		}
	}

	return;
}

// ! Read the sample cases before writing code!
#pragma region
int main() {
	setIO();

    int T = 1;
    // std::cin >> T;  dbgc("loading num cases!!!")  // comment this out for one-case problems.
    for ( int k = 1 ; k <= T ; ++k ) {
        el; dbgc("CASE" , k ); el;
        solve();
    }

	dbg( sizeof(SLSTnode), sizeof(SLSTnode::T), sizeof(SLSTnode::F), sizeof(SLSTnode*) );
	dbg( nodes_allocated );
	if ( SPECIAL ) {
		cout << sizeof(SLSTnode) << '\t' << nodes_allocated << '\n';
	}
    return 0;
}
#pragma endregion
