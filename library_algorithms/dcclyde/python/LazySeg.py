#region  usage suggestions
'''
If you need two segtrees with different operations, just paste the whole template twice and rename one of the classes.
Usually you don't need that though, you can just make one segtree store multiple pieces of data by making seg[k] a tuple.
'''
#endregion

class LazySeg:
    idSeg = 0  # ! seg identity, must satisfy a+idSeg = idSeg+a = a
    idLazy = 0  # ! lazy identity, must satisfy idLazy * a = a
    def cmb(self, a, b):  # ! seg * seg
        return a + b
    def init(self, _n):
        self.orig_n = _n
        self.n = 1
        while self.n < _n: self.n *= 2
        self.SZ = self.n
        self.seg = [self.idSeg for _ in range(2*self.n)]
        self.lazy = [self.idLazy for _ in range(2*self.n)]

    def push(self, ind, L, R):
        self.seg[ind] += (R-L+1) * self.lazy[ind]  # ! lazy * seg
        if L != R:
            for i in range(2):
                self.lazy[2*ind+i] += self.lazy[ind]
        self.lazy[ind] = self.idLazy

    def pull(self, ind): self.seg[ind] = self.cmb(self.seg[2*ind],self.seg[2*ind+1])
    def build(self):
        for k in reversed(range(1, self.n)): self.pull(k)

    def push_all(self, ind=1, L=0, R=None):
        if R is None: R = self.n - 1
        self.push(ind,L,R)
        if L < R:
            M = (L+R)>>1
            self.push_all(2*ind,L,M)
            self.push_all(2*ind+1,M+1,R)

    def upd(self, lo, hi, inc, ind=1, L=0, R=None):
        if R is None: R = self.n - 1
        self.push(ind,L,R)
        if hi < L or R < lo: return
        if lo <= L and R <= hi:
            self.lazy[ind] = inc
            self.push(ind,L,R)
            return
        M = (L+R)>>1
        self.upd(lo,hi,inc,2*ind,L,M)
        self.upd(lo,hi,inc,2*ind+1,M+1,R)
        self.pull(ind)

    def query(self, lo, hi, ind=1, L=0, R=None):
        if R is None: R = self.n - 1
        self.push(ind,L,R)
        if hi < L or R < lo: return self.idSeg
        if lo <= L and R <= hi: return self.seg[ind]
        M = (L+R)>>1
        return self.cmb(
            self.query(lo,hi,2*ind,L,M),
            self.query(lo,hi,2*ind+1,M+1,R)
        )

    # return smallest x s.t. query(base, x) satisfies some criterion.
    def first_satisfying_R(self, base, val, ind=1, l=0, r=None):
        if r is None: r = self.n - 1
        # ! Is there a good idx in [l, r]?
        ok = (self.query(l,r,ind,l,r) >= val)
        if r < base or not ok: return -1
        if l == r: return l
        m = (l+r) // 2
        res = self.first_satisfying_R(base,val,2*ind,l,m)
        if res != -1: return res
        return self.first_satisfying_R(base,val,2*ind+1,m+1,r)

    # return largest x s.t. query(x, base) satisfies some criterion.
    def first_satisfying_L(self, base, val, ind=1, l=0, r=None):
        if r is None: r = self.n - 1
        # ! Is there a good idx in [l, r]?
        ok = (self.query(l,r,ind,l,r) >= val)
        if l > base or not ok: return -1
        if l == r: return l
        m = (l+r) // 2
        res = self.first_satisfying_R(base,val,2*ind+1,m+1,r)
        if res != -1: return res
        return self.first_satisfying_R(base,val,2*ind,l,m)

    def __str__(self):  # make the class nicely printable, including via dbg()
        self.push_all()  # get rid of all laziness.
        out = [self.seg[k] for k in range(self.n, self.n + self.orig_n)]
        return str(out)

    def detailed_printouts(self):
        #region
        if not local_run: return  # this function is expensive.
        ST_SIZE = self.n
        ST_PRINT_SIZE = self.orig_n
        el()
        dbgc("LazySeg DETAILS")
        for k in range(1, ST_SIZE + ST_PRINT_SIZE):
            if k >= ST_SIZE:
                p = k - ST_SIZE
                dbgP(k, p, self.seg[k], self.lazy[k])
            else:
                binary_digits = bin(k)[2:]
                l = 0
                r = ST_SIZE - 1
                for d in binary_digits:
                    m = (l+r) // 2
                    if d == '1': l = m+1
                    else: r = m
                if l < ST_PRINT_SIZE:
                    dbgY(k, (l,r), self.seg[k], self.lazy[k])
        el()
        #endregion

#region  validation slash baby example
# def validate_LazySeg():
#     N = 5
#     dat = [1, 6, 7, 4, 2]
#     st = LazySeg()
#     st.init(N)
#     for k in range(len(dat)):
#         st.seg[st.n + k] = dat[k]  # set node values without updating the tree
#     st.build()  # now update the tree.
#     el()
#     q = st.query(0, 2)
#     dbg(q, st)
#     assert q == 14

#     st.upd(1, 4, 10)  # now holds [1, 16, 17, 14, 12]
#     q = st.query(0, 4)
#     dbg(q, st)
#     assert q == 60
#     st.detailed_printouts()
#     return
#endregion
