
#include <iostream>
#include <vector>
#include <map>

void solve(
    const std::vector< std::vector<int> >& rows,
    const std::vector< std::vector<int> >& cols,
    std::vector< std::vector<int> >& out
)
{
    int R = rows.size();
    int C = cols.size();

    // Find where the 1st element of rows[0] appears in cols.
    int special_col = -1;
    for ( int r = 0 ; r < rows.size() ; ++r ) {
        for ( int c = 0 ; c < cols.size() ; ++c ) {
            if ( cols[ c ][ r ] == rows[ 0 ][ 0 ] ) {
                special_col = c;
                break;
            }
        }
        if ( special_col >= 0 ) {
            break;
        }
    }

    // need inverse map for the special column.
    std::map<int, int> scol_inv;
    for ( int r = 0 ; r < R ; ++r ) {
        scol_inv[ cols[ special_col ][ r ] ] = r;
    }

    for ( int r = 0 ; r < R ; ++r ) {
        int idx = scol_inv[ rows[ r ][ 0 ] ];
        for ( int c = 0 ; c < C ; ++c ) {
            out[ idx ][ c ] = rows[ r ][ c ];
        }
    }
    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie( NULL );
    std::cout.tie( NULL );

    int T;
    std::cin >> T;
    std::vector< std::vector<int> > rows;
    std::vector< std::vector<int> > out;
    std::vector< std::vector<int> > cols;
    int R, C;
    for ( int k = 0 ; k < T ; ++k ) {
        std::cin >> R >> C;
        int M = R;
        int N = C;
        rows.resize( M );
        out.resize( M );
        for ( int r = 0 ; r < M ; ++r ) {
            rows[ r ].resize( N );
            out[ r ].resize( N );
            for ( int c = 0 ; c < N ; ++c ) {
                std::cin >> rows[ r ][ c ];
            }
        }

        cols.resize( N );
        for ( int c = 0 ; c < N ; ++c ) {
            cols[ c ].resize( M );
            for ( int r = 0 ; r < M ; ++r ) {
                std::cin >> cols[ c ][ r ];
            }
        }
        solve(rows, cols, out);

        for ( int r = 0 ; r < R ; ++r ) {
            for ( int c = 0 ; c < C ; ++c ) {
                std::cout << out[r][c] << ' ';
            }
            std::cout << '\n';
        }
    }

    return 0;
}
