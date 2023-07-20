#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <assert.h>
using namespace std;

/*
    binary string S
    length is N <= 1e6.

    I need sum over all intervals [l, r] of:
        A_l # A_{l+1} # ... # A{r}
        applying left to right
        # is "nand".

    *****

    Probably I can just track:
    For each r, how many intervals ending at r give a 1?
*/

using ll = long long;

int main() {
    int N; cin >> N;
    string S; cin >> S;

    ll out = 0;
    ll curr = 0;
    for(int r = 0; r < N; ++r) {
        if (S[r] == '0') {
            // ALL prev strings can be extended here.
            curr = r;
            // ...but this isn't a good 1-len string.
        } else {
            // need strings ending at prev position that did NOT give 1s.
            curr = r - curr;
            // ... and this is also a good 1-len string.
            ++curr;
        }
        out += curr;
    }

    cout << out << endl;
    return 0;
}
