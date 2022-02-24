
#include <iostream>
#include <vector>
typedef long long ll;

void solve() {
    int N;
    std::cin >> N;
    std::vector<ll> dat( N );
    for ( int k = 0 ; k < N ; ++k ) {
        std::cin >> dat[k];
    }
    bool ok = true;
    for ( int k = 0 ; k < N-1 ; ++k ) {
        if ( dat[k] > dat[k+1] ) {
            ok = false;
            break;
        }
    }
    if ( ok ) {
        std::cout << "NO" << std::endl;
    } else {
        std::cout << "YES" << std::endl;
    }
    return;
}

int main()
{
    int T;
    std::cin >> T;
    for ( int k = 0 ; k < T ; ++k ) {
        solve();
    }
    return 0;
}
