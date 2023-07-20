
'''
dp[n][mask] = ways to roll first n dice and end up able to hit exactly mask

'''

MOD = 998244353
T = 10

N = int(input())
A = list(map(int, input().split()))

out_denom_inv = 1
for x in A:
    out_denom_inv *= pow(x, MOD-2, MOD)

# 0 is always hittable.
# If we can hit 10 then we don't care about the rest of the mask anyway.
MASK_END = (1 << (T-1)) + 1
MASK_DONE = MASK_END - 1

dp = [[0 for _1 in range(MASK_END)] for _2 in range(N+1)]

# Base case: with 0 dice we can only hit 0.
dp[0][0] = 1

for n in range(1, N+1):
    for mask in range(0, MASK_END):
        if dp[n-1][mask] == 0: continue
        for roll in range(1, A[n-1] + 1):

            # what will the new mask be?
            if roll > T:
                new_mask = mask
                mult = A[n-1] - T
            elif (
                mask == MASK_DONE
                or roll == T
                or ((mask >> (T-roll-1)) & 1) == 1
            ):
                new_mask = MASK_DONE
                mult = 1
            else:
                new_mask = mask | (mask << roll) | (1 << (roll-1))
                new_mask &= (1<<(T-1)) - 1
                mult = 1

            # if new_mask >= MASK_END:
            #     print('\t', mask, bin(mask), roll, new_mask, bin(new_mask))
            dp[n][new_mask] += dp[n-1][mask] * mult

            if roll > T: break

out_num = dp[N][MASK_DONE]

out = (out_num * out_denom_inv) % MOD
print(out)
