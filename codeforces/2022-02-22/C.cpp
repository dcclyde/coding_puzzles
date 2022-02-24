
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

void solve(const std::vector<ll>& dat, ll toadd) {
    int N = dat.size();
    std::vector<ll> maxes( N+1 , -1e16 );
    maxes[0] = 0;
    for ( int front = 0 ; front < N ; ++front ) {
        ll curr_sum = 0;
        for ( int back = front ; back < N ; ++back ) {
            curr_sum += dat[ back ];
            int length = back - front + 1;
            maxes[ length ] = std::max( maxes[length] , curr_sum );
            // std::cerr << "sum " << curr_sum << ", front = " << front << ", back = " << back << ", maxes =";
            // for ( auto& x : maxes ) {
            //     std::cerr << ' ' << x;
            // }
            // std::cerr << '\n';
        }
    }
    
    for ( int k = 0 ; k <= N ; ++k ) {
        ll best = 0;
        for ( int L = 0 ; L <= N ; ++L ) {
            ll curr = maxes[L] + toadd * std::min(L, k);
            best = std::max(curr, best);
        }
        std::cout << best << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    int T;
    std::cin >> T;
    for ( int k = 0 ; k < T ; ++k ) {
        int N;
        std::cin >> N;
        int toadd;
        std::cin >> toadd;
        std::vector<ll> dat( N );
        for ( int j = 0 ; j < N ; ++j ) {
            std::cin >> dat[j];
        }
        solve(dat, toadd);
    }

    return 0;
}
