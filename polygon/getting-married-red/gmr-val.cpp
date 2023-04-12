#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int nA = inf.readInt(1, 100'000, "W");
    inf.readSpace();
    int nB = inf.readInt(1, 100'000, "M");
    inf.readEoln();

    // read nA integers into a vector called A.
    // Then read nB more integers into a vector called B.
    vector<int> A = inf.readInts(nA, 0, 1'000'000, "women's salaries");
    inf.readEoln();
    vector<int> B = inf.readInts(nB, 0, 1'000'000, "men's salaries");
    inf.readEoln();

    inf.readEof();
    return 0;
}
