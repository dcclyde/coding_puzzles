
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

auto rv(ll N, ll lo, ll hi, ll weight) {
    vector<ll> v(N);
    for (ll i = 0; i < N; i++) {
        v[i] = rnd.wnext(lo, hi, weight);
    }
    return v;
}

auto pv(auto&& v) {
    string out;
    for (auto&& x : v) {
        out += to_string(x) + ' ';
    }
    out.pop_back();
    cout << out << endl;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int ctr = 1;
    int N_MAX = opt<int>("nmax");
    int NA_WEIGHT = opt<int>("naweight");
    int NB_WEIGHT = opt<int>("nbweight");
    int MAX_VALUE = opt<int>("vmax");
    int WEIGHT_VALUE = opt<int>("vweight");

    int nA = rnd.wnext(1, N_MAX, NA_WEIGHT);
    int nB = rnd.wnext(1, N_MAX, NB_WEIGHT);

    cout << nA << ' ' << nB << '\n';

    pv(rv(nA, 1, MAX_VALUE, WEIGHT_VALUE));
    pv(rv(nB, 1, MAX_VALUE, WEIGHT_VALUE));

    return 0;
}
