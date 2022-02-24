
#include <iostream>
#include <vector>
#include <map>
typedef long long ll;

void solve() {
    int N;
    std::cin >> N;
    int num_bad_pairs;
    std::cin >> num_bad_pairs;

    std::map<ll, int> Am( N );
    for ( int k = 0 ; k < N ; ++k ) {
        int x;
        std::cin >> x;
        Am[x] += 1;
    }

    std::vector<std::pair<int, int>> A;
    for ( const auto& [val, count] : Am ) {
        A.emplace_back( val , count );
    }
    std::sort( A.begin(), A.end() );

    std::vector<std::pair

    std::vector<std::pair<int, int>> bad_pairs;
    for ( int k = 0 ; k < num_bad_pairs ; ++k ) {
        int x, y;
        std::cin >> x >> y;
        bad_pairs.emplace_back( x , y );
    }



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
