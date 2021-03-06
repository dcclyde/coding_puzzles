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
//// I'm not used to the defs above.
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
#define mp make_pair
#define MP make_pair
#define MT make_tuple
//// #define f first
//// #define s second

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

//// #define lb lower_bound
//// #define ub upper_bound
tcT> int lwb(V<T>& a, const T& b) { return int(lb(all(a),b)-bg(a)); }
tcT> int upb(V<T>& a, const T& b) { return int(ub(all(a),b)-bg(a)); }

// loops
#define CONCAT_INNER(a, b) a ## b
#define CONCAT(a, b) CONCAT_INNER(a, b)
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(CONCAT(_,__LINE__),a)
#define each(a,x) for (auto& a: x)

//// const int MOD = 1e9+7; // 998244353;  // I can add this myself.
const int MX = 2e5+5;
const ll BIG = 1e18; // not too close to LLONG_MAX
const db PI = acos((db)-1);
//// const int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1}; // for every grid problem!!
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
int fdiv(int a, int b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down

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
    // is_iterable
    // https://stackoverflow.com/questions/13830158/check-if-a-variable-type-is-iterable
    // this gets used only when we can call begin() and end() on that type
    tcT, class = void> struct is_iterable : false_type {};
    tcT> struct is_iterable<T, void_t<decltype(begin(declval<T>())),
                                      decltype(end(declval<T>()))
                                     >
                           > : true_type {};
    tcT> constexpr bool is_iterable_v = is_iterable<T>::value;

    // is_readable
    tcT, class = void> struct is_readable : false_type {};
    tcT> struct is_readable<T,
            typename std::enable_if_t<
                is_same_v<decltype(cin >> declval<T&>()), istream&>
            >
        > : true_type {};
    tcT> constexpr bool is_readable_v = is_readable<T>::value;

    // is_printable
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
    #define lls(...) ll __VA_ARGS__; re(__VA_ARGS__);
    #define ll1(...) lls(__VA_ARGS__); decrement(__VA_ARGS__);
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
    // * Remove debug code; I'll use the tourist+me amalgamation instead.

    const clock_t beg = clock();
    #define dbg_time() dbg((db)(clock()-beg)/CLOCKS_PER_SEC)
}

inline namespace FileIO {
    void setIn(str s)  { freopen(s.c_str(),"r",stdin); }
    void setOut(str s) { freopen(s.c_str(),"w",stdout); }
    void setIO(str s = "") {
        cin.tie(0)->sync_with_stdio(0); // unsync C / C++ I/O streams
        cout.tie(0);
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

void debug_out() { std::cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    std::cerr << to_string(H) << "   ";
    debug_out(T...);
}

// #define BOLD_MAYBE ""    // NOT bold
#define BOLD_MAYBE     ";1"  // YES bold

#define OUT_RESET       "\033[0m"
#define OUT_BOLD        "\033[" << BOLD_MAYBE << "m"
#define OUT_RED         "\033[31" << BOLD_MAYBE << "m"
#define OUT_CYAN        "\033[36" << BOLD_MAYBE << "m"
// #define OUT_GREEN       "\033[32" << BOLD_MAYBE << "m"
#define OUT_GREEN       "\033[32" << "m"
#define OUT_BLUE        "\033[34" << BOLD_MAYBE << "m"
#define OUT_MARK        setw(24)<<"\033[0;30;41m"


#ifdef DCCLYDE_LOCAL
    #define el std::cerr << '\n';  // in my head I say "error line"
    // dbgc = "debug with comment"
    #define dbgcbase(A, ...) std::cerr << OUT_RED \
        << std::right << setw(20) << A \
        << std::right << setw(8) << __LINE__        \
        << OUT_BOLD << " : " << OUT_RESET \
        << OUT_GREEN << "[ " << #__VA_ARGS__ << " ]" \
        << OUT_BOLD << " :    " << OUT_RESET \
        << OUT_CYAN, debug_out(__VA_ARGS__); \
        std::cerr << OUT_RESET;
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

// ! ---------------------------------------------------------------------------

const int INF = 2e9;

#ifdef DCCLYDE_LOCALx
const int COORD_MAX_INPUT = 10;
#else
const int COORD_MAX_INPUT = 200'000;
#endif
const int COORD_MAX_INTERNAL = COORD_MAX_INPUT * 2 + 100;

pii xform(pii& p) {
    auto& [a, b] = p;
    return MP(fdiv(a+b,2), a-b);
}

pii xform_inv(pii& p) {
    if ( p.first == INF ) {
        return p;
    }
    auto& [x, y] = p;
    return MP((x+y)/2, (x-y)/2);
}

/*
    Track a collection of intervals.
    Example usage: codeforces/2022-02-23/E_working_on_data_structure.cpp
*/

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

    /*
        Return a value that's in pr but not in the data structure,
        or INF if pr is fully contained.
    */
    T test_contained(pair<T,T> pr) {
        auto& [a, b] = pr;
        it = x.lower_bound( MP(a,a) );
        // case where there's an interval starting at a
        // dbg(a, b, it==x.end(), it==x.begin());
        if ( it != x.end() ) {
            // dbgc("lower_bound", *it);
            if ( it->first == a ) {
                if ( it->second >= b ) {
                    return INF;
                } else {
                    return it->second + 1;
                }
            }
        }
        // no interval starting at a.
        // previous interval had better cover [a, b].
        if ( it == x.begin() ) {
            return a;
        }
        --it;
        if ( it->second >= b ) {
            return INF;
        }
        return it->second + 1;
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



/**
 * Description: 1D point update, range query where \texttt{cmb} is
 	* any associative operation. If $N=2^p$ then \texttt{seg[1]==query(0,N-1)}.
 * Time: O(\log N)
 * Source:
	* http://codeforces.com/blog/entry/18051
	* KACTL
 * Verification: SPOJ Fenwick
 */

tcT> struct SegTree { // cmb(ID,b) = b
	const T ID{};
    // T cmb(T a, T b) { return a+b; }
	int n; V<T> seg;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2;
		seg.assign(2*n,ID); }
	void pull(int p, int val) {
        // seg[p] = cmb(seg[2*p],seg[2*p+1]);
        // only add this if BOTH children have it.
        seg[p].insert(MP(val,val));
        dbgc("PULL", p, val, seg[p].x);
    }
	void upd(int p, int val) { // set val at position p
		seg[p += n].insert(MP(val,val));
        dbgc("UPD ", p, val, seg[p].x);
        int prev_p = p;
        for (p /= 2; p; p /= 2) {
            // if the adjacent child doesn't contain val, we're done here.
            if ( seg[prev_p ^ 1].test_contained(MP(val,val)) != INF ) {
                break;
            }
            pull(p, val);
            prev_p = p;
        }
    }

    pii find_missing(int p, int tc) {
        // check children until we find one that's missing tc.
        dbgc("fm", p, tc, seg[p].x);
        if ( p >= n ) {
            return MP(p - n, tc);
        }
        int tcL = seg[2*p].test_contained( MP(tc,tc) );
        dbgc("fm calls tc", tc, 2*p, seg[2*p].x, tcL);
        if ( tcL != INF ) {
            return find_missing( 2*p , tc );
        } else {
            return find_missing( 2*p+1 , tc );
        }
    }

    /*
        T/F: Is vert a subset of the intersection from l to r?
        If yes, return (INF, INF).
        If no, return a point that's not included.
    */
	pii query(int l, int r, pair<int,int> vert) {	// associative op on [l, r]
		// T ra = ID, rb = ID;
        dbgc("query", n, l, r, vert);
        if ( l < 0 ) {
            return MP(l, vert.first);
        }
        if ( r >= n ) {
            return MP(r, vert.first);
        }
        dbg();
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            dbg(l, r);
			if (l&1) {
                dbg(seg[l].x);
                // ra = cmb(ra,seg[l++]);
                int tc = seg[l].test_contained( vert );
                if ( tc != INF ) {
                    // found something missing.
                    return find_missing( l , tc );
                }
                ++l;
            }
			if (r&1) {
                dbg(seg[r].x);
                // rb = cmb(seg[--r],rb);
                --r;
                int tc = seg[r].test_contained( vert );
                if ( tc != INF ) {
                    return find_missing( r , tc );
                }
            }
		}
		return MP(INF, INF);
	}
};




void solve() {
    lls(N);
    vector<pii> dat( N );
    SegTree<IntervalUnion<int>> st;
    st.init( COORD_MAX_INTERNAL );
    FOR(k,0,N) {
        auto& [a, b] = dat[k];
        cin >> a >> b;
        tie(a, b) = MP(a+b, a-b);
        dbg(a, b);
        st.upd( a   , b   ); el;
        st.upd( a+1 , b   ); el;
        st.upd( a-1 , b   ); el;
        st.upd( a   , b+1 ); el;
        st.upd( a   , b-1 ); el;

        // #ifdef DCCLYDE_LOCAL
        // int dout = st.seg[23].test_contained(MP(-3,-3));
        // if ( dout == INF ) {
        //     dbg(k, dat[k], dout, st.seg[21].x);
        //     exit(1);
        // }
        // #endif
    }
    dbg(N, dat); el;
    for ( int k = 0 ; k < st.n ; ++k ) {
        if ( st.seg[k+st.n].x.size() > 0 ) {
            dbg(k, st.seg[k+st.n].x);
        }
    }
    el;

    /*
        Describe a 13-point square around (5, 3) as:
        [6, 10] x [0, 4].
        radius = r, center = (a, b)
        [a+b-r, a+b+r] x [
    */

    for ( auto& xx : dat ) {
        auto& [a, b] = xx;
        int lo = 0;  // definitely contained
        int hi = 500;  // definitely not contained. sqrt of num points.

        while ( hi - lo > 1 ) {
            int Q = (lo + hi) / 2;
            el; dbgc(OUT_MARK<<"BINSEARCH", xx, Q);
            /*
                Need to describe box of radius Q around (a, b).
            */
            pii response = st.query(a-Q, a+Q, MP(b-Q, b+Q));
            dbgc(OUT_MARK<<"st response", Q , xx, MP(a-Q,a+Q), MP(b-Q,b+Q), response, xform_inv(response));
            if ( response.first == INF ) {
                // this box is contained.
                lo = Q;
            } else {
                hi = Q;
            }
        }
        el;
        int Q = hi;
        pii final_response = st.query(a-Q, a+Q, MP(b-Q, b+Q));
        auto& [x, y] = final_response;
        int aaa = (x+y) / 2;
        int bbb = (x-y) / 2;
        cout << aaa << ' ' << bbb << '\n';
        // exit(1);
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
        el; dbgc("CASE" , k );
        solve();
    }

    return 0;
}
#pragma endregion
