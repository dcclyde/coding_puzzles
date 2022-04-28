
# Description: Disjoint Set Union with path compression
#     and union by size. Add edges and test connectivity.
#     Use for Kruskal's or Boruvka's minimum spanning tree.
# Time: O(inverse Ackermann function(N)). Just pretend it's O(1).
# Source: Benq's C++ library

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

# Kruskal's algorithm returns cost of Minimum Spanning Tree.
# Time: E*log(E)
def kruskal(N, edges):
    sort(edges)
    out = 0
    D = DSU()
    D.init(N)  # edges that unite are in MST
    for (weight, verts) in edges:
        a, b = verts
        if D.unite(a, b): out += weight
    return out
