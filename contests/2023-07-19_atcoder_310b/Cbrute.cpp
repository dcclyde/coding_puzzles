#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;

/*
    N strings, up to 2e5
    Total length up to 2e5

    Need to know: how many *distinct* strings up to optional reversal?

    I think I can just sort within each pair and then sort all pairs.
*/

int main() {
    int N; cin >> N;
    set<string> dat;
    for(int k = 0; k < N; ++k) {
        string S; cin >> S;
        if (dat.count(S)) {continue;}
        reverse(S.begin(), S.end());
        if (dat.count(S)) {continue;}  // unnecessary
        dat.insert(S);
    }
    cout << dat.size() << endl;
    return 0;
}
