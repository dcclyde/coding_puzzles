#region imports
import copy
from collections import defaultdict as dd
from collections import deque
import math
import sys
import os
import random
import time
#endregion
#region  @bootstrap for recursive functions
# # TLDR:
# # Python's recursion limit is 1000. Increasing the limit often causes MLE.
# # Instead, use this decorator. See https://codeforces.com/blog/entry/80158?#comment-662204.
# # Usage instructions:
# #   1) Put @bootstrap 1 line before the recursive function.
# #   2) Replace "return" with "yield"
# #   3) You also need to wrap your recursive calls like (yield myfunction(x)).
# #          (applies even if the function doesn't return anything!)
#            (only do this for recursive calls within the recursive function though!)
# # Example (original version):
# def f(n):
#     if n <= 0: yield 1
#     return f(n-1) + f(n-2)
#
# print(f(5))
#
# # Example (fixed):
# @bootstrap
# def f(n):
#     if n <= 0: return 1
#     yield (yield f(n-1)) + (yield f(n-2))
#
# print(f(5))  # don't add `yield` to the call from outside!
#
# Extended example:
#     Before: https://pastebin.com/inwciZgh
#     After: https://pastebin.com/fKksXXLj
#     Try submitting at: https://codingcompetitions.withgoogle.com/codejam/round/0000000000876ff1/0000000000a45ef7

from types import GeneratorType
def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to
    return wrappedfunc
#endregion
#region  dbg commands
# remember .bashrc should contain `export PYTHON_CONTEST_HELPER="dummy"`

local_run = False
def dbg(*args, **kwargs): pass
def dbgG(*args, **kwargs): pass
def dbgP(*args, **kwargs): pass
def dbgY(*args, **kwargs): pass
def dbgR(*args, **kwargs): pass
def dbgB(*args, **kwargs): pass
def dbgW(*args, **kwargs): pass
def dbgBackground(*args, **kwargs): pass
def dbgc(*args, **kwargs): pass
def dbgcG(*args, **kwargs): pass
def dbgcP(*args, **kwargs): pass
def dbgcY(*args, **kwargs): pass
def dbgcR(*args, **kwargs): pass
def dbgcB(*args, **kwargs): pass
def dbgcW(*args, **kwargs): pass
def dbgcBackground(*args, **kwargs): pass
def el(n=1): pass
def print_details_helper(*args, **kwargs): pass
def print_tsv_helper(*args, **kwargs): pass
def pdh(*args, **kwargs): pass
def pth(*args, **kwargs): pass
# if os.environ.get("PYTHON_CONTEST_HELPER"):
if False:
    local_run = True

    # call like dbg(print_details_helper(stuff))
    # provides more detailed listing of complicated objects
    def print_details_helper(q):
        out = []
        for k, x in enumerate(q):
            out.append(f"\n\t{k}:\t{x}")
        return ''.join(out) + '\n'

    pdh = print_details_helper  # alternate shorter name

    # good if we want to see spacing, or to copy-paste into GSheets
    def print_tsv_helper(q):
        out = []
        for row in q:
            out.append('\t'.join(str(x) for x in row))
        return ''.join('\n\t' + x for x in out) + '\n'

    pth = print_tsv_helper

    OUT_RED_BOLD = "\033[31;1m"
    OUT_GREEN = "\033[32m"
    OUT_RESET = "\033[0m"
    OUT_BOLD = "\033[;1m"
    OUT_RED = "\033[31m"
    OUT_WHITE = "\033[97m"
    OUT_BLUE = "\033[34;1m"
    OUT_CYAN = "\033[36;1m"
    OUT_PURPLE = "\033[35;1m"
    OUT_YELLOW = "\033[33;1m"
    OUT_BACKGROUND = "\033[41;30;1m"

    # helper function so your error printouts won't show up above an earlier stdout line.
    def flush_stdout():
        print('', flush=True, end='')

    def dbgBase(*args, **kwargs):
        flush_stdout()
        color_helper = kwargs.pop('color', OUT_CYAN)
        if kwargs.get('comment_first', False):
            print(f'{OUT_BOLD}{color_helper}{args[0]: >11} {OUT_RESET}', end='', file=sys.stderr)
            args = tuple(args[1:])
        else:
            print(f"{'': >12}", end='', file=sys.stderr)
        if 'comment_first' in kwargs:
            del kwargs['comment_first']
        print(f"{OUT_RED_BOLD}{sys._getframe().f_back.f_back.f_lineno: >7} {OUT_BOLD}:  {OUT_RESET}{color_helper}", end='', file=sys.stderr)
        end_maybe = kwargs.get('end', '\n')
        kwargs['end']=f"{OUT_RESET}{end_maybe}"
        if 'sep' not in kwargs:
            kwargs['sep'] = ' '*3
        kwargs['flush'] = True
        print(*args, file=sys.stderr, **kwargs)

    # Can always comment out some of these lines to disable those logs.
    # e.g. if you make lots of messy printouts while finding bug #1 but now it's fixed but you still want SOME printouts.
    def dbg(*args, **kwargs): dbgBase(color=OUT_CYAN, *args, **kwargs)
    def dbgG(*args, **kwargs): dbgBase(color=OUT_GREEN, *args, **kwargs)
    def dbgP(*args, **kwargs): dbgBase(color=OUT_PURPLE, *args, **kwargs)
    def dbgY(*args, **kwargs): dbgBase(color=OUT_YELLOW, *args, **kwargs)
    def dbgR(*args, **kwargs): dbgBase(color=OUT_RED, *args, **kwargs)
    def dbgB(*args, **kwargs): dbgBase(color=OUT_BLUE, *args, **kwargs)
    def dbgW(*args, **kwargs): dbgBase(color=OUT_WHITE, *args, **kwargs)
    def dbgBackground(*args, **kwargs): dbgBase(color=OUT_BACKGROUND, *args, **kwargs)
    def el(n=1): flush_stdout(); print('\n'*n, file=sys.stderr, end='', flush=True)
    def dbgc(*args, **kwargs): dbgBase(comment_first=True, color=OUT_CYAN, *args, **kwargs)
    def dbgcG(*args, **kwargs): dbgBase(comment_first=True, color=OUT_GREEN, *args, **kwargs)
    def dbgcP(*args, **kwargs): dbgBase(comment_first=True, color=OUT_PURPLE, *args, **kwargs)
    def dbgcY(*args, **kwargs): dbgBase(comment_first=True, color=OUT_YELLOW, *args, **kwargs)
    def dbgcR(*args, **kwargs): dbgBase(comment_first=True, color=OUT_RED, *args, **kwargs)
    def dbgcB(*args, **kwargs): dbgBase(comment_first=True, color=OUT_BLUE, *args, **kwargs)
    def dbgcW(*args, **kwargs): dbgBase(comment_first=True, color=OUT_WHITE, *args, **kwargs)
    def dbgcBackground(*args, **kwargs): dbgBase(comment_first=True, color=OUT_BACKGROUND, *args, **kwargs)
#endregion
#region  FastIO
from io import BytesIO, IOBase

# BUFSIZE = 8192


# class FastIO(IOBase):
#     newlines = 0

#     def __init__(self, file):
#         self._fd = file.fileno()
#         self.buffer = BytesIO()
#         self.writable = "x" in file.mode or "r" not in file.mode
#         self.write = self.buffer.write if self.writable else None

#     def read(self):
#         while True:
#             b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
#             if not b:
#                 break
#             ptr = self.buffer.tell()
#             self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
#         self.newlines = 0
#         return self.buffer.read()

#     def readline(self):
#         while self.newlines == 0:
#             b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
#             self.newlines = b.count(b"\n") + (not b)
#             ptr = self.buffer.tell()
#             self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
#         self.newlines -= 1
#         return self.buffer.readline()

#     def flush(self):
#         if self.writable:
#             os.write(self._fd, self.buffer.getvalue())
#             self.buffer.truncate(0), self.buffer.seek(0)


# class IOWrapper(IOBase):
#     def __init__(self, file):
#         self.buffer = FastIO(file)
#         self.flush = self.buffer.flush
#         self.writable = self.buffer.writable
#         self.write = lambda s: self.buffer.write(s.encode("ascii"))
#         self.read = lambda: self.buffer.read().decode("ascii")
#         self.readline = lambda: self.buffer.readline().decode("ascii")


# sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
# input = lambda: sys.stdin.readline().rstrip("\r\n")
#endregion
#region  input helpers
def nn():
    return int(input())

def nn1():
    return nn() - 1

def li():
    return list(input())

def lm():
    return list(map(int, input().split()))

def lm1():
    return list(map(lambda x : int(x) - 1, input().split()))

rv = lm
rv1 = lm1

# To print while flushing output for interactive problems:
# print(x, flush=True)
#endregion
#region  output helpers
def ps(*args, **kwargs):
    if hasattr(args[0], '__iter__') and not isinstance(args[0], str):
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
#region  logic

EXECUTION_START_TIME = time.time()
def TIME():
    # return time.time() - EXECUTION_START_TIME
    return int((time.time() - EXECUTION_START_TIME) * 10**6) / 10**6

def YES(): return print("YES")
def NO(): return print("NO")
def Yes(): return print("Yes")
def No(): return print("No")

def remDup(v):
    v = list(set(v))

steps_orthogonal = [(1,0), (0,1), (-1,0), (0,-1)]
steps_diagonal = [(1,1), (1,-1), (-1,-1), (-1,1)]
steps_8dirs = [(-1,-1), (0,-1), (1,-1), (-1,0), (1,0), (-1,1), (0,1), (1,1)]

def fstTrue(lo, hi, f):
    hi += 1
    assert lo <= hi
    while lo < hi:
        mid = lo + (hi-lo) // 2
        if f(mid): hi = mid
        else: lo = mid + 1
    return lo

first_true = fstTrue

def lstTrue(lo, hi, f):
    lo -= 1
    assert lo <= hi
    while lo < hi:
        mid = lo + (hi-lo+1) // 2
        if f(mid): lo = mid
        else: hi = mid-1
    return lo

last_true = lstTrue

# "ceiling divide" and "floor divide"
def cdiv(a, b): return a//b + (1 if ((a^b)>0 and a%b != 0) else 0)
def fdiv(a, b): return a//b - (1 if ((a^b)<0 and a%b != 0) else 0)

def bits_set(x): return bin(x).count('1')
pct = bits_set
popcount = bits_set


#endregion



class LazySegmentTree:
    def __init__(self, data, padding = 0):
        """initialize the lazy segment tree with data"""
        self._len = len(data)
        self._size = _size = 1 << (self._len - 1).bit_length()

        self.data = [padding] * (2 * _size)
        self.data[_size:_size + self._len] = data
        for i in reversed(range(1, _size)):
            self.data[i] = self.data[2 * i] + self.data[2 * i + 1]
        self._lazy = [1,0] * (2 * _size)

    def _push(self, idx):
        """push query on idx to its children"""
        # Let the children know of the queries
        idx *= 2
        a = self._lazy[idx]
        b = self._lazy[idx + 1] >> 1
        self._lazy[idx] = 1
        self._lazy[idx + 1] = 0

        self.data[idx] = a * self.data[idx] + b
        self.data[idx + 1] = a * self.data[ idx + 1] + b

        idx *= 2
        self._lazy[idx] = a * self._lazy[idx]
        self._lazy[idx + 1] = a * self._lazy[idx + 1] + b
        self._lazy[idx + 2] = a * self._lazy[idx + 2]
        self._lazy[idx + 3] = a * self._lazy[idx + 3] + b

    def _build(self, idx):
        """make the changes to idx be known to its ancestors"""
        idx >>= 1
        while idx:
            # TODO
            self.data[idx] = self.data[2 * idx] + self.data[2 * idx + 1]
            idx >>= 1

    def _update(self, idx):
        """updates the node idx to know of all queries applied to it via its ancestors"""
        for i in reversed(range(1, idx.bit_length())):
            self._push(idx >> i)

    def add(self, start, stop, q):
        """lazily add value to [start, stop)"""
        (a, b) = q
        start = start_copy = start + self._size
        stop = stop_copy = stop + self._size

        # Apply all the lazily stored queries
        self._update(start); self._update(stop - 1)

        while start < stop:
            if start & 1:
                self.data[start] = a * self.data[start] + b
                self._lazy[2 * start] = a * self._lazy[2 * start]
                self._lazy[2 * start + 1] = a * self._lazy[2 * start + 1] + b
                start += 1
            if stop & 1:
                stop -= 1
                self.data[stop] = a * self.data[stop] + b
                self._lazy[2 * stop] = a * self._lazy[2 * stop]
                self._lazy[2 * stop + 1] = a * self._lazy[2 * stop + 1] + b
            start >>= 1; stop >>= 1; b <<= 1

        while not start_copy&1: start_copy >>= 1
        while not stop_copy&1: stop_copy >>= 1
        self._build(start_copy); self._build(stop_copy - 1)

    def query(self, start, stop, res = 0):
        """func of data[start, stop)"""
        start += self._size; stop += self._size

        # Apply all the lazily stored queries
        self._update(start); self._update(stop - 1)
        while start < stop:
            if start & 1:
                res += self.data[start]
                start += 1
            if stop & 1:
                stop -= 1
                res += self.data[stop]
            start >>= 1; stop >>= 1
        return res

class LazySeg:
    idSeg = 0  # ! seg identity, must satisfy a+idSeg = idSeg+a = a
    idLazy = [0,0]  # ! lazy identity, must satisfy idLazy * a = a
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
        # a, b = self.lazy[ind]
        # if a == 0: return
        # if a == 1: self.seg[ind] += (R-L+1) * b  # ! lazy * seg
        if self.lazy[ind][0] == 0: return
        if self.lazy[ind][0] == 1: self.seg[ind] += (R-L+1) * self.lazy[ind][1]
        else: self.seg[ind] = (R-L+1) * self.lazy[ind][1]  # ! lazy * seg
        if L != R:
            for i in range(2):
                # ca, cb = self.lazy[2*ind+i]
                '''
                    ca == 0: just use a, b.
                    ca == 1 and a == 1: sum them
                    ca == 1, a == 2: replace
                    ca == 2, a == 1: add onto existing set
                    ca == 2, a == 2: replace
                '''
                if self.lazy[2*ind+i][0] == 0 or self.lazy[ind][0] == 2:
                    self.lazy[2*ind+i] = self.lazy[ind]
                else:
                    self.lazy[2*ind+i][1] += self.lazy[ind][1]
                # if ca == 0 or a == 2: ca, cb = a, b
                # else: cb += b
                # self.lazy[2*ind+i] = (ca, cb)  # ! lazy * lazy

        self.lazy[ind] = self.idLazy

    def pull(self, ind): self.seg[ind] = self.cmb(self.seg[2*ind],self.seg[2*ind+1])
    def build(self):
        for k in reversed(range(1, self.n)): self.pull(k)

    # def push_all(self, ind=1, L=0, R=None):
    #     if R is None: R = self.n - 1
    #     self.push(ind,L,R)
    #     if L < R:
    #         M = (L+R)>>1
    #         self.push_all(2*ind,L,M)
    #         self.push_all(2*ind+1,M+1,R)

    def push_all(self):
        todo = [(1, 0, self.n-1)]
        while len(todo) > 0:
            ind, L, R = todo.pop()
            self.push(ind,L,R)
            if L < R:
                M = (L+R)>>1
                todo.append((2*ind,L,M))
                todo.append((2*ind+1,M+1,R))

    def upd(self, lo, hi, inc):
        todo = [(1, 0, self.n-1)]
        post = []
        while len(todo) > 0:
            ind, L, R = todo.pop()
            self.push(ind, L, R)
            if hi < L or R < lo: continue
            if lo <= L and R <= hi:
                self.lazy[ind] = inc
                self.push(ind,L,R)
                continue
            M = (L+R)>>1
            todo.append((2*ind,L,M))
            todo.append((2*ind+1,M+1,R))
            post.append(ind)
        for ind in reversed(post):
            self.pull(ind)

    def query(self, l, r):
        ra = self.idSeg
        rb = self.idSeg
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
        if not local_run: return ''  # if we call this then we lose all lazy benefits.
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


def main():
    inp = readnumbers()
    ii = 0

    n = inp[ii]
    ii += 1
    q = inp[ii]
    ii += 1

    X = inp[ii:ii+n]
    ii += n

    # seg = LazySegmentTree(X)
    seg = LazySeg()
    seg.init(n)
    for k, v in enumerate(X): seg.seg[seg.n+k] = v
    seg.build()
    dbg(seg)
    el()

    for _ in range(q):
        cas = inp[ii]
        ii += 1
        a = inp[ii] - 1
        ii += 1
        b = inp[ii]
        ii += 1

        if cas == 1:
            x = inp[ii]
            ii += 1
            dbgP(x)
            # seg.add(a, b, (1, x))
            seg.upd(a, b-1, [1, x])
        elif cas == 2:
            x = inp[ii]
            ii += 1
            # seg.add(a, b, (0,x))
            seg.upd(a, b-1, [2, x])
        else:
            # cout << seg.query(a,b) << '\n'
            cout << seg.query(a,b-1) << '\n'
        dbg(_,a,b-1,seg)

#region
######## Python 2 and 3 footer by Pajenegod and c1729

# Note because cf runs old PyPy3 version which doesn't have the sped up
# unicode strings, PyPy3 strings will many times be slower than pypy2.
# There is a way to get around this by using binary strings in PyPy3
# but its syntax is different which makes it kind of a mess to use.

# So on cf, use PyPy2 for best string performance.

py2 = round(0.5)
if py2:
    from future_builtins import ascii, filter, hex, map, oct, zip
    range = xrange

import os, sys
from io import IOBase, BytesIO

BUFSIZE = 8192
class FastIO(BytesIO):
    newlines = 0

    def __init__(self, file):
        self._file = file
        self._fd = file.fileno()
        self.writable = "x" in file.mode or "w" in file.mode
        self.write = super(FastIO, self).write if self.writable else None

    def _fill(self):
        s = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
        self.seek((self.tell(), self.seek(0,2), super(FastIO, self).write(s))[0])
        return s

    def read(self):
        while self._fill(): pass
        return super(FastIO,self).read()

    def readline(self):
        while self.newlines == 0:
            s = self._fill(); self.newlines = s.count(b"\n") + (not s)
        self.newlines -= 1
        return super(FastIO, self).readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.getvalue())
            self.truncate(0), self.seek(0)

class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        if py2:
            self.write = self.buffer.write
            self.read = self.buffer.read
            self.readline = self.buffer.readline
        else:
            self.write = lambda s:self.buffer.write(s.encode('ascii'))
            self.read = lambda:self.buffer.read().decode('ascii')
            self.readline = lambda:self.buffer.readline().decode('ascii')


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline()

# Cout implemented in Python
import sys
class ostream:
    def __lshift__(self,a):
        sys.stdout.write(str(a))
        return self
cout = ostream()
endl = '\n'

def readnumbers(zero=0):
    _ord = ord if round(0.5) else lambda x: x

    nums = []
    num, neg = zero, False
    i, s = 0, sys.stdin.buffer.read()
    try:
        while True:
            if s[i] >= b"0"[0]:
                num = 10 * num + _ord(s[i]) - 48
            elif s[i] == b"-"[0]:
                neg = True
            elif s[i] != b"\r"[0]:
                nums.append(-num if neg else num)
                num, neg = zero, False
            i += 1
    except IndexError:
        pass

    if s and s[-1] >= b"0"[0]:
        nums.append(-num if neg else num)
    return nums

if __name__== "__main__":
  main()
#endregion
