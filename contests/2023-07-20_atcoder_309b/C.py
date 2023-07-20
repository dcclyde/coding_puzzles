
'''
I could binary search for the answer. N * log of max a_j
Alternatively, I could sort things. N*log(N).
I guess sorting is technically a little better. Either would work though.
'''

N, TARG = list(map(int, input().split()))
dat = []
for _ in range(N):
    dat.append(tuple(map(int, input().split())))

dat.sort()
curr_pills = sum(q[1] for q in dat)
if curr_pills <= TARG:
    print(1)
    exit(0)
for last_day, pills in dat:
    curr_pills -= pills
    if curr_pills <= TARG:
        print(last_day + 1)
        exit(0)
