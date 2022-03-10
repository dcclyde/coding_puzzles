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
///// #define f first
///// #define s second

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
//// #define rsz resize
//// #define ins insert
//// #define pb push_back
//// #define eb emplace_back
//// #define ft front()
//// #define bk back()

///// #define lb lower_bound
///// #define ub upper_bound
tcT> int lwb(V<T>& a, const T& b) { return int(lb(all(a),b)-bg(a)); }
tcT> int upb(V<T>& a, const T& b) { return int(ub(all(a),b)-bg(a)); }

// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

///// const int MOD = 1e9+7; // 998244353;  // I can add this myself.
const int MX = 2e5+5;
const ll BIG = 1e18; // not too close to LLONG_MAX
const db PI = acos((db)-1);
///// const int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1}; // for every grid problem!!
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
	tcTU> void re(pair<T,U>& p) { re(p.first,p.second); }
	tcT> typename enable_if<needs_input_v<T>,void>::type re(T& i) {
		each(x,i) re(x); }
	tcTUU> void re(T& t, U&... u) { re(t); re(u...); } // read multiple

	// rv: resize and read vectors
	void rv(size_t) {}
	tcTUU> void rv(size_t N, V<T>& t, U&... u);
	template<class...U> void rv(size_t, size_t N2, U&... u);
	tcTUU> void rv(size_t N, V<T>& t, U&... u) {
		t.resize(N); re(t);
		rv(N,u...); }
	template<class...U> void rv(size_t, size_t N2, U&... u) {
		rv(N2,u...); }

	// dumb shortcuts to read in ints
	void decrement() {} // subtract one from each
	tcTUU> void decrement(T& t, U&... u) { --t; decrement(u...); }
	#define ints(...) int __VA_ARGS__; re(__VA_ARGS__);
	#define int1(...) ints(__VA_ARGS__); decrement(__VA_ARGS__);
}

// inline namespace ToString {
// 	tcT> constexpr bool needs_output_v = !is_printable_v<T> && is_iterable_v<T>;

// 	// ts: string representation to print
// 	tcT> typename enable_if<is_printable_v<T>,str>::type ts(T v) {
// 		stringstream ss; ss << fixed << setprecision(15) << v;
// 		return ss.str(); } // default
// 	tcT> str bit_vec(T t) { // bit vector to string
// 		str res = "{"; F0R(i,sz(t)) res += ts(t[i]);
// 		res += "}"; return res; }
// 	str ts(V<bool> v) { return bit_vec(v); }
// 	template<size_t SZ> str ts(bitset<SZ> b) { return bit_vec(b); } // bit vector
// 	tcTU> str ts(pair<T,U> p); // pairs
// 	tcT> typename enable_if<needs_output_v<T>,str>::type ts(T v); // vectors, arrays
// 	tcTU> str ts(pair<T,U> p) { return "("+ts(p.first)+", "+ts(p.second)+")"; }
// 	tcT> typename enable_if<is_iterable_v<T>,str>::type ts_sep(T v, str sep) {
// 		// convert container to string w/ separator sep
// 		bool fst = 1; str res = "";
// 		for (const auto& x: v) {
// 			if (!fst) res += sep;
// 			fst = 0; res += ts(x);
// 		}
// 		return res;
// 	}
// 	tcT> typename enable_if<needs_output_v<T>,str>::type ts(T v) {
// 		return "{"+ts_sep(v,", ")+"}"; }

// 	// for nested DS
// 	template<int, class T> typename enable_if<!needs_output_v<T>,vs>::type
// 	  ts_lev(const T& v) { return {ts(v)}; }
// 	template<int lev, class T> typename enable_if<needs_output_v<T>,vs>::type
// 	  ts_lev(const T& v) {
// 		if (lev == 0 || !sz(v)) return {ts(v)};
// 		vs res;
// 		for (const auto& t: v) {
// 			if (sz(res)) res.back() += ",";
// 			vs tmp = ts_lev<lev-1>(t);
// 			res.insert(end(res),all(tmp));
// 		}
// 		F0R(i,sz(res)) {
// 			str bef = " "; if (i == 0) bef = "{";
// 			res[i] = bef+res[i];
// 		}
// 		res.back() += "}";
// 		return res;
// 	}
// }

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

void debug_out() { std::cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    std::cerr << to_string(H) << "   ";
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
#define OUT_MARK        setw(24)<<"\033[0;30;41m"


#ifdef DCCLYDE_LOCAL
    // dbgc = "debug with comment"
    #define dbgcbase(A, ...) cerr << OUT_RED \
        << std::right << setw(20) << A \
        << std::right << setw(8) << __LINE__        \
        << OUT_BOLD << " : " << OUT_RESET \
        << OUT_GREEN << "[ " << #__VA_ARGS__ << " ]" \
        << OUT_BOLD << " :    " << OUT_RESET \
        << OUT_CYAN, debug_out(__VA_ARGS__); \
        cerr << OUT_RESET;
    #define dbgbase(...) dbgc2("", __VA_ARGS__)
    // #define dbg(...) ;
    // #define dbgc(...) ;
    // #define el ;
    #define el cerr << '\n';  // in my head I say "error line"
    #define dbg(...) dbgbase(__VA_ARGS__)
    #define dbgc(...) dbgcbase(__VA_ARGS__)
    // useful as a second distinct "log level"
    #define dbg2(...) dbgbase(__VA_ARGS__)
    #define dbgc2(...) dbgcbase(__VA_ARGS__)
    #define el2 cerr << '\n';  // in my head I say "error line"
#else
    #define dbgc(...) ;
    #define dbg(...) ;
    #define dbg2(...) ;
    #define dbgc2(...) ;
    #define el ;
#endif

#pragma endregion

ll f(const pii& a, const pii& b) {
    return (a.first + b.first) * (a.second + b.second);
}

// buckets with more than this many repeats get special handling.
#ifdef DCCLYDE_LOCAL
constexpr int CUTOFF = 2;
#else
constexpr int CUTOFF = 100;
#endif

void solve() {
    ints(N, M);
    map<int,int> dat_pre;
    rep(N) {
        ints(x);
        ++dat_pre[x];
    }
    set<pii> bad_pairs;
    rep(M) {
        ints(a, b);
        bad_pairs.emplace(a,b);
        bad_pairs.emplace(b,a);
    }
    dbg(N, dat_pre);
    dbg(M, bad_pairs);
    el;

    // vector<pii> little;
    map<int, vector<int>> mlittle;
    vector<pii> big;
    for ( auto& p : dat_pre ) {
        if ( p.second > CUTOFF ) {
            big.push_back( p );
        } else {
            // little.push_back( p );
            mlittle[p.second].push_back( p.first );
        }
    }
    #ifdef DCCLYDE_LOCAL
    // actually build all pairs for debugging purposes.
    vector<pair<ll, pii>> results_debug;
    for ( auto& pa : dat_pre ) {
        for ( auto& pb : dat_pre ) {
            if ( pb.first >= pa.first ) {
                break;
            }
            dbg(f(pa, pb), MP(pb.first, pa.first));
            results_debug.emplace_back( f(pa, pb), MP(pb.first, pa.first) );
        }
    }
    sort(rall(results_debug));
    dbg(results_debug);
    results_debug.resize( min(M+1, (int)results_debug.size() ) );
    dbg(results_debug);
    #endif


    vector<pair<int, vector<int>>> little;
    for ( auto& [num_copies, values] : mlittle ) {
        little.emplace_back( num_copies , move(values) );
        reverse(all(little.back().second));  // sort descending
    }

    // build all combinations of big items.
    // cost is |big|^2 <= |N/CUTOFF|^2.
    vector<pair<ll, pii>> big_results;
    big_results.reserve( big.size() * big.size() / 2 );
    for ( int k = 0 ; k < big.size() ; ++k ) {
        for ( int j = 0 ; j < k ; ++j ) {
            big_results.emplace_back( f(big[j], big[k]), MP(big[j].first, big[k].first) );
        }
    }
    sort(rall(big_results));
    dbg(little);
    dbg(big);
    dbg(big_results);
    el;

    dbg2();
    // ok now start a big binary search.
    // I want largest Q s.t. there are M+1 outputs >= Q.
    ll lo = 0;  // too low
    ll hi = 2e18;  // too high
    while ( hi - lo > 1 ) {
        ll Q = (hi + lo) / 2;
        // #ifdef DCCLYDE_LOCAL
        // Q = 120;
        // static bool ran = false;
        // if ( ran ) {
        //     exit(1);
        // } else {
        //     ran = true;
        // }
        // #endif
        // find how many items are >= Q from some variety of different categories.
        int total_ge_Q = 0;
        dbgc2(OUT_MARK<<"START BINSEARCH" , Q);

        // * BIG x BIG
        int num_from_big = fstTrue(
            0,
            (int)big_results.size()-1,
            [&](int idx) { return big_results[idx].first < Q; }
        );
        total_ge_Q += num_from_big;
        dbg(num_from_big);el;

        // * BIG x LITTLE
        ll big_x_small = 0;
        for ( auto& bp : big ) {
            ll geq_local = 0;
            for ( auto& [num_copies, values] : little ) {
                // what value is needed to give a result >= Q?
                // I need (bp.second + num_copies) * (bp.first + x) >= Q
                ll min_good_value = cdiv( Q , (bp.second + num_copies) ) - bp.first;
                int num_good_values = fstTrue(
                    0,
                    (int)values.size() - 1,
                    [&](int idx) { return values[idx] < min_good_value; }
                );
                dbgc("BxL", bp, MP(num_copies,values), num_good_values);
                geq_local += num_good_values;
            }
            dbgc("BxL outer", bp, geq_local);
            big_x_small += geq_local;
        }
        dbg(big_x_small); el;
        total_ge_Q += big_x_small;

        // * LITTLE x LITTLE
        ll small_x_small = 0;
        FOR( aidx , 0 , little.size() ) {
            FOR( bidx , 0 , aidx+1 ) {
                // use the "walk through a matrix" trick.
                auto& [nA, vA] = little[aidx];
                auto& [nB, vB] = little[bidx];

                auto check = [&](int pA, int pB) -> bool {
                    if ( pA == vA.size() || pB == vB.size() ) return true;
                    return f(MP(nA, vA[pA]), MP(nB, vB[pB])) < Q;
                };

                int posA = 0;
                while ( posA < vA.size() && !check(posA, 0) ) {
                    ++posA;
                }
                int out_local = posA;
                if ( aidx == bidx && posA > 0 ) {
                    --out_local;
                }
                for ( int posB = 1 ; posB < vB.size() ; ++posB ) {
                    // move posA as needed.
                    while ( posA >= 0 && check(posA, posB) ) {
                        --posA;
                    }
                    ++posA;  // I want the first index where it's true, not the last false.
                    if ( posA == 0 ) {
                        break;
                    }
                    out_local += posA;
                    if ( aidx == bidx && posA > posB ) {
                        out_local -= 1;  // Don't count (x, x) as a pair.
                    }
                }
                dbgc("LxL", MP(nA,vA), MP(nB,vB), out_local);
                small_x_small += out_local;
            }
        }
        dbg(small_x_small);
        total_ge_Q += small_x_small;
        dbg(total_ge_Q);

        if ( total_ge_Q >= M+1 ) {
            lo = Q;  // Q <= the right answer
        } else {
            hi = Q;  // Q > the right answer
        }
    }

    ll Q = lo;
    dbg2(Q);

    // now we need to actually build+sort the list of pairs giving values >= Q.
    set<pair<ll, pii>> final_options;

    {
        // * BIG x BIG
        int num_from_big = fstTrue(
            0,
            (int)big_results.size()-1,
            [&](int idx) { return big_results[idx].first < Q; }
        );
        final_options.insert(
            big_results.begin(),
            big_results.begin() + num_from_big
        );
    }

    {
        // * BIG x LITTLE
        for ( auto& bp : big ) {
            for ( auto& [num_copies, values] : little ) {
                // what value is needed to give a result >= Q?
                // I need (bp.second + num_copies) * (bp.first + x) >= Q
                ll min_good_value = cdiv( Q , (bp.second + num_copies) ) - bp.first;
                int num_good_values = fstTrue(
                    0,
                    (int)values.size() - 1,
                    [&](int idx) { return values[idx] < min_good_value; }
                );
                // grab all cases with bp x top (num_good_values) items from little list.
                FOR(k, 0, num_good_values) {
                    final_options.emplace(
                        f(bp, MP(values[k], num_copies)),
                        MP(values[k], bp.first)
                    );
                }
            }
        }
    }

    {
        // * LITTLE x LITTLE
        FOR( aidx , 0 , little.size() ) {
            FOR( bidx , 0 , aidx+1 ) {
                // use the "walk through a matrix" trick.
                auto& [nA, vA] = little[aidx];
                auto& [nB, vB] = little[bidx];

                auto check = [&](int pA, int pB) -> bool {
                    if ( pA == vA.size() || pB == vB.size() ) return true;
                    return f(MP(nA, vA[pA]), MP(nB, vB[pB])) < Q;
                };

                int posA = 0;
                while ( posA < vA.size() && !check(posA, 0) ) {
                    ++posA;
                }
                int out_local = posA;
                FOR(k, 0, posA) {
                    if ( nA == nB && vA[k] == vB[0] ) {
                        continue;
                    }
                    final_options.emplace(
                        f(MP(nA, vA[k]), MP(nB, vB[0])),
                        MP(vA[k], vB[0])
                    );
                }
                for ( int posB = 1 ; posB < vB.size() ; ++posB ) {
                    // move posA as needed.
                    while ( posA >= 0 && check(posA, posB) ) {
                        --posA;
                    }
                    ++posA;  // I want the first index where it's true, not the last false.
                    if ( posA == 0 ) {
                        break;
                    }
                    FOR(k, 0, posA) {
                        if ( nA == nB && vA[k] <= vB[posB] ) {
                            continue;
                        }
                        dbg(
                            f(MP(nA, vA[k]), MP(nB, vB[posB])),
                            MP(vA[k], vB[posB])
                        );
                        final_options.emplace(
                            f(MP(nA, vA[k]), MP(nB, vB[posB])),
                            MP(vA[k], vB[posB])
                        );
                    }
                    out_local += posA;
                    if ( aidx == bidx ) {
                        // undo counting same pairs twice.
                        out_local -= min(posB+1, posA);
                    }
                }
                dbgc("LxL", MP(nA,vA), MP(nB,vB), out_local);
                // small_x_small += out_local;
            }
        }
    }
    dbg(final_options);

    for ( auto& [score, values] : final_options | views::reverse ) {
        if ( bad_pairs.count(values) ) {
            continue;
        }
        dbg2(score, values);
        cout << score << '\n';
        return;
    }
    cout << ":(\n";
	return;
}

// ! Read the sample cases before writing code!
#pragma region
int main() {
	setIO();

    int T = 1;
    std::cin >> T;  dbgc("loading num cases!!!")  // comment this out for one-case problems.
    for ( int k = 1 ; k <= T ; ++k ) {
        el; dbgc("CASE" , k );
        solve();
    }

    return 0;
}
#pragma endregion
