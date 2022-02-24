

from __future__ import division, print_function

import copy
from collections import defaultdict
from collections import deque
import math
import sys
import pickle
import bz2
import base64

# sys.setrecursionlimit(10**6)

# #####
# # improving I/O? from https://codeforces.com/blog/entry/47667
# import atexit
# import io
# import sys

# _INPUT_LINES = sys.stdin.read().splitlines()
# input = iter(_INPUT_LINES).__next__
# _OUTPUT_BUFFER = io.StringIO()
# sys.stdout = _OUTPUT_BUFFER

# @atexit.register
# def write():
#     sys.__stdout__.write(_OUTPUT_BUFFER.getvalue())
# #####

###########

# from __future__ import division, print_function

import os
import sys
from io import BytesIO, IOBase

if sys.version_info[0] < 3:
    from __builtin__ import xrange as range
    from future_builtins import ascii, filter, hex, map, oct, zip


def main():
    pass


# region fastio

BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
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


def print(*args, **kwargs):
    """Prints the values to a stream, or to sys.stdout by default."""
    sep, file = kwargs.pop("sep", " "), kwargs.pop("file", sys.stdout)
    at_start = True
    for x in args:
        if not at_start:
            file.write(sep)
        file.write(str(x))
        at_start = False
    file.write(kwargs.pop("end", "\n"))
    if kwargs.pop("flush", False):
        file.flush()


if sys.version_info[0] < 3:
    sys.stdin, sys.stdout = FastIO(sys.stdin), FastIO(sys.stdout)
else:
    sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)

input = lambda: sys.stdin.readline().rstrip("\r\n")

###########

import logging
logger = None
# change DEBUG to INFO to block all the debug-level messages.
numeric_log_level = getattr(logging, 'INFO', None)
logging.basicConfig(
    stream=sys.stderr,
    format='%(asctime)s.%(msecs)d %(levelname)-8s [%(filename)s:%(lineno)d] %(message)s',
)
logger = logging.getLogger('PUZZLES')
logger.setLevel(numeric_log_level)

# logger.debug('example')


# if sys.version_info[0] == 2:
#     input = raw_input

def nn():
    return int(input())

def li():
    return list(input())

def lm():
    return list(map(int, input().split()))

# Tries really hard to serialize + compress any input object as a string.
# Useful if I want to precompute something fat, then compress it, then rebuild it when running on Google servers.
def compress(abc):
    return base64.b64encode(
        bz2.compress(
            pickle.dumps(
                abc
            )
        )
    )

def expand(abc):
    return pickle.loads(
        bz2.decompress(
            base64.b64decode(
                abc
            )
        )
    )

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
            logger.debug(f"Build slot {i} ({self.tree[i]}) from slots {i<<1} ({self.tree[i<<1]}) and {i<<1|1} ({self.tree[i<<1|1]}).")

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
            logger.debug(f"agg range ({m}, {n}), res_left = {res_left}, res_right = {res_right}")
            if m & 1:
                res_left = self.op(res_left, self.tree[m])
                logger.debug(f"Added slot m = {m} ({self.tree[m]}), got {res_left}")
                m += 1
            m >>= 1
            if n & 1 == 0:
                res_right = self.op(self.tree[n], res_right)
                logger.debug(f"Added slot n = {n} ({self.tree[n]}), got {res_right}")
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
    logger.debug(f"Custom op: {x} ~ {y} becomes {out}")
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

logger.debug(dat)
for k, q in enumerate(segtree.tree):
    logger.debug((k, q))

def process_query(L, R):
    A, B, C = segtree.aggregate_range(L - 1, R - 1)
    logger.debug(((L, R), A))
    print(A * 2)


num_queries = nn()
for _ in range(num_queries):
    L, R = lm()
    process_query(L, R)
