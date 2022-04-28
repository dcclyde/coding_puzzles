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

BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")
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

#########################################################################
# Problem specific code usually goes below this line.
#########################################################################

'''
lazy = (a, b).
a denotes update type, b denotes parameter
a=0: identity, don't do anything
a=1: increase range by b
a=2: set range to b
'''

# class LazySeg:
n = -1
orig_n = -1
seg = None
lazy = None
idSeg = 0  # ! seg identity, must satisfy a+idSeg = idSeg+a = a
idLazy = (0,0)  # ! lazy identity, must satisfy idLazy * a = a
def cmb(a, b):  # ! seg * seg
    return a + b
def init(_n):
    global orig_n
    global n
    global seg
    global lazy
    global SZ
    orig_n = _n
    n = 1
    while n < _n: n *= 2
    SZ = n
    seg = [idSeg for _ in range(2*n)]
    lazy = [idLazy for _ in range(2*n)]

def push(ind, L, R):
    global seg
    global lazy
    a, b = lazy[ind]
    if a == 0: return
    if a == 1: seg[ind] += (R-L+1) * b  # ! lazy * seg
    else: seg[ind] = (R-L+1) * b  # ! lazy * seg
    if L != R:
        for i in range(2):
            ca, cb = lazy[2*ind+i]
            '''
                ca == 0: just use a, b.
                ca == 1 and a == 1: sum them
                ca == 1, a == 2: replace
                ca == 2, a == 1: add onto existing set
                ca == 2, a == 2: replace
            '''
            if ca == 0 or a == 2: ca, cb = a, b
            else: cb += b
            lazy[2*ind+i] = (ca, cb)  # ! lazy * lazy

    lazy[ind] = idLazy

def pull(ind):
    global seg
    seg[ind] = cmb(seg[2*ind],seg[2*ind+1])
def build():
    for k in reversed(range(1, n)): pull(k)
    for k in range(1, 2*n): assert lazy[k] == idLazy

def push_all():
    todo = [(1, 0, n-1)]
    while len(todo) > 0:
        ind, L, R = todo.pop()
        push(ind,L,R)
        if L < R:
            M = (L+R)>>1
            todo.append((2*ind,L,M))
            todo.append((2*ind+1,M+1,R))

def upd(lo, hi, inc):
    global seg
    global lazy
    todo = [(1, 0, n-1)]
    post = []
    while len(todo) > 0:
        ind, L, R = todo.pop()
        push(ind, L, R)
        if hi < L or R < lo: continue
        if lo <= L and R <= hi:
            lazy[ind] = inc
            push(ind,L,R)
            continue
        M = (L+R)>>1
        todo.append((2*ind,L,M))
        todo.append((2*ind+1,M+1,R))
        post.append(ind)
    for ind in reversed(post):
        pull(ind)

def query(l, r):
    ra = idSeg
    rb = idSeg
    l += n
    r += n+1
    while l < r:
        if l&1:
            ra = cmb(ra, seg[l])
            l += 1
        if r&1:
            r -= 1
            rb = cmb(seg[r], rb)
        l >>= 1
        r >>= 1
    return cmb(ra, rb)

# return smallest x s.t. query(base, x) satisfies some criterion.
def first_satisfying_R(base, val, ind=1, l=0, r=None):
    if r is None: r = n - 1
    # ! Is there a good idx in [l, r]?
    ok = (query(l,r,ind,l,r) >= val)
    if r < base or not ok: return -1
    if l == r: return l
    m = (l+r) // 2
    res = first_satisfying_R(base,val,2*ind,l,m)
    if res != -1: return res
    return first_satisfying_R(base,val,2*ind+1,m+1,r)

# return largest x s.t. query(x, base) satisfies some criterion.
def first_satisfying_L(base, val, ind=1, l=0, r=None):
    if r is None: r = n - 1
    # ! Is there a good idx in [l, r]?
    ok = (query(l,r,ind,l,r) >= val)
    if l > base or not ok: return -1
    if l == r: return l
    m = (l+r) // 2
    res = first_satisfying_R(base,val,2*ind+1,m+1,r)
    if res != -1: return res
    return first_satisfying_R(base,val,2*ind,l,m)

def to_string():
    if not local_run: return  # if we call this then we lose all lazy benefits.
    push_all()  # get rid of all laziness.
    out = [seg[k] for k in range(n, n + orig_n)]
    return str(out)

def detailed_printouts():
    #region
    if not local_run: return  # this function is expensive.
    ST_SIZE = n
    ST_PRINT_SIZE = orig_n
    dbg(ST_SIZE)
    dbg(ST_PRINT_SIZE)
    el()
    dbgc("LazySeg DETAILS")
    for k in range(1, ST_SIZE + ST_PRINT_SIZE):
        if k >= ST_SIZE:
            p = k - ST_SIZE
            dbgP(k, p, seg[k], lazy[k])
        else:
            binary_digits = bin(k)[2:]
            l = 0
            r = ST_SIZE - 1
            for d in binary_digits:
                m = (l+r) // 2
                if d == '1': l = m+1
                else: r = m
            if l < ST_PRINT_SIZE:
                dbgY(k, (l,r), seg[k], lazy[k])
    el()
    #endregion


def solve(testID):
    global seg
    N, Q = lm()
    dat = lm()
    dbgR(N, dat)
    el()

    init(N)
    for k, v in enumerate(dat): seg[n + k] = v
    build()
    dbgY(to_string())
    detailed_printouts()
    el()

    for qid in range(Q):
        iraw = input().split()
        dbg(iraw)
        qtype = int(iraw[0])
        l = int(iraw[1])
        r = int(iraw[2])
        l, r = l-1, r-1
        if qtype <= 2:
            x = int(iraw[3])
            upd(l, r, (qtype,x))
        else:
            # query range
            result = query(l, r)
            ps(result)
        dbg(qid, iraw, to_string())

    return


if __name__ == '__main__':
    T = 1
    # dbgBackground("Loading num cases!!!!!"); T = nn()  # ! Comment this out for single-case problems!
    for testID in range(1, T+1):
        el()
        dbgBackground(f"Case {testID}")
        solve(testID)
    dbgcR("runtime", TIME())
