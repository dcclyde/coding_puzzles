import os,sys;from io import BytesIO, IOBase
BUFSIZE = 8192
class FastIO(IOBase):
    newlines = 0
    def __init__(self, file):
        self._fd = file.fileno();self.buffer = BytesIO();self.writable = "x" in file.mode or "r" not in file.mode;self.write = self.buffer.write if self.writable else None
    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:break
            ptr = self.buffer.tell();self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()
    def readline(self):
        while self.newlines == 0:b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE));self.newlines = b.count(b"\n") + (not b);ptr = self.buffer.tell();self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()
    def flush(self):
        if self.writable:os.write(self._fd, self.buffer.getvalue());self.buffer.truncate(0), self.buffer.seek(0)
class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file);self.flush = self.buffer.flush;self.writable = self.buffer.writable;self.write = lambda s: self.buffer.write(s.encode("ascii"));self.read = lambda: self.buffer.read().decode("ascii");self.readline = lambda: self.buffer.readline().decode("ascii")
sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
try:sys.stdin,sys.stdout=open('in.txt','r'),open('out.txt','w')
except:pass
ii1=lambda:int(sys.stdin.readline().strip()) # for interger
is1=lambda:sys.stdin.readline().strip() # for str
iia=lambda:list(map(int,sys.stdin.readline().strip().split())) # for List[int]
isa=lambda:sys.stdin.readline().strip().split() # for List[str]
mod=int(1e9 + 7);
from math import inf
from collections import defaultdict as dd

def nn():
    return int(input())

def li():
    return list(input())

def lm():
    return list(map(int, input().split()))

# Snippet for printing while flushing output for interactive problems:
# In python3: print(x, flush=True)
# in python2: print(x) and then sys.stdout.flush()



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
        res_left = self.default_val
        res_right = self.default_val
        while m <= n:
            if m & 1:
                res_left = self.op(res_left, self.tree[m])
                m += 1
            m >>= 1
            if n & 1 == 0:
                res_right = self.op(self.tree[n], res_right)
                n -= 1
            n >>= 1
        return self.op(res_left, res_right)




#########################################################################
# Problem specific code usually goes below this line.
#########################################################################

'''
I'm copying off the following tutorial:

We will support the segments tree. At each vertex will be stored:
av — the maximum length of the bracket subsequence
bv — how many there it open brackets that sequence doesn't contain
cv — how many there it closed brackets that sequence doesn't contain
If we want to combine two vertices with parameters (a1, b1, c1) and (a2, b2, c2), we can use the following rules:
t = min(b1, c2)
a = a1 + a2 + t
b = b1 + b2 - t
c = c1 + c2 - t
'''

dat = input().strip()

# Now build the segtree.
# First, need to build the 1-node versions.
segtree_input = [
    (0, 1, 0) if dat[k] == '(' else (0, 0, 1)
    for k in range(len(dat))
]
def custom_op(x, y):
    t = min(x[1], y[2])
    out = (
        x[0] + y[0] + t,
        x[1] + y[1] - t,
        x[2] + y[2] - t,
    )
    return (
        x[0] + y[0] + t,
        x[1] + y[1] - t,
        x[2] + y[2] - t,
    )

segtree = SegmentTree(
    dat=segtree_input,
    op=custom_op,
    default_val=(0, 0, 0),
)

def process_query(L, R):
    A, B, C = segtree.aggregate_range(L - 1, R - 1)
    return A * 2


num_queries = nn()
out = []
for _ in range(num_queries):
    L, R = lm()
    out.append(str(process_query(L, R)))

print('\n'.join(out))
