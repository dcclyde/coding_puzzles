
MOD = 998_244_353

A = input().strip()
N = len(A)

dp = [
    [0 for h in range(N+1)]
    for n in range(N+1)
]

# base case
dp[0][0] = 1

for n in range(N):
    if A[n] == '(': dirs = {1}
    elif A[n] == ')': dirs = {-1}
    else: dirs = {-1, 1}

    for dh in dirs:
        for h in range(N):
            hh = h + dh
            if hh < 0 or hh > N: continue
            dp[n+1][hh] += dp[n][h]
            dp[n+1][hh] %= MOD

print(dp[n+1][0])
