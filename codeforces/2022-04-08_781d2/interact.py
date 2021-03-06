#region  load template's helpers
import sys
sys.path.append("/home/dcclyde/puzzles/code/templates")
from template import *
#endregion
#region  output
def ps(*args, **kwargs):
    if hasattr(args[0], '__iter__'):
        print(' '.join(str(x) for x in args[0]), **kwargs)
    else:
        print(' '.join(str(x) for x in args), **kwargs)

def pv(q): ps(*q)
def ps1(*args, **kwargs):
    if hasattr(args[0], '__iter__'):
        print(' '.join(str(x+1) for x in args[0]), **kwargs)
    else:
        print(' '.join(str(x+1) for x in args), **kwargs)
def pv1(q): ps1(*q)
def pvn(q):
    for x in q: ps(x)
def pvn1(q):
    for x in q: ps1(x)
#endregion
import random
#region  ri, rv
def ri(q):
    if isinstance(q, int):
        q = (q,q)
    return random.randint(q[0], q[1])

def rv(q, n):
    N = ri(n)
    return [ri(q) for _ in range(N)]
#endregion
#region  rgraph
def rgraph(nr, er, mute=False):
    N = ri(nr)
    E = ri(er)
    E = min(E, N*(N-1)//2)
    edge_options = [(a, b) for a in range(N) for b in range(a+1, N)]
    edges = random.sample(edge_options, E)

    if not mute:
        print(N, E)
        pvn1(edges)
    return N, E, edges
#endregion
#region  rtree
#region  DSU
class DSU:
    def __init__(self, _N):
        self.N = _N
        self.e = [-1] * self.N
    def get(self, x):
        if self.e[x] < 0:
            return x
        self.e[x] = self.e[self.e[x]]
        return self.e[x]
    def sameSet(self, a,b): return self.get(a) == self.get(b)
    def size(self, x): return -self.e[self.get(x)]
    def unite(self, x, y):
        x = self.get(x); y = self.get(y)
        if (x == y): return False
        if (self.e[x] > self.e[y]): x,y = y,x
        self.e[x] += self.e[y]
        self.e[y] = x
        return True
#endregion
def rtree(nr, mute=False):
    N = ri(nr)
    edges = []
    for a in range(1, N):
        b = ri((0, a-1))
        edges.append([a,b])
        random.shuffle(edges[-1])

    perm = list(range(N))
    random.shuffle(perm)
    edges = [[perm[x] for x in q] for q in edges]
    if not mute:
        print(N)
        pvn1(edges)
    return N, edges
#endregion
#region  rtree_rooted
def rtree_rooted(nr, mute=False):
    N, edges = rtree(nr, mute=True)
    G = [[] for _ in range(N)]
    for a, b in edges:
        G[a].append(b)
        G[b].append(a)
    root = 0
    parents = [-2] * N
    parents[root] = -1
    # traverse.
    todo = [root]
    while len(todo) > 0:
        curr = todo.pop()
        for o in G[curr]:
            if parents[o] == -2:
                parents[o] = curr
                todo.append(o)

    parents = parents[1:]
    if not mute:
        print(N)
        pv1(parents)
    return N, parents

def rtree_rooted_v2(nr, mute=False):
    # this version assumes v's parent will have an index < v.
    N = ri(nr)
    parents = [ri((0, k)) for k in range(N-1)]
    if not mute:
        print(N)
        pv1(parents)
    return N, parents
#endregion

N_RANGE = (2, 8)
V_RANGE = (1, 8)
S_RANGE = (1, 50)

def gen_test():
    # rtree_rooted_v2(N_RANGE)
    # rgraph(N_RANGE, S_RANGE)
    # rv(N_RANGE, LR_RANGE)
    N = ri(N_RANGE)
    # dat = [rv(V_RANGE, 2) for _ in range(N)]
    dat = rv(V_RANGE, N)
    ps(1)
    ps(N)
    pvn(dat)

# ! If it passes small random tests then the problem is likely overflow.
# gen_test()

def gcd(a, b):
    if a == 0: return b
    return gcd(b%a, a)

print(1, flush=True)
BIG = 10**9
x = ri((1, BIG))
questions_allowed = 30
while True:
    line = input().split()
    dbgcR("got", line)
    if line[0] == '!':
        if int(line[1]) == x:
            dbgcR("good", x)
            sys.exit(0)
        else:
            dbgcR("bad", x, int(line[1]))
            sys.exit(1)
    else:
        questions_allowed -= 1
        if questions_allowed < 0:
            dbgc("too many ?s", x)
            sys.exit(1)
        a = int(line[1])
        b = int(line[2])
        if (a == b or a < 0 or b < 0 or a > 2*BIG or b > 2*BIG):
            dbgcY("invalid guess", x, (a, b))
            sys.exit(1)
        g = gcd(x+a, x+b)
        print(g, flush=True)


