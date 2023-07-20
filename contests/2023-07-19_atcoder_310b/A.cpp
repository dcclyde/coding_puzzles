#include <iostream>
using namespace std;

/*
    P
    or
    Q + min of the N dishes.
*/

// To execute C++, please define "int main()"
int main() {
    int N; int P; int Q;
    cin >> N >> P >> Q;
    int out = P;
    int d;
    for(int k = 0; k < N; ++k) {
        cin >> d;
        out = min(out, Q + d);
    }
    cout << out << endl;
    return 0;
}
