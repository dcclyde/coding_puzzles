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

#define GET_MACRO_5(_1,_2,_3,_4,_5,NAME,...) NAME
#define FOR(...) GET_MACRO_5(__VA_ARGS__, , FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)

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
// * debug setup adapted from from tourist. https://codeforces.com/contest/1540/submission/120602670
// * dcclyde added line numbers, colors, and some other stuff.

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
#define OUT_GREEN       "\033[32" "m"
// #define OUT_GREEN       "\033[32" << BOLD_MAYBE << "m"
#define OUT_YELLOW      "\033[33" BOLD_MAYBE "m"
#define OUT_BLUE        "\033[34" BOLD_MAYBE "m"
#define OUT_PURPLE      "\033[35" BOLD_MAYBE "m"
#define OUT_CYAN        "\033[36" BOLD_MAYBE "m"
#define OUT_BRIGHTBLUE  "\033[38;5;39m"
#define OUT_WHITE       "\033[97" "m"
#define OUT_MARK        "\033[0;30;41;1m"
#define OUT_LTBLUE      "\033[96m"

#define OUT_DEFAULT OUT_CYAN
#define OUT_INPUTCOLOR OUT_WHITE


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
#define dbgInput(...) ;
#define dbgcInput(...) ;
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

    #undef dbgInput
    #define dbgInput(...) dbgcbase(OUT_GREEN, OUT_INPUTCOLOR, "", #__VA_ARGS__, __VA_ARGS__)
    #undef dbgcInput
    #define dbgcInput(MSG, ...) dbgcbase(OUT_GREEN, OUT_INPUTCOLOR, MSG, #__VA_ARGS__, __VA_ARGS__)

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
    #define readBase(TYPE, ...) TYPE __VA_ARGS__; re(__VA_ARGS__); dbgInput(__VA_ARGS__);
    #define readBase1(TYPE, ...) TYPE __VA_ARGS__; re(__VA_ARGS__); decrement(__VA_ARGS__); dbgInput(__VA_ARGS__);
    #define ints(...) readBase(int, __VA_ARGS__);
    #define int1(...) readBase1(int, __VA_ARGS__);
    #define chars(...) readBase(char, __VA_ARGS__);
    #define char1(...) readBase1(char, __VA_ARGS__);
    #define lls(...) readBase(ll, __VA_ARGS__);
    #define ll1(...) readBase1(ll, __VA_ARGS__);
    #define strings(...) readBase(string, __VA_ARGS__);

    #define vecs_1(TYPE, SIZE, A) V<TYPE> A; rv(SIZE, A); dbgInput(SIZE, A);
    #define vecs_2(TYPE, SIZE, A, B) vecs_1(TYPE, SIZE, A); vecs_1(TYPE, SIZE, B);
    #define vecs_3(TYPE, SIZE, A, B, C) vecs_1(TYPE, SIZE, A); vecs_2(TYPE, SIZE, B, C);
    #define vecs_4(TYPE, SIZE, A, B, C, D) vecs_1(TYPE, SIZE, A); vecs_3(TYPE, SIZE, B, C, D);
    #define vecs_5(TYPE, SIZE, A, B, C, D, E) vecs_1(TYPE, SIZE, A); vecs_4(TYPE, SIZE, B, C, D, E);
    #define vec1_1(TYPE, SIZE, A) V<TYPE> A; rv1(SIZE, A); dbgInput(SIZE, A);
    #define vec1_2(TYPE, SIZE, A, B) vec1_1(TYPE, SIZE, A); vec1_1(TYPE, SIZE, B);
    #define vec1_3(TYPE, SIZE, A, B, C) vec1_1(TYPE, SIZE, A); vec1_2(TYPE, SIZE, B, C);
    #define vec1_4(TYPE, SIZE, A, B, C, D) vec1_1(TYPE, SIZE, A); vec1_3(TYPE, SIZE, B, C, D);
    #define vec1_5(TYPE, SIZE, A, B, C, D, E) vec1_1(TYPE, SIZE, A); vec1_4(TYPE, SIZE, B, C, D, E);

    #define vecs(TYPE, SIZE, ...) GET_MACRO_5(__VA_ARGS__, vecs_5, vecs_4, vecs_3, vecs_2, vecs_1)(TYPE, SIZE, __VA_ARGS__);
    #define vec1(TYPE, SIZE, ...) GET_MACRO_5(__VA_ARGS__, vec1_5, vec1_4, vec1_3, vec1_2, vec1_1)(TYPE, SIZE, __VA_ARGS__);

    // #define vecs(TYPE, SIZE, ...) V<TYPE> __VA_ARGS__; rv(SIZE, __VA_ARGS__); dbgInput(__VA_ARGS__);
    // #define vec1(TYPE, SIZE, ...) V<TYPE> __VA_ARGS__; rv1(SIZE, __VA_ARGS__); dbgInput(__VA_ARGS__);
}

#define timebomb(a) dbg_only({static int _bomb=a;if(_bomb<=0) {dbgcBold("boom!", a);assert(false);exit(1);} dbgcR("timebomb", _bomb); --_bomb;});

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




void brute() {
    lls(N);
    el;

    V<ll> ph;
    FOR(k, 0, N) {ph.push_back(k+1);}
    ll out = 0;
    auto best_permutation = ph;
    do {
        V<ll> scores;
        FOR(i, 0, N) { scores.push_back((i+1) * ph[i]); } sort(all(scores));
        scores.pop_back();
        ll total = sumv(scores);
        if (ckmax(out, total)) {
            best_permutation = ph;
        }
    } while (next_permutation(all(ph)));
    dbgY(best_permutation);
    return ps(out);
}

void solve_v1() {
    lls(N);
    el;

    ll out = 0;
    FOR(a, 1, N+1) {
        FOR(b, a+1, N+1) {
            // what's my score and biggest element if (a, b) is the dead pair?
            ll score = 0;
            ll big = 0;
            ll cap = a * b;
            ll x = 1; ll y = 1;
            FOR(j, 0, N-1) {
                if (x == a) {++x;}
                if (y == b) {++y;}
                score += x*y;
                // dbgP(j, MP(x,y), score);
                if (ckmax(big, x*y) && big > cap) {break;}
                ++x; ++y;
            }
            // dbg(MP(a,b), score, big, cap);
            if (big <= cap) { ckmax(out, score); }
        }
    }

    return ps(out);
}

void solve() {
    lls(N);
    el;

    ll out = 0;
    FOR(cutoff, 0, N) {
        V<ll> p;
        FOR(k, 1, cutoff+1) {p.push_back(k);}
        ROF(k, cutoff+1, N+1) {p.push_back(k);}

        V<ll> scores;
        FOR(i, 0, N) { scores.push_back((i+1) * p[i]); } sort(all(scores));
        scores.pop_back();
        ll total = sumv(scores);
        ckmax(out, total);
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
