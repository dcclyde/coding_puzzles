
from collections import defaultdict

def solve():
    N = int(input())
    A = list(map(int, input().split()))
    Q = int(input())
    queries = []
    for q in range(Q):
        queries.append(tuple(map(int, input().split())))

    cnt = defaultdict(int)
    for a in A:
        cnt[a] += 1

    out = [0 for _ in range(Q)]
    for qid, (S, P) in enumerate(queries):
        # x^2 - S*x + P = 0
        discriminant = S**2 - 4*P
        if discriminant < 0: continue

        # test if the quadratic has integer solutions, and if so find them.

        # x = (S +- sqrt(S^2 - 4P)) / 2

        sqrt_maybe = int(discriminant**0.5)
        success = False
        for offset in range(-2, 3):
            if (sqrt_maybe + offset) ** 2 == discriminant:
                success = True
                sqrt_maybe += offset
                break
        if not success: continue

        if (S + sqrt_maybe) % 2 != 0: continue

        a = (S + sqrt_maybe) // 2
        b = S - a
        if a not in cnt or b not in cnt: continue

        if a == b:
            out[qid] = cnt[a] * (cnt[a] - 1) // 2
        else:
            out[qid] = cnt[a] * cnt[b]


    print(' '.join(map(str, out)))
    return


T = int(input())
for t in range(T):
    solve()
