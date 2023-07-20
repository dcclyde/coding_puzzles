
'''
Seems like we want
(max distance from v1 to anything in first group)
+ (max distance from vLAST to anything in second group)
+ 1.

The first two can just be bfs.
'''

from collections import deque

nA, nB, E = list(map(int, input().split()))
G = [[] for _ in range(nA + nB)]
for _ in range(E):
    a, b = map(int, input().split())
    a -= 1; b -= 1
    G[a].append(b)
    G[b].append(a)

dist = [-1 for _ in range(nA + nB)]
def bfs(base):
    todo = deque([base])
    dist[base] = 0
    out = 0
    while len(todo) > 0:
        curr = todo.popleft()
        # visit everything adjacent to curr.
        for o in G[curr]:
            if dist[o] != -1: continue
            dist[o] = dist[curr] + 1
            todo.append(o)
            out = max(out, dist[o])
    return out

out = bfs(0) + bfs(nA + nB - 1) + 1
print(out)