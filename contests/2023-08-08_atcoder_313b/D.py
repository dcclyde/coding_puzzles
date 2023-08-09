

N, K = tuple(map(int, input().split()))

guess = list(range(1, K+1))
queries_used = 0

def ask():
    global queries_used
    queries_used += 1
    print('? ' + ' '.join(map(str, guess)), flush=True)
    out = int(input())
    return out

start = ask()
edges = []

# edges from initial stuff to N
for k in range(1, K+1):
    guess[k-1] = N
    curr = ask()
    edges.append((k, N, curr ^ start))
    guess[k-1] = k

# edges to stuff outside original guess
for j in range(K+1, N):
    guess[K-1] = j
    curr = ask()
    edges.append((K, j, curr ^ start))
    guess[K-1] = K

# print the edges to stderr.
import sys
# print(edges, file=sys.stderr)

G = [[] for _ in range(N+1)]
for a, b, x in edges:
    G[a].append((b, x))
    G[b].append((a, x))

# print(G, file=sys.stderr)

assert(queries_used == N)

# build hypothetical colors.
colors = [-1 for _ in range(N+1)]
colors[1] = 0
todo = [1]
while len(todo) > 0:
    curr = todo.pop()
    for nxt, x in G[curr]:
        if colors[nxt] == -1:
            colors[nxt] = colors[curr] ^ x
            todo.append(nxt)

colors = colors[1:]

# check if this coloring is correct vs opposite.
start_hypothetical = 0
for k in range(K):
    start_hypothetical ^= colors[k]

if start_hypothetical != start:
    colors = [c ^ 1 for c in colors]

print('!', ' '.join(map(str, colors)), flush=True)
