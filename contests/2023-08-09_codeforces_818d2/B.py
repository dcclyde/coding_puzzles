import sys

def solve():
    N, K, tr, tc = tuple(map(int, input().split()))
    tr -= 1
    tc -= 1
    tr %= K
    tc %= K

    '''
        (tr, tc) = (2, 5) --> offset is 3
    '''

    if tc < tr: tc += K
    offset = tc - tr

    out = [['.' for _ in range(N)] for _ in range(N)]
    for rblock in range(N//K):
        for cblock in range(N//K):
            for k in range(K):
                r = rblock * K + k
                c = cblock * K + (k + offset) % K
                # print((rblock, cblock), k, (r,c), file=sys.stderr)
                out[r][c] = 'X'

    print('\n'.join(''.join(row) for row in out))


T = int(input())
for _ in range(T):
    solve()
