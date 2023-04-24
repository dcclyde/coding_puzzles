#pragma region
#if defined(DCCLYDE_LOCAL) && __has_include("/home/dcclyde/puzzles/code/templates/superheader.h")
    #include "/home/dcclyde/puzzles/code/templates/superheader.h"
#else
    #include <bits/stdc++.h>
    #include <ext/pb_ds/assoc_container.hpp>
    #include <ext/pb_ds/tree_policy.hpp>
#endif
#ifdef _OPENMP
    #include <omp.h>
#endif
using namespace std;
using namespace __gnu_pbds;

#define CLEAN 0
#define CF 1
#define GCJ 2

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
using vll = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pii>;
using vpii = V<pii>;
using vpl = V<pll>;
using vpll = V<pll>;
using vpd = V<pdd>;

// vectors
// size(x), rbegin(x), rend(x) need C++17
#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define pb push_back
#define eb emplace_back
#define emp emplace
#define ft front()
#define bk back()

//// #define lb lower_bound
//// #define ub upper_bound
//// tcT> int lwb(V<T>& a, const T& b) { return int(lb(all(a),b)-bg(a)); }
//// tcT> int upb(V<T>& a, const T& b) { return int(ub(all(a),b)-bg(a)); }

// Easily create k-dimensional vectors (C++14).
template <class T>
vector<T> ndvec(size_t size, T initialValue) {
    return vector<T>(size, initialValue);
}

template <class T, class... Args>
auto ndvec(size_t head, Args&&... tail) {
    auto inner = ndvec<T>(tail...);
    return vector<decltype(inner)>(head, inner);
}

// bitwise ops
// also see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set bits_set
constexpr ll pct(ll x) { return __builtin_popcountll(x); }
constexpr int bigbit(ll x) { // assert(x >= 0); // make C++11 compatible until USACO updates ...
    return x == 0 ? 0 : 63-__builtin_clzll(x); } // floor(log2(x))
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }

ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(auto a, auto b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down

ll powll(ll b, ll e) {
    ll out = 1;
    while (true) {
        if (e&1) {out *= b;}
        e >>= 1;
        if (e == 0) {break;}
        b *= b;
    }
    return out;
}
ll rootll(ll a, ll n) {  // nth root of a, rounded down.
    // assert(a >= 0); assert(n >= 1);
    ll x = pow(a, 1./n);
    while (powll(x, n) > a) {--x;}
    while (powll(x+1, n) <= a) {++x;}
    return x;
}
ll sqrtll(ll a) {return rootll(a, 2);}
ll powmod(ll b, ll e, ll mod) {
    ll out = 1;
    while (e) {
        if (e&1) {out *= b; out %= mod;}
        b *= b; b %= mod; e >>= 1;
    }
    return out;
}

tcTU> bool ckmin(T& a, const U& b) {
    return (T)b < a ? a = (T)b, 1 : 0; } // set a = min(a,b)
tcTU> bool ckmax(T& a, const U& b) {
    return a < (T)b ? a = (T)b, 1 : 0; } // set a = max(a,b)

int maxi(int a, int b) {return max((int)a, (int)b);}
int mini(int a, int b) {return min((int)a, (int)b);}
ll maxll(ll a, ll b) {return max((ll)a, (ll)b);}
ll minll(ll a, ll b) {return min((ll)a, (ll)b);}


template <typename, typename = void>
constexpr bool is_iterable_v{};

template <typename T>
constexpr bool is_iterable_v<
    T,
    std::void_t< decltype(std::declval<T>().begin()),
                decltype(std::declval<T>().end())
    >
> = true;

// Safe hash maps. See https://codeforces.com/blog/entry/62393
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    template<class T, class U>
    size_t operator()(const pair<T,U>& x) const {
        uint64_t a = (*this)(x.first);
        uint64_t b = (*this)(x.second);
        return a + 3*b;
    }

    template <class... Ts> size_t operator()(const tuple<Ts...>& t) const {
        size_t out = 0;
        apply([&](const Ts& ...args) {
            ll m = 0;
            ((out += (*this)(args) * ++m), ...);
        }, t);
        return out;
    }

    template <typename A>
    typename enable_if<is_iterable_v<A>, size_t>::type operator()(const A& v) const {
        uint64_t out = 0;
        uint64_t offset = 1;
        for (const auto& x : v) {
            uint64_t curr = (*this)(x);
            out ^= curr * offset;
            offset *= 3;
        }
        return out;
    }
};

/**
    Reasons for different definitions:
        gp_hash_table seems fastest in general.
        custom_hash lets me hash some types (tuples, vectors) that aren't hashable by default.
        I can't use unordered_map on codeforces servers because it's hackable.
        If _GLIBCXX_DEBUG is defined then gp_hash_table doesn't compile (printability stuff?)
 */
#if defined(_GLIBCXX_DEBUG)
    // template<class A, class B> using umap = gp_hash_table<A,B,custom_hash>;
    template<class A, class B> using umap = unordered_map<A,B,custom_hash>;  // slower?
    // template<class A, class B> using umap = map<A,B>;  // ok for tiny cases?
    // template<class A, class B> using umap = unordered_map<A,B>;  // slower and unsafe?

    // template<class A> using uset = gp_hash_table<A,null_type,custom_hash>;
    template<class A> using uset = unordered_set<A, custom_hash>;
    // template<class A> using uset = set<A>;
    // template<class A> using uset = unordered_set<A>;
#else
    template<class A, class B> using umap = gp_hash_table<A,B,custom_hash>;
    // template<class A, class B> using umap = unordered_map<A,B,custom_hash>;  // slower?
    // template<class A, class B> using umap = map<A,B>;  // ok for tiny cases?
    // template<class A, class B> using umap = unordered_map<A,B>;  // slower and unsafe?

    template<class A> using uset = gp_hash_table<A,null_type,custom_hash>;
    // template<class A> using uset = unordered_set<A, custom_hash>;
    // template<class A> using uset = set<A>;
    // template<class A> using uset = unordered_set<A>;
#endif

#define unordered_map DCCLYDE_REMINDER_DONT_USE_UNPROTECTED_HASH_MAP
#define unordered_set DCCLYDE_REMINDER_DONT_USE_UNPROTECTED_HASH_SET

// Example: tinyurl.com/2c222yvx
// myset.order_of_key(5) = number of elements < 5
// myset.find_by_order(5) = iterator to 5th largest element (0-indexed)
template <class c, class cmp = less<c>>
using indexed_set = tree<c, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;
template<class c, class d, class cmp = less<c>>
using indexed_map = tree<c, d, cmp, rb_tree_tag, tree_order_statistics_node_update>;

// Maybe I need this if I want the indexed_ stuff to compile with _GLIBCXX_DEBUG?
namespace std {
    ostream& operator<<(ostream &o, vector<int>) {return o;}
}


// loops
#define CONCAT_INNER(a, b) a ## b
#define CONCAT(a, b) CONCAT_INNER(a, b)
#define FORll(i,a,b) for (ll i = ((ll)a); i < ((ll)b); ++i)
#define FORint(i,a,b) for (int i = ((int)a); i < ((int)b); ++i)
// #define FOR3(i,a,b) for (int i = (a); i < (b); ++i)
#define FOR3(i,a,b) FORll(i,a,b)
#define F0R(i,a) FOR(i,0,a)
#define FOR2(i,a) FOR(i,0,a)
#define ROFll(i,a,b) for (ll i = ((ll)b)-1; i >= ((ll)a); --i)
#define ROFint(i,a,b) for (int i = ((int)b)-1; i >= ((int)a); --i)
// #define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define ROF(i,a,b) ROFll(i,a,b)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(CONCAT(_,__LINE__),a)
#define each(a,x) for (auto& a: x)
#define foreach(a,x) each(a,x)

#define FOR1(x) for(auto x)
#if __cplusplus >= 202002L
auto stepped_iota(ll start, ll end, ll step=1) {
    ll iter_count = cdiv(end-start, step);
    ckmax(iter_count, 0);
  return std::ranges::views::iota(0LL, iter_count) |
         std::ranges::views::transform([=](ll x) { return x * step + start; });
}
#define FOR4(i,s,e,step) for(auto i : stepped_iota(s, e, step))
#else
#define FOR4(i,s,e,step) for(ll i = s; i != e && ((i<e) == (s<e)) ; i += step)
#endif

// just as an example of how to iterate in reverse order
// for(auto& x : dat | views::reverse) {}

#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define FOR(...) GET_MACRO(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)

#pragma region  // rangeint
V<int> rangeint(int start, int end, int inc=1) {
    V<int> out;
    if (inc > 0) {
        for(int curr = start; curr < end; curr += inc) {
            out.push_back(curr);
        }
        return out;
    } else {
        for(int curr = start; curr > end; curr += inc) {
            out.push_back(curr);
        }
        return out;
    }
}
#pragma endregion

// const int MX = 2e5+5;
const ll BIG = 1e18; // not too close to LLONG_MAX
const db PI = acos((db)-1);
//// const int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1}; // for every grid problem!!
vector<pii> stepsOrthogonal = {{1,0},{0,1},{-1,0},{0,-1}};
vector<pii> stepsDiagonal = {{1,1},{1,-1},{-1,-1},{-1,1}};
vector<pii> steps8dirs = {{1,0},{0,1},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
#pragma region  // rng examples
// std::uniform_real_distribution<db> rand_dbl(0, 1);  // [L, R)
// db ard = unif_db(rng);
// std::uniform_int_distribution<int> rand_int(1, 2);  // inclusive
// int ri = rand_int(rng);
#pragma endregion
template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>;

tcT> ll fstTrue(ll lo, ll hi, T f) {
    ++hi; assert(lo <= hi); // assuming f is increasing
    while (lo < hi) { // find first index such that f is true
        ll mid = lo+(hi-lo)/2;
        f(mid) ? hi = mid : lo = mid+1;
    }
    return lo;
}
tcT> ll lstTrue(ll lo, ll hi, T f) {
    --lo; assert(lo <= hi); // assuming f is decreasing
    while (lo < hi) { // find first index such that f is true
        ll mid = lo+(hi-lo+1)/2;
        f(mid) ? lo = mid : hi = mid-1;
    }
    return lo;
}
tcT> void remDup(vector<T>& v) { // sort and remove duplicates
    sort(all(v)); v.erase(unique(all(v)),end(v)); }
tcTU> void erase(T& t, const U& u) { // don't erase element that doesn't exist from (multi)set
    auto it = t.find(u); assert(it != end(t));
    t.erase(it); }

// use like sumv(all(dat))
template<class ForwardIt>
auto sumv(ForwardIt first, ForwardIt last)
{
    /**
        Careful: accumulation in int could overflow.
        Therefore, make `out` an ll if the data is any integer type.
        Otherwise, out is the same type as the data.
     */
    typename std::conditional<
        std::is_integral<typename std::iterator_traits<ForwardIt>::value_type>::value,
        ll,
        typename std::iterator_traits<ForwardIt>::value_type
    >::type out {};
    for (; first != last; ++first) {
        out += *first;
    }
    return out;
}
template<class T> auto sumv(T&& data) {return sumv(all(data));}
template<class T> auto max_element(T&& data) {return *max_element(all(data));}
template<class T> auto min_element(T&& data) {return *min_element(all(data));}


#define tcTUU tcT, class ...U

inline namespace Helpers {
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


    template <class... Ts> void increment_one(tuple<Ts...>& t, int inc);
    template <class A, class B> void increment_one(pair<A,B>& t, int inc);
    tcT> typename enable_if<!is_iterable_v<T>, void>::type increment_one(T& x, int inc) {x += inc;}
    tcT> typename enable_if<is_iterable_v<T>, void>::type increment_one(T& t, int inc) { for(auto&& x : t) {increment_one(x, inc);} }

    template <class... Ts> void increment_one(tuple<Ts...>& t, int inc) {
        apply([&](Ts& ...args) {(increment_one(args, inc), ...);}, t);
    }
    template <class A, class B> void increment_one(pair<A,B>& t, int inc) {
        t.f += inc; t.s += inc;
    }

    void increment(auto& ...args) {(increment_one(args, +1), ...);} // add one to each, for output.  BE CAREFUL TO UNDO MODIFICATIONS
    void decrement(auto& ...args) {(increment_one(args, -1), ...);} // subtract one from each, for input. MODIFICATION IS THE GOAL
}

inline namespace Input {
    tcT> constexpr bool needs_input_v = !is_readable_v<T> && is_iterable_v<T>;

    // re: read
    void re(auto &...args);
    tcTU> void re(pair<T,U>& p) { re(p.first,p.second); }  // pairs
    tcT> void re(complex<T>& c) { T a,b; re(a,b); c = {a,b}; } // complex
    tcT> typename enable_if<needs_input_v<T>,void>::type re(T& i); // ex. vectors, arrays

    template <class... Ts> void re(tuple<Ts...> &t) {
        apply([](Ts &...args) { re(args...); }, t);
    }

    tcT> typename enable_if<needs_input_v<T>,void>::type re(T& i) {
        each(x,i) re(x); }
    void re(auto& ...args) { ((cin >> args), ...); } // read multiple

    // rv: resize and read vectors
    void rv(size_t) {}
    tcTUU> void rv(size_t N, V<T>& t, U&... u);
    template<class...U> void rv(size_t, size_t N2, U&... u);
    tcTUU> void rv(size_t N, V<T>& t, U&... u) {
        t.resize(N); re(t);
        rv(N,u...); }
    template<class...U> void rv(size_t, size_t N2, U&... u) {
        rv(N2,u...); }
    void rv1(size_t) {}
    tcTUU> void rv1(size_t N, V<T>& t, U&... u) {
        t.resize(N); re(t); for(auto& x : t) decrement(x);
        rv1(N,u...); }


    // dumb shortcuts to read in ints
    #define ints(...) int __VA_ARGS__; re(__VA_ARGS__);
    #define int1(...) ints(__VA_ARGS__); decrement(__VA_ARGS__);
    #define chars(...) char __VA_ARGS__; re(__VA_ARGS__);
    #define lls(...) ll __VA_ARGS__; re(__VA_ARGS__);
    #define ll1(...) lls(__VA_ARGS__); decrement(__VA_ARGS__);
    #define strings(...) string __VA_ARGS__; re(__VA_ARGS__);
}

inline namespace ToString {
    tcT> constexpr bool needs_output_v = !is_printable_v<T> && is_iterable_v<T>;

    // ts: string representation to print
    tcT> typename enable_if<is_printable_v<T>,str>::type ts(T v, ll d=15) {
        stringstream ss; ss << fixed << setprecision(d) << v;
        return ss.str(); } // default
    tcT> str bit_vec(T t) { // bit vector to string
        str res = "{"; F0R(i,sz(t)) res += ts(t[i]);
        res += "}"; return res; }
    str ts(V<bool> v) { return bit_vec(v); }
    template<size_t SZ> str ts(bitset<SZ> b) { return bit_vec(b); } // bit vector
    tcTU> str ts(pair<T,U> p); // pairs
    tcT> typename enable_if<needs_output_v<T>,str>::type ts(T v); // vectors, arrays
    tcTU> str ts(pair<T,U> p) { return "("+ts(p.first)+", "+ts(p.second)+")"; }
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
            if (sz(res)) res.back() += ",";
            vs tmp = ts_lev<lev-1>(t);
            res.insert(end(res),all(tmp));
        }
        F0R(i,sz(res)) {
            str bef = " "; if (i == 0) bef = "{";
            res[i] = bef+res[i];
        }
        res.back() += "}";
        return res;
    }
}

inline namespace Output {
    string tsish(char c) {return string(1, c);}
    string tsish(const char* s) {return s;}
    string tsish(double x) {return ToString::ts(x);}
    string tsish(long double x) {return ToString::ts(x);}
    string tsish(const string& x) {return x;}
    string tsish(const auto& t) {return to_string(t);}
    template<typename A, typename B> string tsish(const pair<A,B>& t) {
        return tsish(t.f) + " " + tsish(t.s);}
    template<class... Ts> string tsish(const tuple<Ts...>& t) {
        string out = "";
        apply([&](const Ts& ...args) {((out += ts(args), out.push_back(' ')), ...);}, t);
        out.pop_back();
        return out;}

    template<class T> void pr_sep(ostream& os, str, const T& t) { os << tsish(t); }
    template<class T, class... U> void pr_sep(ostream& os, str sep, const T& t, const U&... u) {
        pr_sep(os,sep,t); os << sep; pr_sep(os,sep,u...); }
    template<class T> void pr_sep1(ostream& os, str, T& t) { increment(t); os << tsish(t); decrement(t); }
    template<class T, class... U> void pr_sep1(ostream& os, str sep, T& t, U&... u) {
        pr_sep1(os,sep,t); os << sep; pr_sep1(os,sep,u...); }
    // print w/ no spaces
    template<class ...T> void pr(const T&... t) { pr_sep(cout,"",t...); }
    // print w/ spaces, end with newline
    void ps() { cout << "\n"; }
    template<class ...T> void ps(const T&... t) { pr_sep(cout," ",t...); ps(); }
    void ps1() { cout << "\n"; }
    template<class ...T> void ps1(T&... t) { pr_sep1(cout," ",t...); ps1(); }
    void pso() {}
    template<class ...T> void pso(const T&... t) { pr_sep(cout," ",t...); pso(); }
    void pso1() {}
    template<class ...T> void pso1(T&... t) { pr_sep1(cout," ",t...); pso1(); }

    template<class T>
    void pv(T& dat) {bool f=1; for(auto&& x : dat) {if (!f) {cout<<' ';} f=0; cout << tsish(x);} cout<<'\n';}
    template<class T>
    void pv1(T& dat) {bool f=1; increment(dat); for(auto&& x : dat) {if (!f) {cout<<' ';} f=0; cout << tsish(x);} cout<<'\n'; decrement(dat);}
    template<class T>
    void pvn(T& dat) {bool f=1; for(auto&& x : dat) {if (!f) {cout<<'\n';} f=0; cout << tsish(x);} cout<<'\n';}
    template<class T>
    void pvn1(T& dat) {bool f=1; increment(dat); for(auto&& x : dat) {if (!f) {cout<<'\n';} f=0; cout << tsish(x);} cout<<'\n'; decrement(dat);}
    // * Remove debug code; I'll use the tourist+me amalgamation instead.

#ifndef _OPENMP
    const clock_t beg = clock();
    #define dbg_time() dbg((db)(clock()-beg)/CLOCKS_PER_SEC)
    db TIME() {return (db)(clock()-beg)/CLOCKS_PER_SEC;}
#else
    const db beg = omp_get_wtime();
    db TIME() {return omp_get_wtime() - beg;}
#endif
    void flush() {std::cout << std::flush;}
}

inline namespace FileIO {
    void setIn(str s)  { if ( !freopen(s.c_str(),"r",stdin) ) assert(false); }
    void setOut(str s) { if ( freopen(s.c_str(),"w",stdout) ) assert(false); }
    void setIO(str s = "") {
        cin.tie(0)->sync_with_stdio(0); // unsync C / C++ I/O streams
        cout.tie(0);
        cin.exceptions(cin.failbit);
        // throws exception when do smth illegal
        // ex. try to read letter into int
        if (sz(s)) setIn(s+".in"), setOut(s+".out"); // for old USACO
    }
}

#pragma region  // debugging
// * debug setup mostly stolen from tourist. https://codeforces.com/contest/1540/submission/120602670
// * dcclyde added line numbers, colors, probably some other stuff.

// for dbg printouts of C arrays.
template<typename T>
V<T> vform(T* arr, ll len) { return V<T> (arr, arr+len); }

template <typename A, typename B>
string tsdbg(pair<A, B> p);

template<class ...Ts> string tsdbg(const tuple<Ts...>& t);

string tsdbg(db x) {
    return ts(x, 3);
    // ostringstream out;
    // out.precision(3);
    // out << fixed << x;
    // return out.str();
}
string tsdbg(double x) { return ts(x, 3); }
string tsdbg(float x) { return ts(x, 3); }

string tsdbg(const string& s) {
    return '"' + s + '"';
}

string tsdbg(char c) {
    return "'" + string(1, c) + "'";
}

template<typename T>
typename enable_if<is_integral<T>::value, string>::type tsdbg(T x) {return to_string(x);}

string tsdbg(__int128_t x) {
    if (x == 0) {return "0";}
    string out;
    while (x > 0) {out.push_back('0' + (x%10)); x /= 10;}
    reverse(all(out));
    return out;
}

string tsdbg(const char* s) {
    return tsdbg((string) s);
}

string tsdbg(bool b) {
    return (b ? "true" : "false");
}

string tsdbg(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += tsdbg(v[i]);
    }
    res += "}";
    return res;
}

template <size_t N>
string tsdbg(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
typename enable_if<is_iterable_v<A>, string>::type tsdbg(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += tsdbg(x);
    }
    res += "}";
    return res;
}

template<typename T, typename A, typename B>
V<T> pqueue_to_iterable(priority_queue<T,A,B> PQ) { // PASS BY VALUE!
    V<T> working;
    while (!PQ.empty()) {working.push_back(PQ.top()); PQ.pop();}
    // reverse(all(working));
    return working;
}
template<typename T, typename A, typename B>
string tsdbg(priority_queue<T,A,B> PQ) {
    return tsdbg(pqueue_to_iterable(PQ));
}

template<typename T>
V<T> queue_to_iterable(queue<T> S) { // PASS BY VALUE!
    V<T> working;
    while (!S.empty()) {working.push_back(S.front()); S.pop();}
    // reverse(all(working));
    return working;
}
template <typename T>
string tsdbg(queue<T> S) {
    return tsdbg(queue_to_iterable(S));
}

template<typename T>
V<T> stack_to_iterable(stack<T> S) { // PASS BY VALUE!
    V<T> working;
    while (!S.empty()) {working.push_back(S.top()); S.pop();}
    // reverse(all(working));
    return working;
}
template <typename T>
string tsdbg(stack<T> S) {
    return tsdbg(stack_to_iterable(S));
}

template <typename A, typename B>
string tsdbg(pair<A, B> p) {
    return "(" + tsdbg(p.first) + ", " + tsdbg(p.second) + ")";
}

template<class ...Ts> string tsdbg(const tuple<Ts...>& t) {
    string out = "(";
    apply([&](const Ts& ...args) {((out += tsdbg(args) + ", "), ...);}, t);
    out.pop_back(); out.pop_back(); out.push_back(')'); return out;
}

// template<class T> string tsdbg(const T&& x) {return to_string(x);}


// helpers for debugging complicated objects
template<class T, class S>
string print_details_helper_general(T&& q, S f, ll MAX) {
    string out;
    ll ctr = 0;
    bool trimmed = false;
    for ( auto&& x : q ) {
        if (ctr == MAX) {trimmed = true; break;}
        out.push_back('\t');
        out += tsdbg(ctr) + ":\t" + tsdbg(f(x)) + "\n";
        ++ctr;
    }
    // string prefix = "\tlen " + tsdbg(q.size());
    string prefix = "";
    if (trimmed) {
        // prefix += ", trimmed to " + tsdbg(MAX);
        out.pop_back();
        out = prefix + "\n" + out + "\n\t... (full length " + tsdbg(q.size()) + ")";
        out.push_back('\n');
    } else {
        out = prefix + "\n" + out;
    }
    return out;
}

#define PDH_DEFAULT_MAX 100'000
template<class T>
string print_details_helper(T&& q, ll MAX=PDH_DEFAULT_MAX) {
    return print_details_helper_general(q, [&](auto x) {return x;}, MAX);
}
string print_details_helper(V<bool>&& q, ll MAX=PDH_DEFAULT_MAX) {
    return print_details_helper_general(q, [&](auto x) {return static_cast<bool>(x);}, MAX);
}
template<class T>
string print_details_helper(priority_queue<T>&& PQ, ll MAX=PDH_DEFAULT_MAX) {
    return print_details_helper(pqueue_to_iterable(PQ), MAX);
}
#define pdh print_details_helper

template<class T, class S>
string print_details_helper_func(T&& q, S f, ll MAX=PDH_DEFAULT_MAX) {
    return print_details_helper_general(q, f, MAX);
}
template<class S>
string print_details_helper_func(V<bool>&& q, S f, ll MAX=PDH_DEFAULT_MAX) {
    return print_details_helper_general(q, [&](auto x) {return f(static_cast<bool>(x));}, MAX);
}
template<class T, class S>
string print_details_helper_func(priority_queue<T>&& PQ, S f, ll MAX=PDH_DEFAULT_MAX) {
    return print_details_helper_general(pqueue_to_iterable(PQ), f, MAX);
}
#define pdh_func print_details_helper_func
#define pdhf print_details_helper_func



template<class T>
string print_tsv_helper(T&& q) {
    string out = "\n";
    for ( auto&& x : q ) {
        bool first = true;
        for ( auto& v : x ) {
            if ( !first ) {
                out += '\t';
            }
            out += tsdbg(v);
            first = false;
        }
        out += '\n';
    }
    return out;
}
#define pth print_tsv_helper


void debug_out() {}

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    // mostly no difference unless there's a background color.
    // std::cerr << tsdbg(H) << "   ";
    // debug_out(T...);
    std::cerr << ' ' << tsdbg(H) << ' ';
    if (sizeof...(T)) {
        std::cerr << " ";
        debug_out(T...);
    }
}

// #define BOLD_MAYBE ""    // NOT bold
#define BOLD_MAYBE     ";1"  // YES bold

#define OUT_RESET       "\033[0m"
#define OUT_BOLD        "\033[;1m"
#define OUT_RED         "\033[31" "m"
#define OUT_CYAN        "\033[36" BOLD_MAYBE "m"
#define OUT_DEFAULT OUT_CYAN
// #define OUT_GREEN       "\033[32" << BOLD_MAYBE << "m"
#define OUT_GREEN       "\033[32" "m"
#define OUT_BLUE        "\033[34" BOLD_MAYBE "m"
#define OUT_WHITE       "\033[97" "m"
#define OUT_MARK        "\033[0;30;41;1m"
#define OUT_YELLOW      "\033[33" BOLD_MAYBE "m"
#define OUT_PURPLE      "\033[35" BOLD_MAYBE "m"


#define dbgc(...) ;
#define dbg(...) ;
#define el ;
#define dbgBold(...) ;
#define dbgcBold(...) ;
#define dbgY(...) ;
#define dbgcY(...) ;
#define dbgP(...) ;
#define dbgcP(...) ;
#define dbgR(...) ;
#define dbgcR(...) ;
#define dbgB(...) ;
#define dbgcB(...) ;
#define dbgW(...) ;
#define dbgcW(...) ;
#define dbgGeneral(...) ;
#define dbgcGeneral(...) ;
#define dbg_only(...) ;
#define local_run (false)
#ifdef DCCLYDE_LOCAL
    // dbgc = "debug with comment"
    #define dbgcbase(A, B, C, ARGTEXT, ...) std::cout << std::flush; \
        std::cerr << OUT_BOLD << B \
        << std::right << setw(20) << C << ' ' \
        << OUT_RESET << OUT_BOLD << OUT_RED \
        << std::right << setw(7) << __LINE__        \
        << OUT_BOLD << " : " << OUT_RESET \
        << A << "[ " << ARGTEXT << " ]" \
        << OUT_BOLD << " :   " << OUT_RESET \
        << B, debug_out(__VA_ARGS__); \
        std::cerr << OUT_RESET << std::endl;

    #undef dbgBold
    #define dbgBold(...) dbgcbase(OUT_GREEN, OUT_MARK, "", #__VA_ARGS__, __VA_ARGS__)
    #undef dbgcBold
    #define dbgcBold(MSG, ...) dbgcbase(OUT_GREEN, OUT_MARK, MSG, #__VA_ARGS__, __VA_ARGS__)

    #undef dbg
    #define dbg(...) dbgcbase(OUT_GREEN, OUT_CYAN, "", #__VA_ARGS__, __VA_ARGS__)
    #undef dbgc
    #define dbgc(MSG, ...) dbgcbase(OUT_GREEN, OUT_CYAN, MSG, #__VA_ARGS__, __VA_ARGS__)

    #undef dbgY
    #define dbgY(...) dbgcbase(OUT_GREEN, OUT_YELLOW, "", #__VA_ARGS__, __VA_ARGS__)
    #undef dbgcY
    #define dbgcY(MSG, ...) dbgcbase(OUT_GREEN, OUT_YELLOW, MSG, #__VA_ARGS__, __VA_ARGS__)

    #undef dbgP
    #define dbgP(...) dbgcbase(OUT_GREEN, OUT_PURPLE, "", #__VA_ARGS__, __VA_ARGS__)
    #undef dbgcP
    #define dbgcP(MSG, ...) dbgcbase(OUT_GREEN, OUT_PURPLE, MSG, #__VA_ARGS__, __VA_ARGS__)

    #undef dbgR
    #define dbgR(...) dbgcbase(OUT_GREEN, OUT_RED, "", #__VA_ARGS__, __VA_ARGS__)
    #undef dbgcR
    #define dbgcR(MSG, ...) dbgcbase(OUT_GREEN, OUT_RED, MSG, #__VA_ARGS__, __VA_ARGS__)

    #undef dbgB
    #define dbgB(...) dbgcbase(OUT_GREEN, OUT_BLUE, "", #__VA_ARGS__, __VA_ARGS__)
    #undef dbgcB
    #define dbgcB(MSG, ...) dbgcbase(OUT_GREEN, OUT_BLUE, MSG, #__VA_ARGS__, __VA_ARGS__)

    #undef dbgW
    #define dbgW(...) dbgcbase(OUT_GREEN, OUT_WHITE, "", #__VA_ARGS__, __VA_ARGS__)
    #undef dbgcW
    #define dbgcW(MSG, ...) dbgcbase(OUT_GREEN, OUT_WHITE, MSG, #__VA_ARGS__, __VA_ARGS__)

    #undef dbgGeneral
    #define dbgGeneral(COLOR, ...) dbgcbase(OUT_GREEN, COLOR, "", #__VA_ARGS__, __VA_ARGS__)
    #undef dbgcGeneral
    #define dbgcGeneral(COLOR, MSG, ...) dbgcbase(OUT_GREEN, COLOR, MSG, #__VA_ARGS__, __VA_ARGS__)

    #undef dbg_only
    #define dbg_only(...) __VA_ARGS__;

    #undef el
    #define el std::cerr << std::flush; std::cerr << '\n';  // in my head I say "error line"

    #undef local_run
    #define local_run (true)
#endif
#pragma endregion

#define timebomb(a) dbg_only({static int _bomb = 0; if(++_bomb>=a) {dbgcBold("boom!", a);exit(1);}});

#define YES ps("YES");
#define NO ps("NO");
#define YESNO(x) ps((x) ? ("YES") : ("NO"));
#define Yes ps("Yes");
#define No ps("No");
#define YesNo(x) ps((x) ? ("Yes") : ("No"));
#define IMPOSSIBLE ps("IMPOSSIBLE");
#define Impossible ps("Impossible");
#define POSSIBLE ps("POSSIBLE");
#define Possible ps("Possible");



const ll INF_ll = 2'000'000'000'000'000'001;  // 2e18 + 1
const int INF_i = 2'000'000'001;  // 2e9 + 1

#pragma endregion

// ! ---------------------------------------------------------------------------

/**
 * Description: Persistent min segtree with lazy updates, no propagation.
 	* If making \texttt{d} a vector then save the results of
 	* \texttt{upd} and \texttt{build} in local variables first to
 	* avoid issues when vector resizes in C++14 or lower.
 * Memory: O(N+Q\log N)
 * Source: CF, Franklyn Wang
 * Verification:
 	* https://codeforces.com/contest/1090/problem/G
 	* https://codeforces.com/gym/102423/submission/70170291

	PSEG_NODES_ALLOCATED sizing:
		(int, 1.25e7) made my code use 220mb here: https://codeforces.com/contest/1771/submission/202989566
		(int, 5e6 barely worked on that problem. 4e6 is too small though.)
 */

// template<class T, class S, int SZ> struct PersistentSegTree;
// template<class T, class S, int SZ>
// string tsdbg(PersistentSegTree<T, S, SZ> st, int time);


// ! Remember to update LIM, SZ. Watch out for overflow!
const int PSEG_NODES_ALLOCATED = 1.25e7;  // ~ TODO tune using custom invocation
const int PSEG_POSITIONS = (1<<17);  // ~ 2^18 = 262144. TODO update using problem constraints

template<class T, class S, int SZ> struct PersistentSegTree {
	static const int LIM = PSEG_NODES_ALLOCATED;
	static const int sz = PSEG_POSITIONS;
    static const T idT = INF_i;  // ! IDseg
    static const S idS = -INF_i;  // ! IDlazy
	int orig_n = -1;
    static T lazy_seg(S lazy, T seg) { return (lazy==idS) ? seg : lazy; }  // ! lazy * seg
	struct node {
		int l, r; T val = idT, lazy = idS;
		void inc(S x) { if (lazy != idS) lazy = x; }  // ! lazy * lazy
		T get() { return lazy_seg(lazy, val); }
	};
	node d[LIM]; int nex = 0;
	int copy(int c) { d[nex] = d[c]; return nex++; }
	T cmb(T a, T b) { return min(a,b); }  // ! seg * seg
	void pull(int c) { d[c].val =
		cmb(d[d[c].l].get(), d[d[c].r].get()); }
	//// MAIN FUNCTIONS
	T query(int c, int lo, int hi, int L, int R) {
		if (lo <= L && R <= hi) return d[c].get();
		if (R < lo || hi < L) return idT;
		int M = (L+R)/2;
		return lazy_seg(d[c].lazy, cmb(query(d[c].l,lo,hi,L,M),
							query(d[c].r,lo,hi,M+1,R)));
	}
	int upd(int c, int lo, int hi, S v, int L, int R) {
		if (R < lo || hi < L) return c;
		int x = copy(c);
		if (lo <= L && R <= hi) { d[x].inc(v); return x; }
		int M = (L+R)/2;
		d[x].l = upd(d[x].l,lo,hi,v,L,M);
		d[x].r = upd(d[x].r,lo,hi,v,M+1,R);
		pull(x); return x;
	}
	int build(const auto& arr, int L, int R) {
		int c = nex++;
		if (L == R) {
			if (L < sz(arr)) d[c].val = arr[L];
			return c;
		}
		int M = (L+R)/2;
		d[c].l = build(arr,L,M), d[c].r = build(arr,M+1,R);
		pull(c); return c;
	}

    #pragma region  // lstTrue_from_base. TODO add fstTrue_from_base.
    // ~ lstTrue_from_base(L, check(v,r)) == lstTrue(L, orig_n-1, check(query(L,r), r)).
    int lstTrue_from_base(int L, int time, auto&& check) {
        assert(pct(SZ) == 1);  // SZ should be a power of 2.
        int n = SZ;
        int c = time;
        int l = 0; int r = n-1;
        auto m = [&]() -> int {return (l+r)>>1;};

        dbgcBold("lsR", L, MT(l,r), MP(*this, c));
        // Special case: Check if the whole array is valid.
        pull(c);
        V<int> path;  // path holds all ancestors of c.
        if (L == 0 && check(d[c].get(), r)) {return orig_n-1;}

        auto move_DL = [&]() -> void { path.push_back(c); c = d[c].l; pull(c); r=m(); };
        auto move_DR = [&]() -> void { path.push_back(c); c = d[c].r; pull(c); l=m()+1; };
        auto move_U = [&]() -> void {
            int len = r-l+1;
            if (d[path.back()].l == c) { r += len; }
            else { l -= len; }
            c = path.back(); path.pop_back(); pull(c);
        };
        auto move_R = [&]() -> void {
            int steps = 0;
            while (d[path.back()].r == c) { move_U(); ++steps; }
            c = d[path.back()].r; pull(c); int len=(r-l+1); l+=len; r+=len;
            rep(steps) { move_DL(); }
        };

        while (l != L) {
            dbgc("stage 1", l,r, L, path);
            path.push_back(c);
            if (L <= m()) {move_DL();}
            else {move_DR();}
            pull(c);
        }

        T wip = idT;
        while (true) {
            T fut = cmb(wip, d[c].get());
            dbgcP("stage 2", l,r, "", fut, path);
            if (check(fut,r)) {  // If we can safely add this chunk...
                wip = fut;
                if (r == n-1) {
                    // We've reached the end.
                    return orig_n-1;
                } else if (d[path.back()].r == c) {
                    // This was a right child.
                    move_U(); move_R();
                } else {
                    // This was a left child.
                    move_R();
                }
            } else { break; }
        }

        // (l,r) would reach too far.
        while (l != r) {
            // does DL reach too far?
            pull(d[c].l);
            T fut = cmb(wip, d[d[c].l].get());
            if (check(fut,m())) {wip = fut; move_DR();}
            else {move_DL();}
        }
        int out = l-1;
        ckmin(out, orig_n-1);
        dbgR(out); el;
        return out;
    }
    #pragma endregion  // lstTrue_from_base


	vi loc; //// PUBLIC
	void upd(int lo, int hi, S v) {
		loc.pb(upd(loc.bk,lo,hi,v,0,SZ-1)); }
	T query(int ti, int lo, int hi) {
		return query(loc[ti],lo,hi,0,SZ-1); }

    void clear() { FOR(c, 0, nex) {d[c] = {};} nex = 0; orig_n = -1; loc.clear(); }
	void init(int n_) { assert(n_ <= SZ); clear(); orig_n = n_; build(V<T>(n_)); }
	void build(const auto& arr) {orig_n = arr.size(); assert(orig_n <= SZ); loc.pb(build(arr,0,SZ-1));}
};

template<class T, class S, int SZ>
string tsdbg(pair<PersistentSegTree<T, S, SZ>, int> pst_and_node) {
    auto& [st, c] = pst_and_node;
	assert(st.orig_n != -1);
	V<T> out;
	FOR(k, 0, st.orig_n) { out.pb(st.query(c, k, k)); dbgB(out);}
    return tsdbg(out);
}


PersistentSegTree<int, int, PSEG_POSITIONS> pst;

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


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
	const T ID{INF_ll};  // ! identity
    T cmb(T a, T b) { return min(a,b); }  // ! seg * seg
	int n; V<T> seg; int orig_n;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2;
		seg.assign(2*n,ID); orig_n = _n;}
	void pull(int p) { seg[p] = cmb(seg[2*p],seg[2*p+1]); }
    void build() { ROF(i,1,n) pull(i); }
	void upd(int p, T val) { // set val at position p
		seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    void inc(int p, T val) { upd(p, cmb(val, seg[n+p])); }
	T query(int l, int r) {	// associative op on [l, r]
        if (l > r) {return ID;}
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = cmb(ra,seg[l++]);
			if (r&1) rb = cmb(seg[--r],rb);
		}
		return cmb(ra,rb);
	}

    #pragma region  // lstTrue_from_base, fstTrue_from_base
    // ~ lstTrue_from_base(L, check(v,r)) == lstTrue(L, orig_n-1, check(query(L,r), r)).
    int lstTrue_from_base(int L, auto&& check) {
        int ind = 1; int l = 0; int r = n-1;
        // dbgcBold("lsR", L, MT(ind,l,r), *this);
        // push(ind,l,r);  // ~ leave these commented for analogy to LazySeg.
        if (L == 0 && check(seg[ind], r)) {return orig_n-1;}

        while (l != L) {
            // dbgc("stage 1", ind,l,r, L);
            int m = (l+r)/2;
            if (L <= m) {ind = 2*ind; r = m;}
            else {ind = 2*ind+1; l = m+1;}
            // push(ind,l,r);
        }

        T wip = ID;
        while (true) {
            T fut = cmb(wip, seg[ind]);
            // dbgcP("stage 2", ind,l,r, "", fut);
            if (check(fut,r)) {  // If we can safely add this chunk...
                wip = fut;
                if (r == n-1) {
                    // We've reached the end.
                    return orig_n-1;
                } else if (ind & 1) {
                    // This was a right child.
                    ind = ind/2 + 1;
                    int len = r-l+1;
                    l += len; r += 2*len;
                } else {
                    // This was a left child.
                    ++ind;
                    int len = r-l+1;
                    l += len; r += len;
                }
                // push(ind,l,r);
            } else { break; }
        }

        // (ind,l,r) would reach too far.
        while (l != r) {
            // does DL reach too far?
            int m = (l+r)/2;
            // push(2*ind, l, m);
            T fut = cmb(wip, seg[2*ind]);
            // dbgcW("stage 3", ind,l,r, "", m, fut);
            if (check(fut,m)) {
                wip = fut;
                ind = 2*ind+1;
                l = m+1;
                // push(ind,l,r);
            } else {
                ind = 2*ind; r = m;
            }
        }
        int out = l-1;
        ckmin(out, orig_n-1);
        // dbgR(out); el;
        return out;
    }

    // fstTrue_from_base(R, check(v,l)) == fstTrue(0, R, check(query(l,R), l)).
    int fstTrue_from_base(int R, auto&& check) {
        int ind = 1; int l = 0; int r = n-1;
        // dbgcBold("fsb", R, MT(ind,l,r), *this);
        // push(ind,l,r);  // ~ leave these commented for analogy to LazySeg.
        if (R == orig_n-1 && check(seg[ind], 0)) {return 0;}

        while (r != R) {
            // dbgc("stage 1", ind,l,r, R);
            int m = (l+r)/2;
            if (R <= m) {ind = 2*ind; r = m;}
            else {ind = 2*ind+1; l = m+1;}
            // push(ind,l,r);
        }

        T wip = ID;
        while (true) {
            T fut = cmb(wip, seg[ind]);
            // dbgcP("stage 2", ind,l,r, "", fut);
            if (check(fut,l)) {  // If we can safely add this chunk...
                wip = fut;
                if (l == 0) {
                    // We've reached the end.
                    return 0;
                } else if (ind & 1) {
                    // This was a right child.
                    --ind;
                    int len = r-l+1;
                    l -= len; r -= len;
                } else {
                    // This was a left child.
                    ind = ind/2 - 1;
                    int len = r-l+1;
                    l -= 2*len; r -= len;
                }
                // push(ind,l,r);
            } else { break; }
        }

        // (ind,l,r) would reach too far.
        while (l != r) {
            // does DR reach too far?
            int m = (l+r)/2;
            // push(2*ind+1, m+1, r);
            T fut = cmb(wip, seg[2*ind+1]);
            // dbgcW("stage 3", ind,l,r, "", m, fut);
            if (check(fut,m+1)) {
                wip = fut; ind *= 2; r = m;
                // push(ind,l,r);
            } else {
                ind = 2*ind+1; l = m+1;
            }
        }
        int out = r+1;
        return out;
    }
    #pragma endregion  // lstTrue_from_base, fstTrue_from_base
    void detailed_printouts() {
        #pragma region
        dbg_only(
        int ST_SIZE = n;
        int ST_PRINT_SIZE = orig_n;
        // ST_PRINT_SIZE = ST_SIZE;  // toggle whether to print irrelevant suffix
        el;
        dbgc("SegTree DETAILS");
        FOR(k, 1, ST_SIZE + ST_PRINT_SIZE) {
            if ( k >= ST_SIZE) {
                int p = k - ST_SIZE;
                dbgP(k, p, seg[k]);
            } else {
                vector<int> binary_digits;
                int temp = k;
                while ( temp > 0 ) {
                    binary_digits.push_back( temp % 2 );
                    temp /= 2;
                }
                reverse(all(binary_digits));
                int L = 0; int R = ST_SIZE-1;
                for ( int didx = 1 ; didx < binary_digits.size() ; ++didx ) {
                    int M = (L+R) / 2;
                    if ( binary_digits[didx] == 1 ) {
                        L = M+1;
                    } else {
                        R = M;
                    }
                }
                if ( L < ST_PRINT_SIZE ) {
                    dbgY(k, MP(L,R), seg[k]);
                }
            }
        }
        el;
        );  // end dbg_only
        #pragma endregion
    }
};
template<class T>
string tsdbg(SegTree<T> st) {
    vector<T> out;
    FOR(k, st.n, st.n + st.orig_n) { out.push_back( st.seg[k] ); }
    return tsdbg(out);
}

#pragma region  // LazySeg
/**
 * Description: 1D range increment and sum query.
 * Source: USACO Counting Haybales
 * Verification: SPOJ Horrible
 */

tcT, class S> struct LazySeg {
	const T idT{INF_ll}; const S idS{-INF_ll};  // ! identity
	int n; V<T> seg; V<S> lazy; int orig_n; int SZ;
	T cmb(T a, T b) {  // ! seg * seg
		return min(a,b);
	}
	void init(int _n) {
		orig_n = _n; for (n = 1; n < _n; ) n *= 2;
		SZ = n; seg.assign(2*n,idT); lazy.assign(2*n, idS);  // ! initialize
	}
	void push(int ind, int L, int R) { /// modify values for current node
        if (lazy[ind] == idS) return;
        seg[ind] = lazy[ind];  // ! lazy * seg
		if (L != R) F0R(i,2) lazy[2*ind+i] = lazy[ind]; // ! lazy * lazy
		lazy[ind] = idS;
	} // recalc values for current node
	void pull(int ind){seg[ind]=cmb(seg[2*ind],seg[2*ind+1]);}
	void build() { ROF(i,1,SZ) pull(i); }
    void push_all(int ind=1, int L=0, int R=-1) {
        if ( R == -1 ) {R = SZ-1;} push(ind, L, R);
        if (L < R) {int M = (L+R)/2; push_all(2*ind, L, M); push_all(2*ind+1, M+1, R);}
    }
	void upd(int lo,int hi,S inc,int ind=1,int L=0, int R=-1) {
        // dbgcBold("upd", MP(lo,hi), inc);
        if ( R == -1 ) {R = SZ-1;}
		push(ind,L,R); if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) {
            // dbgW(lo,hi,inc,"",MT(ind,L,R));
			lazy[ind] = inc;
            // detailed_printouts();
            push(ind,L,R);
            // detailed_printouts();
            // assert(false);
            return; }
		int M = (L+R)/2; upd(lo,hi,inc,2*ind,L,M);
		upd(lo,hi,inc,2*ind+1,M+1,R); pull(ind);
	}
	T query(int lo, int hi, int ind=1, int L=0, int R=-1) {
        if ( R == -1 ) {R = SZ-1;}
		push(ind,L,R); if (lo > R || L > hi) return idT;
		if (lo <= L && R <= hi) return seg[ind];
		int M = (L+R)/2; return cmb(query(lo,hi,2*ind,L,M),
			query(lo,hi,2*ind+1,M+1,R));
	}
    #pragma region  // lstTrue_from_base, fstTrue_from_base
    // ~ lstTrue_from_base(L, check(v,r)) == lstTrue(L, orig_n-1, check(query(L,r), r)).
    int lstTrue_from_base(int L, auto&& check) {
        int ind = 1; int l = 0; int r = n-1;
        // dbgcBold("lsR", L, MT(ind,l,r), *this);
        push(ind,l,r);
        if (L == 0 && check(seg[ind], r)) {return orig_n-1;}

        while (l != L) {
            // dbgc("stage 1", ind,l,r, L);
            int m = (l+r)/2;
            if (L <= m) {ind = 2*ind; r = m;}
            else {ind = 2*ind+1; l = m+1;}
            push(ind,l,r);
        }

        T wip = idT;
        while (true) {
            T fut = cmb(wip, seg[ind]);
            // dbgcP("stage 2", ind,l,r, "", fut);
            if (check(fut,r)) {  // If we can safely add this chunk...
                wip = fut;
                if (r == n-1) {
                    // We've reached the end.
                    return orig_n-1;
                } else if (ind & 1) {
                    // This was a right child.
                    ind = ind/2 + 1;
                    int len = r-l+1;
                    l += len; r += 2*len;
                } else {
                    // This was a left child.
                    ++ind;
                    int len = r-l+1;
                    l += len; r += len;
                }
                push(ind,l,r);
            } else { break; }
        }

        // (ind,l,r) would reach too far.
        while (l != r) {
            // does DL reach too far?
            int m = (l+r)/2;
            push(2*ind, l, m);
            T fut = cmb(wip, seg[2*ind]);
            // dbgcW("stage 3", ind,l,r, "", m, fut);
            if (check(fut,m)) {
                wip = fut;
                ind = 2*ind+1;
                l = m+1;
                push(ind,l,r);
            } else {
                ind = 2*ind; r = m;
            }
        }
        int out = l-1;
        ckmin(out, orig_n-1);
        // dbgR(out); el;
        return out;
    }

    // fstTrue_from_base(R, check(v,l)) == fstTrue(0, R, check(query(l,R), l)).
    int fstTrue_from_base(int R, auto&& check) {
        int ind = 1; int l = 0; int r = n-1;
        // dbgcBold("fsb", R, MT(ind,l,r), *this);
        push(ind,l,r);  // ~ leave these commented for analogy to LazySeg.
        if (R == orig_n-1 && check(seg[ind], 0)) {return 0;}

        while (r != R) {
            // dbgc("stage 1", ind,l,r, R);
            int m = (l+r)/2;
            if (R <= m) {ind = 2*ind; r = m;}
            else {ind = 2*ind+1; l = m+1;}
            push(ind,l,r);
        }

        T wip = idT;
        while (true) {
            T fut = cmb(wip, seg[ind]);
            // dbgcP("stage 2", ind,l,r, "", fut);
            if (check(fut,l)) {  // If we can safely add this chunk...
                wip = fut;
                if (l == 0) {
                    // We've reached the end.
                    return 0;
                } else if (ind & 1) {
                    // This was a right child.
                    --ind;
                    int len = r-l+1;
                    l -= len; r -= len;
                } else {
                    // This was a left child.
                    ind = ind/2 - 1;
                    int len = r-l+1;
                    l -= 2*len; r -= len;
                }
                push(ind,l,r);
            } else { break; }
        }

        // (ind,l,r) would reach too far.
        while (l != r) {
            // does DR reach too far?
            int m = (l+r)/2;
            push(2*ind+1, m+1, r);
            T fut = cmb(wip, seg[2*ind+1]);
            // dbgcW("stage 3", ind,l,r, "", m, fut);
            if (check(fut,m+1)) {
                wip = fut; ind *= 2; r = m;
                push(ind,l,r);
            } else {
                ind = 2*ind+1; l = m+1;
            }
        }
        int out = r+1;
        return out;
    }
    #pragma endregion  // lstTrue_from_base, fstTrue_from_base
    void detailed_printouts() {
        #pragma region
        dbg_only(
        int ST_SIZE = n;
        int ST_PRINT_SIZE = orig_n;
        // ST_PRINT_SIZE = ST_SIZE;  // toggle whether to print irrelevant suffix
        el;
        dbgc("LazySeg DETAILS");
        FOR(k, 1, ST_SIZE + ST_PRINT_SIZE) {
            if ( k >= ST_SIZE) {
                int p = k - ST_SIZE;
                dbgP(k, p, seg[k], lazy[k]);
            } else {
                vector<int> binary_digits;
                int temp = k;
                while ( temp > 0 ) {
                    binary_digits.push_back( temp % 2 );
                    temp /= 2;
                }
                reverse(all(binary_digits));
                int L = 0; int R = ST_SIZE-1;
                FOR(didx, 1, binary_digits.size()) {
                    int M = (L+R) / 2;
                    if ( binary_digits[didx] == 1 ) {
                        L = M+1;
                    } else {
                        R = M;
                    }
                }
                if ( L < ST_PRINT_SIZE ) {
                    dbgY(k, MP(L,R), seg[k], lazy[k]);
                }
            }
        }
        el;
        );  // end dbg_only
        #pragma endregion
    }
};

template<class T, class S>
string tsdbg(LazySeg<T, S> st) {
    st.push_all(); vector<T> out;
    FOR(k, st.n, st.n + st.orig_n) { out.push_back(st.seg[k]); }
    return tsdbg(out);
}
#pragma endregion  // LazySeg


void solve() {
    cout << "AWEW" << endl;
    lls(N, E);
    V<pll> edges;
    rv1(E, edges);
    dbgR(N, E, edges);
    el;

    V<ll> wip(N, N);
    for(auto& [a, b] : edges) {
        if (a > b) {swap(a, b);}
        ckmin(wip[a], b);
    }
    cerr << flush; cout << flush;
    return;
    pst.build(wip);
    dbg(pst.orig_n, pst.loc);
    FOR(k, 0, N) {
        ll v = pst.query(pst.loc.back(), k, k);
        dbgP(k, v);
    }

    dbgY(MP(pst,pst.loc.back())); el;

    // SegTree<ll> st;
    LazySeg<ll,ll> st;
    st.init(N);
    st.seg.assign(2*st.n, N);
    for(auto& [a, b] : edges) {
        if (a > b) {swap(a, b);}
        ckmin(st.seg[st.n+a], b);
    }
    st.build();
    dbgY(st); el;

    LazySeg<ll,ll> stBackward;
    stBackward.init(N);
    FOR(k, 0, N) { stBackward.upd(k, k, st.query(N-1-k, N-1-k)); dbg(stBackward);}
    dbgB(stBackward); el;



    ll out = 0;
    FOR(L, 0, N) {
        // ll Rold = lstTrue(L, N-1, [&](ll r) {
        //     return st.query(L, r) > r;
        // });

        // Find first r such that query(L, r) <= r.
        // I think this can be coded similar to a crappy query() that handles all left stuff first?
        // auto fsR = [&]() -> ll {
        //     ll l = 0; ll r = st.n - 1; ll ind = 1;
        //     while (l < r) {
        //         ll m = (l+r)/2;

        //     }
        // };


        // ll R = st.first_satisfying_R(L);

        ll R_persistent = pst.lstTrue_from_base(L, pst.loc.back(), [&](ll v, ll r) -> bool {
            return v > r;
        });

        ll R = st.lstTrue_from_base(L, [&](ll v, ll r) -> bool {
            return v > r;
        });
        dbgB(L, MP(R, R_persistent));
        assert(R == R_persistent);
        ll len = R-L+1;
        ll R_backward = stBackward.fstTrue_from_base(N-1-L, [&](ll v, ll l) -> bool {
            ll reflect = N-1-l;
            dbgcR("check bkwd", v, l, reflect, (v>reflect));
            return v > reflect;
        });
        ll len_backward = N-1-L - R_backward + 1;
        dbg(N-1-L, R_backward, len_backward);
        dbg_only(
            ll Rold = lstTrue(L, N-1, [&](ll r) {
                return st.query(L, r) > r;
            });
            dbgY(Rold, R, R_backward, MP(len, len_backward));
            assert(Rold == R);
            assert(len_backward == len);
        );
        assert(len_backward == len);

        // if (R == -1) {continue;}
        // --R;
        // out += len;
        out += len_backward;
        dbgB(L, R, len, out); el; el; el;
    }

    return ps(out);
}

// ! Do something instead of nothing: write out small cases, code bruteforce
// ! Check bounds even if I have a solution - are they letting through simpler versions?
// ! If stuck on a "should be easy" problem for 10 mins, reread statement, check bounds

#define PROBLEM_STYLE CF
// #define SINGLE_CASE  // ! Uncomment this for one-case problems.
#pragma region  // main
#if PROBLEM_STYLE == CF || PROBLEM_STYLE == GCJ
int main() {
    setIO();

    int T = 1;
    #ifndef SINGLE_CASE
        dbgc("loading num cases!!!"); std::cin >> T;
    #endif
    for ( int CASE = 1 ; CASE <= T ; ++CASE ) {
        #if PROBLEM_STYLE == GCJ
            cout << "Case #" << CASE << ": ";
        #endif
        el;
        #ifndef DCCLYDE_BRUTEFORCE
            dbgcBold("CASE" , CASE );
            solve();
        #else
            dbgcBold("brute force" , CASE );
            brute();
        #endif
    }
    dbgR(TIME());
    return 0;
}
#else
// PROBLEM_STYLE is CLEAN or undefined.
int main() {
    #ifdef _OPENMP
        ll num_procs = omp_get_num_procs();
        ll max_threads = omp_get_max_threads();
        dbgBold(num_procs, max_threads);
        omp_set_num_threads(num_procs - 4);
    #endif
    setIO();

    solve();

    dbgR(TIME());
    return 0;
}
#endif
#pragma endregion
