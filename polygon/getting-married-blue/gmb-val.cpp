#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 200, "N");
    inf.readEoln();

    vector<int> A = inf.readInts(N, 0, 1'000'000, "salaries");
    inf.readEoln();

    inf.readEof();
    return 0;
}
