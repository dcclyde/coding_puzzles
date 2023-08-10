import sys
MOD = 10**9 + 7

N = int(input())

# sieve and compute phi.
sp = [-1 for _ in range(N+1)]
for p in range(2, N+1):
    if sp[p] == -1:
        sp[p] = p
        for q in range(p*p, N+1, p):
            if sp[q] == -1:
                sp[q] = p

# totient function
def totient(n):
    if n == 0: return 0
    if n == 1: return 1

    out = n
    wip = n
    while wip > 1:
        p = sp[wip]
        out = out // p * (p-1)
        while wip % p == 0: wip //= p
    return out

phi = [totient(n) for n in range(N+1)]
# print(phi, file=sys.stderr)

pair_sum_le = [0 for _ in range(N+1)]
pair_sum_le[2] = 1
for n in range(3, N+1):
    # pair_sum_le[n] = pair_sum_le[n-1] + phi[n] // 2
    pair_sum_le[n] = pair_sum_le[n-1] + phi[n]
# print(pair_sum_le, file=sys.stderr)

pair_sum_le_weighted = [0 for _ in range(N+1)]
pair_sum_le_weighted[2] = 2
for n in range(3, N+1):
    # pair_sum_le_weighted[n] = pair_sum_le_weighted[n-1] + n * phi[n] // 2
    pair_sum_le_weighted[n] = pair_sum_le_weighted[n-1] + n * phi[n]
# print(pair_sum_le_weighted, file=sys.stderr)

def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

# divs = [g for g in range(1, N+1) if N % g == 0]
out = 0
for g in range(1, N+1):
    if N - 2*g <= 0: break

    scalar = g // gcd(g, N)
    # main = N * phi_prefix[(N-1)//g] - g * phi_prefix_weighted[(N-1)//g]
    main = N * pair_sum_le[(N-1)//g] - g * pair_sum_le_weighted[(N-1)//g]
    # print(scalar, main, file=sys.stderr)
    curr = scalar * main

    # print(g, scalar, main, curr, file=sys.stderr)
    out += curr
    out %= MOD

print(out)

