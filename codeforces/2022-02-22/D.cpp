
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;
ll MOD = 998244353;

void solve(int R, int C, int num_colors, int num_ops) {
    std::vector<std::pair<int, int>> ops( num_ops );
    for ( int k = 0 ; k < num_ops ; ++k ) {
        int rr, cc;
        std::cin >> rr >> cc;
        ops[k].first = rr - 1;
        ops[k].second = cc - 1;
    }
    
    std::vector<bool> row_seen( R , false );
    std::vector<bool> col_seen( C , false );
    int num_rows_seen = 0;
    int num_cols_seen = 0;
    ll out = 1;

    for ( int k = num_ops - 1 ; k >= 0 ; --k ) {
        int rr = ops[k].first;
        int cc = ops[k].second;
        bool row_irrelevant = (row_seen[rr] || num_cols_seen == C);
        bool col_irrelevant = (col_seen[cc] || num_rows_seen == R);
        
        if ( !row_seen[rr] ) {
            row_seen[rr] = true;
            num_rows_seen += 1;
        }
        if ( !col_seen[cc] ) {
            col_seen[cc] = true;
            num_cols_seen += 1;
        }

        if ( !( row_irrelevant && col_irrelevant ) ) {
            out = (out * num_colors) % MOD;
        }
        if ( num_rows_seen == R && num_cols_seen == C ) {
            break;
        }
    }
    std::cout << out << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    int T;
    std::cin >> T;
    for ( int k = 0 ; k < T ; ++k ) {
        int R; std::cin >> R;
        int C; std::cin >> C;
        int num_colors; std::cin >> num_colors;
        int num_ops; std::cin >> num_ops;
        solve(R, C, num_colors, num_ops);
    }

    return 0;
}
