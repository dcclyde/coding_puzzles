
import copy
from collections import defaultdict
from collections import deque
import math
import sys
import os

# sys.setrecursionlimit(10**5)  # This uses something like 128 MB RAM. I guess only play with this if I expect recursion depth problems.

# provides more detailed listing of complicated objects
# call like dbg(print_details_helper)
def print_details_helper(q):
    out = []
    for k, x in enumerate(q):
        out.append(f"\n\t{k}\t{x}")
    return ''.join(out)

pdh = print_details_helper  # alternate shorter name

# good if we want to see spacing, or to copy-paste into GSheets
def print_tsv_helper(q):
    out = []
    for row in q:
        out.append('\t'.join(str(x) for x in row))
    return ''.join('\n\t' + x for x in out)

pth = print_tsv_helper


#region  set up dbg commands
# set up debug stuff.
# remember .bashrc should contain `export PYTHON_CONTEST_HELPER="dummy"`
local_run = False
if os.environ.get("PYTHON_CONTEST_HELPER"):
    local_run = True
    OUT_RED_BOLD = "\033[31;1m"
    OUT_GREEN = "\033[32m"
    OUT_RESET = "\033[0m"
    OUT_BOLD = "\033[;1m"
    OUT_CYAN = "\033[36;1m"
    OUT_PURPLE = "\033[35;1m"
    OUT_YELLOW = "\033[33;1m"
    OUT_BACKGROUND = "\033[41;30;1m"

    def dbgBase(*args, **kwargs):
        color_helper = kwargs.pop('color', OUT_CYAN)
        print(f"{OUT_RED_BOLD}{sys._getframe().f_back.f_back.f_lineno: >20} {OUT_BOLD}: {color_helper}", end='', file=sys.stderr)
        end_maybe = kwargs.get('end', '\n')
        kwargs['end']=f"{OUT_RESET}{end_maybe}"
        print(*args, file=sys.stderr, **kwargs)

    def dbg(*args, **kwargs): dbgBase(color=OUT_CYAN, *args, **kwargs)
    dbgB = dbg
    def dbgG(*args, **kwargs): dbgBase(color=OUT_GREEN, *args, **kwargs)
    def dbgP(*args, **kwargs): dbgBase(color=OUT_PURPLE, *args, **kwargs)
    def dbgY(*args, **kwargs): dbgBase(color=OUT_YELLOW, *args, **kwargs)
    def dbgBackground(*args, **kwargs): dbgBase(color=OUT_BACKGROUND, *args, **kwargs)
    def el(n=1): print('\n'*n, file=sys.stderr, end='')
else:
    def dbg(*args, **kwargs): pass
    def dbgB(*args, **kwargs): pass
    def dbgG(*args, **kwargs): pass
    def dbgP(*args, **kwargs): pass
    def dbgY(*args, **kwargs): pass
    def dbgBackground(*args, **kwargs): pass
    def el(n=1): pass
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

def nn():
    return int(input())

def li():
    return list(input())

def lm():
    return list(map(int, input().split()))


# To print while flushing output for interactive problems:
# print(x, flush=True)


#########################################################################
# Problem specific code usually goes below this line.
#########################################################################

# ! Read the sample cases before writing code!








def solve(testID):
    N = nn()
    dat = lm()
    dbg(N, dat)





    return


if __name__ == '__main__':
    T = 1
    dbgBackground("Loading num cases!!!!!"); T = nn()  # ! Comment this out for single-case problems!
    for testID in range(1, T+1):
        el()
        dbgBackground(f"Case {testID}")
        solve(testID)
