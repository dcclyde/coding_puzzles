#region imports
import copy
from collections import defaultdict as dd
from collections import deque
import math
import sys
import os
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
if os.environ.get("PYTHON_CONTEST_HELPER"):
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

def li():
    return list(input())

def lm():
    return list(map(int, input().split()))

# To print while flushing output for interactive problems:
# print(x, flush=True)
#endregion

#########################################################################
# Problem specific code usually goes below this line.
#########################################################################

# ! Read the sample cases before writing code!

def check(N, tp, desired, tests_active, G):

    dbg(N, tp, desired, tests_active, G)
    el()

    # now do the actual traversal.
    results = [[0 for x in range(3)] for y in range(N)]
    global ctr
    ctr = 0
    def Dfs(curr, parent):
        global ctr
        ctr += 1
        dbgP(parent, curr)
        if ctr > 2*N*N:
            dbgcG("cycles?", curr, pdh(results))
            return False
        for o in G[curr]:
            if o == parent: continue
            for k in range(3):
                results[o][k] |= results[curr][k] and not (tests_active[curr] and (tp[curr][k] == 0))
            Dfs(o, curr)


    results[0] = [1,1,1]
    Dfs(0, -1)
    dbg(pdh(results))
    if results != desired:
        dbgcR("wrong answer", pdh(desired))
        return False

    return True




ctr = 0
def solve():
    N = nn()

    desired = []
    for _ in range(N):
        desired.append(lm())

    tp = []
    for _ in range(N):
        tp.append(lm())

    dbgR(N, tp)
    dbgR(desired)

    for mask in range(1<<(N**2)):
        tests_active = [0 for _ in range(N)]
        for k in range(N):
            if ((mask>>k) & 1):
                tests_active[k] = 1

        G = [[] for _ in range(N)]
        ctr = N
        for a in range(N):
            for b in range(N):
                if a == b: continue
                if (mask >> ctr) & 1:
                    G[a].append(b)
                ctr += 1

        if check(N, tp, desired, tests_active, G):
            return print("Possible")

    print("Impossible")


if __name__ == '__main__':
    solve()
