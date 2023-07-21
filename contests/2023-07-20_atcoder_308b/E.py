'''
For any given way to get M E X as a subseq of the string,
    we get a contribution of mex(corresponding numbers).

Maybe dp[n] is like (
    ways to have (M, 0),
    ways to have (M, 1),
    ...
    ways to have (ME, 0),
    ways to have (ME, 01),
    ...

)

I don't need to store any previous dp's.

'''

N = int(input())
A = list(map(int, input().split()))
S = input()

NEED = 'MEX'
ndict = {c: k for k, c in enumerate(NEED)}

MASK_END = (1 << len(NEED))
wip = [[0 for x in range(MASK_END)] for y in range(len(NEED))]

for k in range(N):
    v = A[k]
    c = S[k]
    pos = ndict[c]

    if pos == 0:
        wip[0][(1<<v)] += 1
    else:
        for mask in range(MASK_END):
            wip[pos][mask | (1<<v)] += wip[pos-1][mask]

out = 0
for mask in range(MASK_END):
    ways = wip[len(NEED)-1][mask]
    mex = 0
    while ((mask >> mex) & 1) == 1:
        mex += 1
    out += ways * mex

print(out)
