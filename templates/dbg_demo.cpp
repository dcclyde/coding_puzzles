// Stripped-down version of template.cpp that adds only the dbg() functionality.
// No guarantees that I'll remember to keep this updated as I edit template.cpp going forward.
// Compile and run with: g++ --std=c++17 -DDCCLYDE_LOCAL dbg_demo.cpp && ./a.out

#include <bits/stdc++.h>
using namespace std;

#pragma region  // setup for dbg() printouts
template <typename, typename=void>
constexpr bool is_tuplelike_v{};

template <typename T>
constexpr bool is_tuplelike_v<
    T,
    void_t<
        decltype(std::get<0>(declval<T>())),
        decltype(std::tuple_size_v<T>)
    >
> = true;

template <typename, typename = void>
constexpr bool is_iterable_v{};

template <typename T>
constexpr bool is_iterable_v<
    T,
    std::void_t< decltype(std::declval<T>().begin()),
                decltype(std::declval<T>().end())
    >
> = true;


template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename X>
typename enable_if<is_tuplelike_v<X>, string>::type to_string(X p);

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
typename enable_if<is_iterable_v<A>, string>::type to_string(A v) {
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

template<typename T>
vector<T> pqueue_to_iterable(priority_queue<T> PQ) { // PASS BY VALUE!
    vector<T> working;
    while (!PQ.empty()) {working.push_back(PQ.top()); PQ.pop();}
    reverse(all(working));
    return working;
}

template <typename T>
string to_string(priority_queue<T>&& PQ) {
    return to_string(pqueue_to_iterable(PQ));
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template<class T, size_t k>
void to_string_tuplehelper(string& out, T& t) {
    out += ", " + to_string(get<k>(t));
    if constexpr (k < tuple_size_v<T> - 1) {
        to_string_tuplehelper<T, k+1>(out, t);
    }
}
template <typename X>
typename enable_if<is_tuplelike_v<X>, string>::type to_string(X p) {
    string out = "(" + to_string(get<0>(p));
    to_string_tuplehelper<X, 1>(out, p);
    out += ")";
    return out;
}


// helpers for debugging complicated objects
template<class T, class S>
string print_details_helper_general(T&& q, S f, int MAX) {
    string out;
    int ctr = 0;
    bool trimmed = false;
    for ( auto&& x : q ) {
        if (ctr == MAX) {trimmed = true; break;}
        out.push_back('\t');
        out += to_string(ctr) + ":\t" + to_string(f(x)) + "\n";
        ++ctr;
    }
    // string prefix = "\tlen " + to_string(q.size());
    string prefix = "";
    if (trimmed) {
        // prefix += ", trimmed to " + to_string(MAX);
        out.pop_back();
        out = prefix + "\n" + out + "\n\t... (full length " + to_string(q.size()) + ")";
        out.push_back('\n');
    } else {
        out = "\n" + prefix + "\n" + out;
    }
    return out;
}

#define PDH_DEFAULT_MAX 10'000
template<class T>
string print_details_helper(T&& q, int MAX=PDH_DEFAULT_MAX) {
    return print_details_helper_general(q, [&](auto x) {return x;}, MAX);
}
string print_details_helper(vector<bool>&& q, int MAX=PDH_DEFAULT_MAX) {
    return print_details_helper_general(q, [&](auto x) {return static_cast<bool>(x);}, MAX);
}
template<class T>
string print_details_helper(priority_queue<T>&& PQ, int MAX=PDH_DEFAULT_MAX) {
    return print_details_helper(pqueue_to_iterable(PQ), MAX);
}
#define pdh print_details_helper

template<class T, class S>
string print_details_helper_func(T&& q, S f, int MAX=PDH_DEFAULT_MAX) {
    return print_details_helper_general(q, f, MAX);
}
template<class S>
string print_details_helper_func(vector<bool>&& q, S f, int MAX=PDH_DEFAULT_MAX) {
    return print_details_helper_general(q, [&](auto x) {return f(static_cast<bool>(x));}, MAX);
}
template<class T, class S>
string print_details_helper_func(priority_queue<T>&& PQ, S f, int MAX=PDH_DEFAULT_MAX) {
    return print_details_helper_general(pqueue_to_iterable(PQ), f, MAX);
}
#define pdh_func print_details_helper_func
#define pdhf print_details_helper_func


// Useful to visualize a 2D array, or copy-paste into a spreadsheet etc
template<class T>
string print_tsv_helper(T&& q) {
    string out = "\n";
    for ( auto&& x : q ) {
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
#define OUT_RED         "\033[31" "m"
#define OUT_CYAN        "\033[36" BOLD_MAYBE "m"
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

    #undef dbg_only
    #define dbg_only(...) __VA_ARGS__;

    #undef el
    #define el std::cerr << std::flush; std::cerr << '\n';  // in my head I say "error line"

    #undef local_run
    #define local_run (true)
#endif
#pragma endregion  // END setup for dbg() printouts



int main() {
    // placeholder code that demos the dbg() functionality
    // Compile and run with: g++ --std=c++17 -DDCCLYDE_LOCAL dbg_demo.cpp && ./a.out
    int a = 14; double b = -3e-2; char c = '@'; string s = "Test String";
    vector<int> q = {1, 6, 4, 3, 5, 3, 1};
    dbg(a, b, c, "", s, q);
    dbgc("show this on left", make_pair(a, c));  // dbgc = "debug with 1st arg as comment"
    dbgcP("diff colors", a, b);  // uppercase letters change the color; all terminal colors are available
    dbgc("expressions work too", 2*b, gcd(a, a+4));
    el;  // empty line

    // complex/nested data structures work too.
    map<pair<int, int>, vector<string>> dat = {
        {{3, 5}, {"abc", "def"}},
        {{4, -1}, {"apple", "peach", "banana"}},
        {{-5, 0}, {"tourist", "jiangly", "um_nik", "slime", "ksun48"}}
    };
    dbgY(dat);
    // that may be pretty messy to read all on one line though, so we can use:
    dbg(pdh(dat));
    el;

    // show how "regular output" lines look visibly different from dbg() lines.
    cout << a << ' ' << b << ' ' << c << '\n';

    // what if we have a big object and we want to "get the idea" of its contents
    // without printing the whole thing?
    vector<pair<int, int>> vbig; for(int k=0; k<100; ++k) {vbig.emplace_back(k, -k*k);}
    dbgR(pdh(vbig, 10));  // short for "print_details_helper"

    el;
    // Advanced: pdhf lets me specify a function, so f(x) will be printed for each x in the structure.
    dbg(pdhf(vbig, [&](auto x){return x.second;}, 5));  // pdhf = "print_details_helper_func"

    dbgcBold("done!");

    return 0;
}
