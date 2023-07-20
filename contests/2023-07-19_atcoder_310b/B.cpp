#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

/*
    Looks like I should just compare all pairs of products.
*/

struct Product {
    int price;
    unordered_set<int> functions;
};

int main() {
    int N, TOTAL_FEATURES;
    cin >> N >> TOTAL_FEATURES;

    vector<Product> dat(N);
    for(int k = 0; k < N; ++k) {
        auto& curr = dat[k];
        cin >> curr.price;
        int len; cin >> len;
        for(int j = 0; j < len; ++j) {
            int x; cin >> x;
            curr.functions.insert(x);
        }
    }

    // sort unnecessarily, just practicing the syntax.
    sort(dat.begin(), dat.end(), [&](Product& P, Product& Q) -> bool {
        return (P.price < Q.price);
    });

    // function for checking one pair.
    // Is dat[a] strictly better than dat[b]?
    auto check_pair = [&](int a, int b) -> bool {
        // bool equal = true;
        if (dat[a].price > dat[b].price) {return false;}
        // else if (dat[a].price < dat[b].price) {equal = false;}

        for(auto& x : dat[b].functions) {
            if (dat[a].functions.count(x) == 0) {
                return false;
            }
        }
        // if (dat[a].functions.size() > dat[b].functions.size()) {equal = false;}
        return true;
    };

    // now just check all pairs one at a time.
    for(int a = 0; a < N; ++a) {
        for (int b = a+1; b < N; ++b) {
            bool a_leq_b = check_pair(a, b);
            bool b_leq_a = check_pair(b, a);
            if (a_leq_b ^ b_leq_a) {
                cout << "Yes";
                return 0;
            }
        }
    }
    cout << "No";
    return 0;
}
