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
def ps1(*args, **kwargs): alocal = tuple(tuple(x+1 for x in q) for q in args); ps(*alocal, **kwargs)
def pv1(q): ps1(*q)
def pvn(q):
    for x in q: ps(x)
def pvn1(q):
    for x in q: ps1(x)
#endregion
#region  randomness helpers
import random
#region  ints, lists
def ri(q):
    if isinstance(q, int):
        q = (q,q)
    return random.randint(q[0], q[1])

def rv(q, n):
    N = ri(n)
    return [ri(q) for _ in range(N)]
#endregion
#region  rgraph
def rgraph(nr, er):
    N = ri(nr)
    E = ri(er)
    E = min(E, N*(N-1)//2)
    edge_options = [(a, b) for a in range(N) for b in range(a+1, N)]
    edges = random.sample(edge_options, E)

    print(N, E)
    pvn1(edges)
    return
#endregion
#region  rtree
#region  DSU (for tree)
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

def rtree(nr):
    N = ri(nr)
    dsu = DSU(N)
    edges = []
    for _ in range(N-1):
        while True:
            a, b = rv((0,N-1), 2)
            if dsu.unite(a, b):
                break
        edges.append((a,b))
    print(N)
    pvn1(edges)
    return
#endregion
#endregion

# N_RANGE = (1, 100)
# V_RANGE = (1, 5)

# def gen_test():
#     N = ri(N_RANGE)
#     K = ri((1, N))
#     dat = rv(V_RANGE, N)
#     ps(N, K)
#     pv(dat)

N_RANGE = (1, 10)
XY_RANGE = (1, 100)

def gen_test():
    N = ri(N_RANGE)
    dat = [rv(XY_RANGE, 2) for _ in range(N)]
    ps(1)
    ps(N)
    pvn(dat)

gen_test()
