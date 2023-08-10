
MOD = 10**9 + 7

N, K = tuple(map(int, input().split()))

if K >= N:
    # worst possible result.
    out = pow(2, N, MOD)
    print(out)
    exit(0)

fact_helper = [1]
def fact(n):
    while n >= len(fact_helper):
        fact_helper.append(fact_helper[-1] * len(fact_helper) % MOD)
    return fact_helper[n]

def comb(n, k):
    if not (0 <= k <= n):
        return 0
    return fact(n) * pow(fact(k), MOD-2, MOD) * pow(fact(n-k), MOD-2, MOD) % MOD

# how many N digit binary numbers have at most K zeros?
out = 0
for k in range(0, K+1):
    out += comb(N, k)
    out %= MOD

print(out)
