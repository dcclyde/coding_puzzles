#include <iostream>
#include <vector>
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
    vector<pair<string, string>> dat(N);
    for(int k = 0; k < N; ++k) {
        cin >> dat[k].first;
        dat[k].second = dat[k].first;
        reverse(dat[k].second.begin(), dat[k].second.end());
        if (dat[k].first > dat[k].second) {
            swap(dat[k].first, dat[k].second);
        }
    }
    sort(dat.begin(), dat.end());

    int out = 1;  // first string always scores a point.
    for(int k = 1; k < N; ++k) {
        if (dat[k] != dat[k-1]) {++out;}
    }

    cout << out << endl;
    return 0;
}
