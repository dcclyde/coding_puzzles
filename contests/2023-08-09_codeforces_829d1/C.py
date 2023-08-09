import sys
MOD = 998_244_353

def divmod(a, b):
    return a * pow(b, MOD-2, MOD) % MOD

def solve():
    N = int(input())
    A = list(map(int, input().split()))

    C = 0
    B = sorted(A)
    for k in range(N):
        if A[k] == B[k]: C += 1

    # print(C, A, file=sys.stderr)
    out = 0  # answer for C == N.
    for a in range(1, (N-C) // 2 + 1):
        c = N - 2*a

        # P_no_trash = divmod(2*a * (2*a-1), 2*N * (2*N-1))
        P = divmod(2*a*a, (N * (N-1)))

        # out = 1 + divmod(a**2, (2*a+c)**2) * out
        # out += divmod((2*a+c)**2, a**2)
        out += divmod(1, P)
        out %= MOD
        # print(a, c, out, file=sys.stderr)


    print(out)
    return



T = int(input())
for i in range(T):
    solve()
