#pragma once

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

///// START debug setup, mostly stolen from tourist.
///// https://codeforces.com/contest/1540/submission/120602670

#define el cerr << '\n';  // in my head I say "error line"

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

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
#define OUT_GREEN   "\033[32" << BOLD_MAYBE << "m"
#define OUT_BLUE    "\033[34" << BOLD_MAYBE << "m"

// dbc = "debug with comment"
#define dbc(A, ...) cerr << OUT_RED << right << setw(8) << __LINE__        \
    << " " << A << OUT_BOLD << "\t: " << OUT_GREEN          \
    << "[ " << #__VA_ARGS__ << " ]" << OUT_BOLD << " :    " \
    << OUT_CYAN, debug_out(__VA_ARGS__); \
    cerr << OUT_RESET
#define db(...) dbc("", __VA_ARGS__)

///// END debug setup, mostly stolen from tourist.
