
#include <iostream>
#include <vector>
#include <map>
typedef long long ll;

void solve() {
    int N;
    std::cin >> N;
    int total = 0;

    std::vector<ll> A( N );
    for ( int k = 0 ; k < N ; ++k ) {
        std::cin >> A[k];
        total += A[k];
    }
    std::vector<ll> B( N );
    for ( int k = 0 ; k < N ; ++k ) {
        std::cin >> B[k];
        total += B[k];
    }

    std::vector<std::map<ll, bool>> f(N+1);
    f[0][0] = false;
    for ( int k = 1 ; k <= N ; ++k ) {
        for ( const auto& [sum, prev] : f[k-1] ) {
            f[k][sum + A[k-1]] = true;
            f[k][sum + B[k-1]] = false;
        }
//        std::cerr << "Dumping f[ " << k << " ]:" << std::endl;
//        for ( const auto& [sum, prev] : f[k] ) {
//            std::cerr << sum << '\t' << prev << std::endl;
//        }
//        std::cerr << std::endl;
    }

    int best_sum = 1e9;
    for ( const auto& [sum, prev] : f[N] ) {
        if ( abs(2*sum - total) < abs(2*best_sum - total) ) {
            best_sum = sum;
        }
    }

//    std::cerr << "N: " << N << std::endl;
//    std::cerr << "best sum: " << best_sum << std::endl;

    // swap things so that A adds up to best_sum.
    for ( int k = N-1 ; k >= 0 ; --k ) {
        if ( ! f[k + 1][best_sum] ) {
//            std::cerr << "Switching in step " << k << std::endl;
            std::swap(A[k], B[k]);
        }
        best_sum -= A[k];
//        std::cerr << "After step " << k << ", best_sum = " << best_sum << std::endl;

//        for ( auto& x : A) {
//            std::cerr << x << ' ';
//        }
//        std::cerr << std::endl;
//        for ( auto& x : B) {
//            std::cerr << x << ' ';
//        }
//        std::cerr << std::endl << std::endl;
    }

    // now compute the cost.
//    std::cerr << "Computing cost." << std::endl;
//    for ( auto& x : A) {
//        std::cerr << x << ' ';
//    }
//    std::cerr << std::endl;
//    for ( auto& x : B) {
//        std::cerr << x << ' ';
//    }
//    std::cerr << std::endl;

    ll out = 0;
    for ( int j = 0 ; j < N ; ++j ) {
        for ( int k = j+1 ; k < N ; ++k ) {
            ll aa = A[j] + A[k];
            out += aa * aa;

            ll bb = B[j] + B[k];
            out += bb * bb;
        }
    }

    std::cout << out << std::endl;
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
