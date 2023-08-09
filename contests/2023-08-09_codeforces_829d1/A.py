import sys

def solve():
    N = int(input())
    A = list(map(int, input().split()))

    S = sum(A)
    if S < 0:
        A = [-x for x in A]
        S = -S

    print(S, A, file=sys.stderr)
    # Try to find S/2 positions that can change from + to -.
    if S % 2 == 1:
        print("-1")
        return

    special = set()
    need = S // 2
    for k in range(1, N):
        if need == 0:
            break
        if A[k] == 1 and k-2 not in special:
            special.add(k-1)
            need -= 1

    if need > 0:
        print("-1")
        return

    out = []
    for k in range(N):
        if k in special:
            out.append((k+1, k+2))
        elif k-1 in special:
            pass
        else:
            out.append((k+1, k+1))

    # test that this is a valid solution.
    def check():
        X = 0
        for l, r in out:
            # print(l, r, file=sys.stderr)
            X += sum(A[l-1+k] * (-1 if k%2 == 1 else 1) for k in range(r-l+1))
        assert X == 0

    print(out, file=sys.stderr)
    check()

    print(len(out))
    for x, y in out:
        print(x, y)

    return

T = int(input())
for testid in range(T):
    solve()
