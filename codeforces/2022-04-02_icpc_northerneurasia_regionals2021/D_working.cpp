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
// using pl = pair<ll,ll>;
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
using vpl = V<pll>;
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
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(CONCAT(_,__LINE__),a)
#define each(a,x) for (auto& a: x)
#define foreach(a,x) each(a,x)


//// const int MOD = 1e9+7; // 998244353;  // I can add this myself.
const int MX = 2e5+5;
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

tcT> bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0; } // set a = max(a,b)

int maxi(int a, int b) {return max((int)a, (int)b);}
int mini(int a, int b) {return min((int)a, (int)b);}
ll maxll(ll a, ll b) {return max((ll)a, (ll)b);}
ll minll(ll a, ll b) {return min((ll)a, (ll)b);}

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
    template<class T> void pr_sep1(ostream& os, str, const T& t) { os << ts(t); }
    template<class T, class... U> void pr_sep1(ostream& os, str sep, const T& t, const U&... u) {
        pr_sep1(os,sep,t); os << sep; pr_sep1(os,sep,u...); }
    // print w/ no spaces
    template<class ...T> void pr(const T&... t) { pr_sep(cout,"",t...); }
    // print w/ spaces, end with newline
    void ps() { cout << "\n"; }
    template<class ...T> void ps(const T&... t) { pr_sep(cout," ",t...); ps(); }
    void ps1() { cout << "\n"; }
    template<class ...T> void ps1(const T&... t) { pr_sep1(cout," ",t...); ps1(); }

    template<class T>
    void pv(T& dat) {bool first=true; for(auto& x : dat) {if (!first) {cout<<' ';} first=false; cout << x;} cout<<'\n';}
    template<class T>
    void pv1(T& dat) {bool first=true; for(auto& x : dat) {if (!first) {cout<<' ';} first=false; cout << x+1;} cout<<'\n';}
    // * Remove debug code; I'll use the tourist+me amalgamation instead.

    const clock_t beg = clock();
    // #define dbg_time() dbg((db)(clock()-beg)/CLOCKS_PER_SEC)
    db TIME() {return (db)(clock()-beg)/CLOCKS_PER_SEC;}

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
        out += to_string(ctr) + "\t" + to_string(x) + "\n";
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


void debug_out() { std::cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    std::cerr << to_string(H) << "   ";
    debug_out(T...);
}

// #define BOLD_MAYBE ""    // NOT bold
#define BOLD_MAYBE     ";1"  // YES bold

#define OUT_RESET       "\033[0m"
#define OUT_BOLD        "\033[;1m"
#define OUT_RED         "\033[31" << BOLD_MAYBE << "m"
#define OUT_CYAN        "\033[36" << BOLD_MAYBE << "m"
// #define OUT_GREEN       "\033[32" << BOLD_MAYBE << "m"
#define OUT_GREEN       "\033[32" << "m"
#define OUT_BLUE        "\033[34" << BOLD_MAYBE << "m"
#define OUT_MARK        "\033[0;30;41m"
#define OUT_YELLOW      "\033[33" << BOLD_MAYBE << "m"
#define OUT_PURPLE      "\033[35" << BOLD_MAYBE << "m"


#define dbgc(...) ;
#define dbg(...) ;
#define el ;
#define dbgcBold(...) ;
#define dbgY(...) ;
#define dbgcY(...) ;
#define dbgP(...) ;
#define dbgcP(...) ;
#define dbgR(...) ;
#define dbgcR(...) ;
#define dbg_only(...) ;
#define local_run (false)
#ifdef DCCLYDE_LOCAL
    // dbgc = "debug with comment"
    #define dbgcbase(A, B, C, ...) std::cerr << OUT_BOLD << OUT_RED \
        << std::right << setw(20) << C \
        << std::right << setw(8) << __LINE__        \
        << OUT_BOLD << " : " << OUT_RESET \
        << A << "[ " << #__VA_ARGS__ << " ]" \
        << OUT_BOLD << " :    " << OUT_RESET \
        << B, debug_out(__VA_ARGS__); \
        std::cerr << OUT_RESET;

    #undef dbgcBold
    #define dbgcBold(...) dbgcbase(OUT_GREEN, OUT_CYAN, OUT_MARK<<__VA_ARGS__)

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

    #undef dbg_only
    #define dbg_only(...) __VA_ARGS__;

    #undef el
    #define el std::cerr << '\n';  // in my head I say "error line"

    #undef local_run
    #define local_run (true)
#endif


#define yes return ps("YES");
#define no return ps("NO");

// const int MOD = 1000000007;

#pragma endregion

// ! ---------------------------------------------------------------------------






void solve() {
    ints(N, D);
    vector<ll> dat;
    rv(N, dat);
    dbgY(N, dat);

    if (D == 0) {
        // use everything.
        int prod = 1;
        for(auto& x : dat) {
            prod *= x;
            prod %= 10;
        }
        if ( prod == D ) {
            ps(dat.size());
            pv(dat);
            return;
        } else {
            return ps(-1);
        }
    }

    V<V<int>> per_digit(10);
    for(auto& x : dat) {
        per_digit[x%10].push_back(x);
    }
    per_digit[0].clear();  // * Never use 0s unless that's the target.
    FOR(k, 0, 10) {
        sort(all(per_digit[k]));
    }

    V<umap<int, int>> helper(10);
    FOR(d, 0, 10) {
        int curr = 1;
        helper[d][1] = 0;
        FOR(k, 0, per_digit[d].size()) {
            auto& x = per_digit[d][k];
            curr *= x;
            curr %= 10;
            helper[d][curr] = k+1;
        }
    }
    dbg(pdh(helper));

    FOR(d, 0, 10) {
        if ( D % 2 == 1 ) {
            for(int k=2; k<10; k+=2) {
                helper[d].erase(k);
            }
        }

    }

    V<V<pii>> hvec(10);  // (value mod 10, num used to get here)
    int num_options = 1;
    FOR(d, 0, 10) {
        hvec[d].insert(hvec[d].begin(), all(helper[d]));
        sort(all(hvec[d]));
        num_options *= hvec[d].size();
    }
    dbg(pdh(hvec));
    dbg(num_options);

    V<V<db>> suffix_logsums(10);
    V<V<ll>> suffix_products(10);
    V<V<ll>> prefix_logsums(10);
    V<V<ll>> prefix_products(10);
    FOR(d, 0, 10) {
        auto& sl = suffix_logsums[d];
        auto& sp = suffix_products[d];
        auto& pl = prefix_logsums[d];
        auto& pp = prefix_products[d];
        int n = per_digit[d].size();
        sl.resize(n+1);
        sp.resize(n+1);
        pl.resize(n+1);
        pp.resize(n+1);
        sp[n] = 1;
        pp[0] = 1;
        for(int k = n-1; k >= 0 ; --k) {
            sl[k] = sl[k+1] + log10(per_digit[d][k]);
            sp[k] = sp[k+1] * per_digit[d][k];
        }
        for(int k = 0; k < n ; ++k ) {
            pl[k+1] = pl[k] + log10(per_digit[d][k]);
            pp[k+1] = pp[k] * per_digit[d][k];
        }
    }
    dbgP(pdh(suffix_products));
    dbgY(pdh(prefix_products));

    db best_logsum = 2e18;
    // ll best_logsum = 2e18;
    V<int> best_omitted;
    FOR(oid, 0, num_options) {
        int oid_working = oid;
        db omitted_logsum = 0.;
        // ll omitted_logsum = 1;
        int curr_d = 1;
        V<int> num_omitted(10);
        bool omitted_all = true;
        FOR(d, 0, 10) {
            int cidx = oid_working % hvec[d].size();
            oid_working /= hvec[d].size();

            // how many items from this pile will we actually use?
            auto& [d_pile, num_used_pile] = hvec[d][cidx];
            if ( num_used_pile > 0 ) {
                omitted_all = false;
            }
            curr_d *= d_pile; curr_d %= 10;
            num_omitted[d] = per_digit[d].size() - num_used_pile;
            omitted_logsum += prefix_logsums[d][num_omitted[d]];
            // omitted_logsum *= prefix_products[d][num_omitted[d]];
            dbgP(d, prefix_products[d][num_omitted[d]]);
        }
        dbg(oid, omitted_logsum, curr_d, num_omitted);
        if ( omitted_all || curr_d != D ) {
            continue;
        }
        if ( ckmin(best_logsum, omitted_logsum) ) {
            best_omitted = num_omitted;
        }
    }
    if ( best_logsum >= 1e18 ) {
        return ps(-1);
    }
    V<int> out;
    FOR(d, 0, 10) {
        FOR(k, best_omitted[d], per_digit[d].size()) {
            out.push_back(per_digit[d][k]);
        }
    }

    sort(all(out));
    ps(out.size());
    pv(out);
    return;
}

// ! Check bounds even if I have a solution - are they letting through simpler versions?
// ! If stuck on a "should be easy" problem for 10 mins, reread statement, check bounds
// ! Read the sample cases before writing code!
#pragma region
int main() {
    setIO();

    int T = 1;
    // dbgc("loading num cases!!!"); std::cin >> T;  // ! Comment this out for one-case problems.
    for ( int CASE = 1 ; CASE <= T ; ++CASE ) {
        el; dbgcBold("CASE" , CASE );
#ifndef DCCLYDE_BRUTEFORCE
        solve();
#else
        brute();
#endif
    }
    dbg(TIME());

    return 0;
}
#pragma endregion
