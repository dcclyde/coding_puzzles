#region  load template's helpers
import sys
sys.path.append("/home/dcclyde/puzzles/code/templates")
from template import *
#endregion
#region  block all buffering (don't want this in submittable solutions!)
import functools
print = functools.partial(print, flush=True)  # including this in debug_only section of template.py could cause server-only bugs.
ps = functools.partial(ps, flush=True)  # including this in debug_only section of template.py could cause server-only bugs.
#endregion
#region  ri, rv
def ri(q, b=None):
    if isinstance(b, int):
        q = (q, b)
    elif isinstance(q, int):
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


N_RANGE = (6, 10)

def gcd(a, b):
    if b == 0: return a
    return gcd(b, a % b)

def interact():
    ps(1)

    N = ri(N_RANGE)
    dat = list(range(N))
    random.shuffle(dat)
    for k in range(N):
        if dat[k] == 0: answer = k

    dbgR(answer, dat)
    ps(N)

    queries_allowed = 2*N
    while True:
        raw = input().split()
        # dbgP(raw)
        qtype = raw[0]
        a = int(raw[1]) - 1
        b = int(raw[2]) - 1
        if qtype == '!':
            if answer == a or answer == b:
                dbgc("! good", a, b, answer)
                ps(1)
                print(1)
                sys.exit(0)
            else:
                dbgcR("! bad", a, b, answer)
                ps(-1)
                print(-1)
                sys.exit(1)
        else:
            queries_allowed -= 1
            if queries_allowed < 0:
                dbgcR("too many queries", query)
                sys.exit(1)
            else:
                ps(gcd(dat[a], dat[b]))


# ! IF RANDOM TESTS PASS:
# !   * OVERFLOW! Remember pii, FOR, maxi/mini, INF Write an "overflow gen"?
# !   * RECODE FROM SCRATCH? Maybe in Python?
# !   * Misunderstanding the problem rules?
# !   * Brute force wrong - is it sufficiently different?
# !   * Edge case not buildable in brute forceable inputs (or needs mid size AND pathological)
#region  past mistakes
# * Uninitialized variable
# * I used INF = 1e9 but answer could be bigger
#endregion
interact()
