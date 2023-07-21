import functools

N = int(input())
dat = [tuple(map(int, input().split())) for _ in range(N)]

dat = [(k, q[0], q[1]) for k, q in enumerate(dat)]

# sort by decreasing success rate, then by asc index.
def compare(x, y):
    xh = x[1] * (y[1] + y[2])
    yh = y[1] * (x[1] + x[2])
    xt = (-xh, x[0])
    yt = (-yh, y[0])
    if xt < yt: return -1
    elif xt == yt: return 0
    else: return 1

dat.sort(key=functools.cmp_to_key(compare))

out = [q[0] for q in dat]
print(' '.join(str(x+1) for x in out))

