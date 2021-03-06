#pragma region
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

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
using vll = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpii = V<pi>;
using vpl = V<pl>;
using vpll = V<pll>;
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
#define emp emplace
//// #define ft front()
//// #define bk back()

//// #define lb lower_bound
//// #define ub upper_bound
//// tcT> int lwb(V<T>& a, const T& b) { return int(lb(all(a),b)-bg(a)); }
//// tcT> int upb(V<T>& a, const T& b) { return int(ub(all(a),b)-bg(a)); }


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
    size_t operator()(pair<T,U> x) const {
        uint64_t a = (*this)(x.first);
        uint64_t b = (*this)(x.second);
        return a + 3*b;
    }
};

template<class A, class B> using umap = gp_hash_table<A,B,custom_hash>;
// template<class A, class B> using umap = unordered_map<A,B,custom_hash>;  // slower?
// template<class A, class B> using umap = map<A,B>;  // ok for tiny cases?
// template<class A, class B> using umap = unordered_map<A,B>;  // slower and unsafe?

template<class A> using uset = gp_hash_table<A,null_type,custom_hash>;
// template<class A> using uset = unordered_set<A, custom_hash>;
// template<class A> using uset = set<A>;
// template<class A> using uset = unordered_set<A>;

#define unordered_map DCCLYDE_REMINDER_DONT_USE_UNPROTECTED_HASH_MAP
#define unordered_set DCCLYDE_REMINDER_DONT_USE_UNPROTECTED_HASH_SET


// loops
#define CONCAT_INNER(a, b) a ## b
#define CONCAT(a, b) CONCAT_INNER(a, b)
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define FORll(i,a,b) for (ll i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define ROFll(i,a,b) for (ll i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(CONCAT(_,__LINE__),a)
#define each(a,x) for (auto& a: x)
#define foreach(a,x) each(a,x)

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

//// const int MOD = 1e9+7; // 998244353;  // I can add this myself.
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

// bitwise ops
// also see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set bits_set
constexpr ll pct(ll x) { return __builtin_popcountll(x); }
constexpr int bits(int x) { // assert(x >= 0); // make C++11 compatible until USACO updates ...
    return x == 0 ? 0 : 31-__builtin_clz(x); } // floor(log2(x))
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }

ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down

tcTU> bool ckmin(T& a, const U& b) {
    return (T)b < a ? a = (T)b, 1 : 0; } // set a = min(a,b)
tcTU> bool ckmax(T& a, const U& b) {
    return a < (T)b ? a = (T)b, 1 : 0; } // set a = max(a,b)

int maxi(int a, int b) {return max((int)a, (int)b);}
int mini(int a, int b) {return min((int)a, (int)b);}
ll maxll(ll a, ll b) {return max((ll)a, (ll)b);}
ll minll(ll a, ll b) {return min((ll)a, (ll)b);}

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
tcTU> void erase(T& t, const U& u) { // don't erase
    auto it = t.find(u); assert(it != end(t));
    t.erase(it); } // element that doesn't exist from (multi)set

// use like sumv(all(dat))
template<class ForwardIt>
ll sumv(ForwardIt first, ForwardIt last)
{
    // typename std::iterator_traits<ForwardIt>::value_type out {};  // acc in int can overflow
    ll out = 0;
    for (; first != last; ++first) {
        out += *first;
    }
    return out;
}
template<class T> auto sumv(const T& data) {return sumv(all(data));}
template<class T> auto max_element(const T& data) {return *max_element(all(data));}
template<class T> auto min_element(const T& data) {return *min_element(all(data));}


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
    tcTU> void re(pair<T,U>& p) { re(p.first,p.second); }
    template<class A,class B,class C> void re(tuple<A,B,C>& t) {auto& [a,b,c]=t; re(a,b,c);}
    template<class A,class B,class C, class D> void re(tuple<A,B,C,D>& t) {auto& [a,b,c,d]=t; re(a,b,c,d);}
    template<class A,class B,class C, class D, class E> void re(tuple<A,B,C>& t) {auto& [a,b,c,d,e]=t; re(a,b,c,d,e);}
    template<class A,class B,class C, class D, class E, class F> void re(tuple<A,B,C>& t) {auto& [a,b,c,d,e,f]=t; re(a,b,c,d,e,f);}
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
    void rv1(size_t) {}
    tcTUU> void rv1(size_t N, V<T>& t, U&... u) {
        t.resize(N); re(t); for(auto& x : t) --x;
        rv(N,u...); }


    // dumb shortcuts to read in ints
    void decrement() {} // subtract one from each
    tcTUU> void decrement(T& t, U&... u) { --t; decrement(u...); }
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
    template<class T> void pr_sep(ostream& os, str, const T& t) { os << ts(t); }
    template<class T, class... U> void pr_sep(ostream& os, str sep, const T& t, const U&... u) {
        pr_sep(os,sep,t); os << sep; pr_sep(os,sep,u...); }
    template<class T> void pr_sep1(ostream& os, str, const T& t) { os << ts(t+1); }
    template<class T, class... U> void pr_sep1(ostream& os, str sep, const T& t, const U&... u) {
        pr_sep1(os,sep,t); os << sep; pr_sep1(os,sep,u...); }
    // print w/ no spaces
    template<class ...T> void pr(const T&... t) { pr_sep(cout,"",t...); }
    // print w/ spaces, end with newline
    void ps() { cout << "\n"; }
    template<class ...T> void ps(const T&... t) { pr_sep(cout," ",t...); ps(); }
    void ps1() { cout << "\n"; }
    template<class ...T> void ps1(const T&... t) { pr_sep1(cout," ",t...); ps1(); }
    void pso() {}
    template<class ...T> void pso(const T&... t) { pr_sep(cout," ",t...); pso(); }
    void pso1() {}
    template<class ...T> void pso1(const T&... t) { pr_sep1(cout," ",t...); pso1(); }

    template<class T>
    void pv(T& dat) {bool f=1; for(auto& x : dat) {if (!f) {cout<<' ';} f=0; cout << x;} cout<<'\n';}
    template<class T>
    void pv1(T& dat) {bool f=1; for(auto& x : dat) {if (!f) {cout<<' ';} f=0; cout << x+1;} cout<<'\n';}
    template<class T>
    void pvn(T& dat) {bool f=1; for(auto& x : dat) {if (!f) {cout<<'\n';} f=0; cout << x;} cout<<'\n';}
    template<class T>
    void pvn1(T& dat) {bool f=1; for(auto& x : dat) {if (!f) {cout<<'\n';} f=0; cout << x+1;} cout<<'\n';}
    // * Remove debug code; I'll use the tourist+me amalgamation instead.

    const clock_t beg = clock();
    // #define dbg_time() dbg((db)(clock()-beg)/CLOCKS_PER_SEC)
    db TIME() {return (db)(clock()-beg)/CLOCKS_PER_SEC;}
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

// helpers for debugging complicated objects
template<class T>
string print_details_helper(T& q) {
    string out = "\n";
    int ctr = 0;
    for ( auto& x : q ) {
        out.push_back('\t');
        out += to_string(ctr) + ":\t" + to_string(x) + "\n";
        ++ctr;
    }
    return out;
}
#define pdh print_details_helper

template<class T>
string print_tsv_helper(T& q) {
    string out = "\n";
    for ( auto& x : q ) {
        bool first = true;
        for ( auto& v : x ) {
            if ( !first ) {
                out += '\t';
            }
            out += to_string(v);
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
    // std::cerr << to_string(H) << "   ";
    // debug_out(T...);
    std::cerr << ' ' << to_string(H) << ' ';
    if (sizeof...(T)) {
        std::cerr << " ";
        debug_out(T...);
    }
}

// #define BOLD_MAYBE ""    // NOT bold
#define BOLD_MAYBE     ";1"  // YES bold

#define OUT_RESET       "\033[0m"
#define OUT_BOLD        "\033[;1m"
#define OUT_RED         "\033[31" << "m"
#define OUT_CYAN        "\033[36" << BOLD_MAYBE << "m"
// #define OUT_GREEN       "\033[32" << BOLD_MAYBE << "m"
#define OUT_GREEN       "\033[32" << "m"
#define OUT_BLUE        "\033[34" << BOLD_MAYBE << "m"
#define OUT_WHITE       "\033[97" << "m"
#define OUT_MARK        "\033[0;30;41;1m"
#define OUT_YELLOW      "\033[33" << BOLD_MAYBE << "m"
#define OUT_PURPLE      "\033[35" << BOLD_MAYBE << "m"


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
#define dbg_only(...) ;
#define local_run (false)
#ifdef DCCLYDE_LOCAL
    // dbgc = "debug with comment"
    #define dbgcbase(A, B, C, ...) std::cout << std::flush; \
        std::cerr << OUT_BOLD << B \
        << std::right << setw(20) << C << ' ' \
        << OUT_RESET << OUT_BOLD << OUT_RED \
        << std::right << setw(7) << __LINE__        \
        << OUT_BOLD << " : " << OUT_RESET \
        << A << "[ " << #__VA_ARGS__ << " ]" \
        << OUT_BOLD << " :   " << OUT_RESET \
        << B, debug_out(__VA_ARGS__); \
        std::cerr << OUT_RESET << std::endl;

    #undef dbgBold
    #define dbgBold(...) dbgcbase(OUT_GREEN, OUT_MARK, "", __VA_ARGS__)
    #undef dbgcBold
    #define dbgcBold(...) dbgcbase(OUT_GREEN, OUT_MARK, __VA_ARGS__)

    #undef dbg
    #define dbg(...) dbgcbase(OUT_GREEN, OUT_CYAN, "", __VA_ARGS__)
    #undef dbgc
    #define dbgc(...) dbgcbase(OUT_GREEN, OUT_CYAN, __VA_ARGS__)

    #undef dbgY
    #define dbgY(...) dbgcbase(OUT_GREEN, OUT_YELLOW, "", __VA_ARGS__)
    #undef dbgcY
    #define dbgcY(...) dbgcbase(OUT_GREEN, OUT_YELLOW, __VA_ARGS__)

    #undef dbgP
    #define dbgP(...) dbgcbase(OUT_GREEN, OUT_PURPLE, "", __VA_ARGS__)
    #undef dbgcP
    #define dbgcP(...) dbgcbase(OUT_GREEN, OUT_PURPLE, __VA_ARGS__)

    #undef dbgR
    #define dbgR(...) dbgcbase(OUT_GREEN, OUT_RED, "", __VA_ARGS__)
    #undef dbgcR
    #define dbgcR(...) dbgcbase(OUT_GREEN, OUT_RED, __VA_ARGS__)

    #undef dbgB
    #define dbgB(...) dbgcbase(OUT_GREEN, OUT_BLUE, "", __VA_ARGS__)
    #undef dbgcB
    #define dbgcB(...) dbgcbase(OUT_GREEN, OUT_BLUE, __VA_ARGS__)

    #undef dbgW
    #define dbgW(...) dbgcbase(OUT_GREEN, OUT_WHITE, "", __VA_ARGS__)
    #undef dbgcW
    #define dbgcW(...) dbgcbase(OUT_GREEN, OUT_WHITE, __VA_ARGS__)

    #undef dbg_only
    #define dbg_only(...) __VA_ARGS__;

    #undef el
    #define el std::cerr << std::flush; std::cerr << '\n';  // in my head I say "error line"

    #undef local_run
    #define local_run (true)
#endif
#pragma endregion

#define timebomb(a) {static int _bomb = 0; if(++_bomb>=a) {dbgc("BOOM");exit(1);}}

#define yes ps("YES");
#define no ps("NO");

// const int MOD = 1000000007;

#pragma endregion

// ! ---------------------------------------------------------------------------

const ll INF = 2e18;
ll cost_one(int dx, int n) {
    if (n < 0) {return INF;}
    ll base_size = dx / (n+1);
    int num_big = dx % (n+1);
    int num_base = n+1 - num_big;
    ll cost_big = num_big * (base_size + 1) * (base_size + 1);
    ll cost_base = num_base * (base_size) * (base_size);
    ll result = cost_big + cost_base;
    // dbgcP("c_o", dx, n, result);
    return result;
}

ll cost_delta(int dx, int n) {
    // dbgcR("c_d", dx, n);
    return cost_one(dx, n) - cost_one(dx, n+1);
}

#pragma region  // brute
void brute() {
    lls(N);
    ++N;
    vector<ll> dat(N);
    FOR(k, 1, N) {
        cin >> dat[k];
    }
    lls(GOAL);
    dbgR(N, GOAL, dat);

    ll out = 0;
    ll total_cost = 0;
    // (reduction from next post here, interval length, num posts)
    using t3 = tuple<ll,int,int>;
    priority_queue<t3> intervals;
    FOR(k, 0, N-1) {
        ll dx = dat[k+1] - dat[k];
        total_cost += dx*dx;
        intervals.emplace(cost_delta(dx, 0), dx, 0);
    }

    while (total_cost > GOAL) {
        ++out;
        auto [reduction, dx, n] = intervals.top();
        total_cost -= reduction;
        dbg(out, dx, n, reduction, total_cost, GOAL);
        intervals.pop();
        reduction = cost_delta(dx, n+1);
        intervals.emplace(reduction, dx, n+1);
    }
    V<t3> intervals_debug;
    while (!intervals.empty()) {
        intervals_debug.push_back(intervals.top());
        intervals.pop();
    }
    sort(all(intervals_debug));
    dbgP(intervals_debug);
    ps(out);
}
#pragma endregion

void solve() {
    lls(N);
    ++N;
    vector<ll> dat(N);
    FOR(k, 1, N) {
        cin >> dat[k];
    }
    lls(GOAL);
    dbgR(N, GOAL, dat);

    ll total_cost = 0;
    // (reduction from next post here, interval length, num posts)
    using t4 = tuple<ll,int,int,int>;
    set<t4> intervals;
    FOR(k, 0, N-1) {
        ll dx = dat[k+1] - dat[k];
        total_cost += dx*dx;
        intervals.emplace(cost_delta(dx, 0), dx, 0, k);
    }

    auto check = [&](ll T) {
        ll nc = T - N;  // number of non-constrained things we'll be inserting.
        // that breaks the space up into nc+1 intervals.

        ll tc_local = total_cost;
        set<t4> intervals_local;
        // ll T_local = T;
        ll cost_local = N;
        dbgY(T, T-N);

        /*
            Before doing priority queue stuff, do the "obvious part".
            We'd like all our intervals to have size S = dat[N-1] / (T-1).
            So, if an interval currently has size >= k*S
            then it should get at least k-1 help.
        */
        dbgP(db(dat[N-1]) / (nc+1));
        for(auto& [_1, dx, _2, iidx] : intervals) {
            ll n_new = dx * (nc+1) / dat[N-1] - 1;
            ckmax(n_new, 0);
            dbg(dx, n_new);
            ll reduction = cost_one(dx, 0) - cost_one(dx, n_new);
            tc_local -= reduction;
            cost_local += n_new;
            intervals_local.emplace(cost_delta(dx, n_new), dx, n_new, iidx);
        }
        dbg(intervals_local, cost_local);
        if (cost_local > T) {dbg(false); return false;}

        while (tc_local > GOAL) {
            ++cost_local;
            if (cost_local > T) {dbg(false); return false;}
            auto it = intervals_local.rbegin();
            auto [reduction, dx, n, iidx] = *it;
            if (reduction == 0) {dbg(false); return false;}
            tc_local -= reduction;
            dbg(cost_local, dx, n, reduction, tc_local, GOAL);
            intervals_local.erase(*it);
            reduction = cost_delta(dx, n+1);
            intervals_local.emplace(reduction, dx, n+1, iidx);
        }
        dbgP(intervals_local);
        dbg(true);
        return true;
    };
    dbgBold(N, dat[N-1]+1);
    ll teleporters_total = fstTrue(N, dat[N-1] + 1, check);
    ll out = teleporters_total - N;
    ps(out);
}

/*
    If we just spaced everything out perfectly (using doubles) with no restrictions,
    then what index post would be barely <= each of our constrained positions?
    I want jb[k] * (R / (T-1)) <= dat[k] <= (jb[k]+1) * (R/(T-1)).
    jb[k] * R <= dat[k] * (T-1)
*/

#pragma region  // solve_old
void solve_old() {
    // dbg(cost_one(14, 13));
    // dbg(cost_one(14, 14));
    // dbg(cost_one(14, 15));
    // exit(1);
    lls(N);
    ++N;
    vector<ll> dat(N);
    FOR(k, 1, N) {
        cin >> dat[k];
    }
    lls(GOAL);
    dbgR(N, GOAL, dat);

    // resort the intervals in dat to be from smallest to biggest.
    V<int> interval_sizes;
    FOR(k, 0, N-1) {
        interval_sizes.push_back(dat[k+1] - dat[k]);
    }
    sort(all(interval_sizes));
    FOR(k, 1, N) {
        dat[k] = dat[k-1] + interval_sizes[k-1];
    }

    ll R = dat.back();
    V<ll> jb(N);  // "just below"
    V<V<ll>> dp(2, V<ll>(N+1, INF));
    V<ll> dat_local;
    // function<bool(ll)> check_out = [&](ll T) {
    auto check_out = [&](ll T) {
        el; dbgY(T, T-N);
        dbg(R, dat);

        // Throw out intervals that are too small to receive any help.
        // We ideally wish every interval would have size R / (T-1).
        dat_local = {0};
        ll cost_pre = 0;
        ll offset = 0;
        ll T_local = T;
        ll R_local = R;
        dbg(db(R) / (T-1));
        FOR(k, 1, N) {
            ll dx = dat[k]-offset - dat_local.back();
            // dbgP(k, dx, offset, dat[k], dat_local, dat[k]-offset);
            if (dx * (T_local-1) <= R_local) {
                // handle this interval right now and then don't think about it.
                cost_pre += dx*dx;
                offset += dx;
                R_local = R - offset;
                --T_local;
            } else {
                dat_local.push_back(dat[k] - offset);
            }
        }
        dbg(db(R_local) / (T_local-1));
        ll N_local = dat_local.size();
        dbgP(N_local, R_local, dat_local);
        if (R_local == 0) {
            bool out = (cost_pre <= GOAL);
            dbgcY("done early", out);
            return out;
        }


        dbg_only(jb.resize(N_local));
        FOR(k, 0, N_local) {
            jb[k] = dat_local[k] * (T_local-1) / R_local;
            // dbgR(k, dat_local[k], T_local-1, R_local, jb[k]);
        }
        dbg(jb);
        FOR(o,0,2) FOR(k,0,N_local+1) {dp[o][k] = INF;}
        dp[0][0] = 0;
        FOR(n,0,N_local-1) FOR(o,0,2) {
            if (dp[o][n] == INF) {
                continue;
            }
            // dbgBold(o, n, dp[o][n]);
            FOR(p,0,2) {
                int num_between = jb[n+1] - jb[n] + p - o - 1;
                // dbg(o, n, p, num_between);
                ll cost_here = cost_one(dat_local[n+1] - dat_local[n], num_between);
                ckmin(dp[p][n+1], dp[o][n] + cost_here);
            }
        }
        ll result = dp[0][N_local-1];
        result += cost_pre;
        bool out = (result <= GOAL);
        dbgY(result, out, pdh(dp));
        return out;
    };

    // bool test = check_out(4);
    // dbg(test);
    // exit(1);

    ll teleporters_total = fstTrue(N, R + 1, check_out);
    ll out = teleporters_total - N;
    ps(out);
    return;
}
#pragma endregion

// ! Check bounds even if I have a solution - are they letting through simpler versions?
// ! If stuck on a "should be easy" problem for 10 mins, reread statement, check bounds
// ! Read the sample cases before writing code!
#define SINGLE_CASE
#pragma region
int main() {
    setIO();

    int T = 1;
#ifndef SINGLE_CASE
    dbgc("loading num cases!!!"); std::cin >> T;  // ! Comment this out for one-case problems.
#endif
    for ( int CASE = 1 ; CASE <= T ; ++CASE ) {
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
#pragma endregion
