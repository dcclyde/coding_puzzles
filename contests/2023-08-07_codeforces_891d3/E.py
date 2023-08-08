
def solve():
    N = int(input())
    A = list(map(int, input().split()))
    out = [None for _ in range(N)]

    B = [(A[k], k) for k in range(N)]
    B.sort()

    out[B[0][1]] = 0
    for k in range(N):
        out[B[0][1]] += abs(B[k][0] - B[0][0]) + 1

    for k in range(1, N):
        delta = B[k][0] - B[k-1][0]
        out[B[k][1]] = out[B[k-1][1]] + (k * delta) - ((N-k) * delta)

    print(' '.join(map(str, out)))

T = int(input())
for _ in range(T):
    solve()
