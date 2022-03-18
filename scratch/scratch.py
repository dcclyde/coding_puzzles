
import copy
from collections import defaultdict
from collections import deque
import math
import sys
import os

# sys.setrecursionlimit(10**5)  # This uses something like 128 MB RAM. I guess only play with this if I expect recursion depth problems.

#region set up dbg commands
# set up debug stuff.
# remember .bashrc should contain `export PYTHON_CONTEST_HELPER="dummy"`
if os.environ.get("PYTHON_CONTEST_HELPER"):
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
        print(*args, file=sys.stderr, **kwargs)
        print(f"{OUT_RESET}", file=sys.stderr, end='')

    def dbg(*args, **kwargs):
        kwargs['color'] = OUT_CYAN
        dbgBase(*args, **kwargs)

    dbgB = dbg

    def dbgG(*args, **kwargs):
        kwargs['color'] = OUT_GREEN
        dbgBase(*args, **kwargs)

    def dbgP(*args, **kwargs):
        kwargs['color'] = OUT_PURPLE
        dbgBase(*args, **kwargs)

    def dbgY(*args, **kwargs):
        kwargs['color'] = OUT_YELLOW
        dbgBase(*args, **kwargs)

    def dbgBackground(*args, **kwargs):
        kwargs['color'] = OUT_BACKGROUND
        dbgBase(*args, **kwargs)

    def el(n=1):
        print('\n'*n, file=sys.stderr, end='')
else:
    def dbg(*args, **kwargs):
        pass
    def dbgB(*args, **kwargs):
        pass
    def dbgG(*args, **kwargs):
        pass
    def dbgP(*args, **kwargs):
        pass
    def dbgY(*args, **kwargs):
        pass
    def el(n=1):
        pass
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


def solve():
    N = nn()
    dat = lm()





    return


dbg("This is just me demoing dbg, obviously not part of the template.")
dbgP("Use dbg just like print, but it prints with fancy format and writes to cerr and also won't print at all unless PYTHON_CONTEST_HELPER is defined, see comment about PYTHON_CONTEST_HELPER above.")
dbgBackground("Most python objects get passed by reference so you could call dbg(hugeList) and leave that call in when submitting and it should be no problem.")
dbgY("Don't call dbg([x for x in range(10**15)]) though. And if you have calls that construct a big object then you do need to comment those before submitting.")
dbgG("el() writes one empty line just for spcaing purposes. el(n) writes n empty lines. Again safe to submit with these left in.")
el()
dbg("The FastIO part is an experiment, copy-pasting from someone on codeforces. You should find a problem with a lot of input/output and experiment whether commenting out that whole section helps vs hurts your runtime (or correctness??)")
el()
X = 14
dat = [x**3 - 6 for x in range(2,9)]
dbgB(X, dat)
dbgG('abc')
el(3)
dbgP('12', {1, 3})
el(2)
dbgY([1,534,23,2], [{1, 'b'}, 31])
exit()

T = 1
T = nn()  # ! Comment this out for single-case problems!
for testID in range(1, T+1):
    solve()
