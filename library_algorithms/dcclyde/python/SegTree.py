
class SegTree:
    ID = 0  # ! identity
    def cmb(self, a, b):  # ! seg * seg
        return a+b
    def init(self, _n):
        self.orig_n = _n
        self.n = 1
        while self.n < _n:
            self.n *= 2
        self.seg = [self.ID for _ in range(2*self.n)]

    def pull(self, p):
        self.seg[p] = self.cmb(self.seg[2*p], self.seg[2*p+1])

    def build(self):
        for k in reversed(range(1, self.n)): self.pull(k)

    def upd(self, p, val):  # set val at position p
        p += self.n
        self.seg[p] = val
        p >>= 1
        while p != 0:
            self.pull(p)
            p >>= 1

    def query(self, l, r):  # query the CLOSED range [l, r].
        if r < l: return self.ID
        ra = self.ID
        rb = self.ID
        l += self.n
        r += self.n+1
        while l < r:
            if l&1:
                ra = self.cmb(ra, self.seg[l])
                l += 1
            if r&1:
                r -= 1
                rb = self.cmb(self.seg[r], rb)
            l >>= 1
            r >>= 1
        return self.cmb(ra, rb)

    # return smallest x s.t. query(base, x) satisfies some criterion.
    def first_satisfying_R(self, base, val, ind=1, l=0, r=None):
        if r is None: r = self.n - 1
        can_look_sideways = False
        while True:
            # ! Is there a good idx in [l, r]?
            ok = (self.seg[ind] >= val)
            if r < base or not ok:
                if not can_look_sideways: return -1
                d = r-l+1
                l, r, ind = l+d, r+d, ind+1
                # ! May need to modify `base`, e.g. if we're targeting sum >= S.
                continue
            if l == r: return l
            m = (l+r) // 2
            l, r, ind, can_look_sideways = l, m, 2*ind, True

    # return largest x s.t. query(x, base) satisfies some criterion.
    def first_satisfying_L(self, base, val, ind=1, l=0, r=None):
        if r is None: r = self.n - 1
        can_look_sideways = False
        while True:
            # ! Is there a good idx in [l, r]?
            ok = (self.seg[ind] >= val)
            if l > base or not ok:
                if not can_look_sideways: return -1
                d = r-l+1
                l, r, ind = l-d, r-d, ind-1
                # ! May need to modify `base`, e.g. if we're targeting sum >= S.
                continue
            if l == r: return l
            m = (l+r) // 2
            l, r, ind, can_look_sideways = m+1, r, 2*ind+1, True

    def __str__(self):  # make the class nicely printable, including via dbg()
        if not local_run: return ''
        out = [self.seg[k] for k in range(self.n, self.n + self.orig_n)]
        return str(out)

    def detailed_printouts(self):
        #region
        if not local_run: return  # this function is expensive.
        ST_SIZE = self.n
        ST_PRINT_SIZE = self.orig_n
        el()
        dbgc("ST DETAILS")
        for k in range(1, ST_SIZE + ST_PRINT_SIZE):
            if k >= ST_SIZE:
                p = k - ST_SIZE
                dbgP(k, p, self.seg[k])
            else:
                binary_digits = bin(k)[2:]
                l = 0
                r = ST_SIZE - 1
                for d in binary_digits:
                    m = (l+r) // 2
                    if d == '1': l = m+1
                    else: r = m
                if l < ST_PRINT_SIZE:
                    dbgY(k, (l,r), self.seg[k])
        el()
        #endregion

#region  validation slash baby example
# def validate_SegTree():
#     N = 5
#     dat = [1, 6, 7, 4, 2]
#     st = SegTree()
#     st.init(N)
#     for k in range(len(dat)):
#         st.upd(k, dat[k])
#     dbgY(st)
#     q = st.query(0, 2)
#     el()
#     dbg(q)
#     assert q == 14
#     st.upd(2, 5)
#     q = st.query(0, 2)
#     dbg(q)
#     assert q == 12
#     st.detailed_printouts()
#     return
#endregion
