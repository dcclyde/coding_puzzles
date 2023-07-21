
R, C = list(map(int, input().split()))
dat = [input() for _ in range(R)]

SNUKE = 'snuke'
sdict = {c: k for k, c in enumerate(SNUKE)}

START = (0,0)
GOAL = (R-1, C-1)
STEPS = ((0,1), (1,0), (0,-1), (-1,0))


vis = {(0,0)}
todo = [(0,0)]
while len(todo) > 0:
    r, c = todo.pop()
    for dr, dc in STEPS:
        rr = r+dr
        cc = c+dc
        if (rr, cc) in vis: continue
        if not (0 <= rr < R and 0 <= cc < C): continue
        if dat[rr][cc] not in sdict: continue
        if sdict[dat[rr][cc]] != (sdict[dat[r][c]] + 1) % len(SNUKE): continue

        # ok, looks like we can walk here.
        if (rr, cc) == GOAL:
            print('Yes')
            exit(0)

        vis.add((rr, cc))
        todo.append((rr, cc))

print('No')
