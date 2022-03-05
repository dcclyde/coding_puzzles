
class SegmentTree(object):
    def __init__(self, dat, op, default_val):
        '''
        op is an associative binary function (e.g. max, min, sum)
        default_val is "op applied to an empty set" (e.g. -3e9, 3e9, 0)
        '''
        self.N = len(dat)
        self.op = op
        self.default_val = default_val
        self.tree = [default_val] * self.N + dat
        for i in range(self.N - 1, 0, -1):
            self.tree[i] = self.op(self.tree[i<<1], self.tree[i<<1|1])

    def update(self, i, val):
        n = self.N + i
        self.tree[n] = val
        while n > 1:
            params = (n, n^1) if n&1 == 0 else (n^1, n)
            self.tree[n>>1] = self.op(self.tree[params[0]], self.tree[params[1]])
            n >>= 1


    def aggregate_range(self, i, j):
        m = self.N + i
        n = self.N + j
        res = self.default_val
        while m <= n:
            if m & 1:
                res = self.op(self.tree[m], res)
                m += 1
            m >>= 1
            if n & 1 == 0:
                res = self.op(res, self.tree[n])
                n -= 1
            n >>= 1
        return res
