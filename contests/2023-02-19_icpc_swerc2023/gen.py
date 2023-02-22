#region  load template's helpers
import sys
sys.path.append("/home/dcclyde/puzzles/code/templates")
from template import *
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


# N_RANGE = (0, 10**5)
# V_RANGE = (0, 10**4)

N_RANGE = (4, 5)
COORD_RANGE = (-1, 1)

def random_convex_poly(nrange, coord_range, mute=False):
    # generate the sides.
    N = ri(nrange)
    coords = rv(coord_range, 2*(N-1))
    # dbg(coords)
    vectors = [(coords[k], coords[2*k+1]) for k in range(len(coords)//2)]
    leftover = [0, 0]
    for k in range(len(vectors)):
        while (vectors[k] == (0,0)):
            vectors[k] = (ri(COORD_RANGE), ri(COORD_RANGE))
        for j in range(2): leftover[j] -= vectors[k][j]
    vectors.append(tuple(leftover))

    vectors.sort(key=lambda q: math.atan2(q[1], q[0]))
    dbgY(vectors)

    verts = [(0, 0)]
    for x, y in vectors:
        verts.append((verts[-1][0]+x, verts[-1][1]+y))
    verts.pop()
    dbgR(verts)

    if not mute:
        ps(N)
        pvn(verts)

# make a random polygon.
def gen_test():
    random_convex_poly(N_RANGE, COORD_RANGE)


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
gen_test()
