
import copy
from collections import defaultdict
from collections import deque
import math
import sys
import pickle
import bz2
import base64

# sys.setrecursionlimit(10**5)  # This uses something like 128 MB RAM. I guess only play with this if I expect recursion depth problems.

import logging
logger = None
# change DEBUG to INFO to block all the debug-level messages.
numeric_log_level = getattr(logging, 'DEBUG', None)
numeric_log_level = getattr(logging, 'INFO', None)
logging.basicConfig(
    stream=sys.stderr,
    format='%(asctime)s.%(msecs)d %(levelname)-8s [%(filename)s:%(lineno)d] %(message)s',
)
logger = logging.getLogger('PUZZLES')
logger.setLevel(numeric_log_level)


if sys.version_info[0] == 2:
    input = raw_input

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


#########################################################################
# Problem specific code usually goes below this line.
#########################################################################

'''
all vars <= 2e5.



'''

MOD = 998244353

def solve(R, C, num_colors, num_ops):
    ops = []
    for _ in range(num_ops):
        rr, cc = lm()
        ops.append((rr-1, cc-1))

    row_seen = [False for k in range(R)]
    col_seen = [False for k in range(C)]
    num_rows_seen = 0
    num_cols_seen = 0
    out = 1

    for rr, cc in reversed(ops):
        row_irrelevant = (row_seen[rr] or num_cols_seen == C)
        col_irrelevant = (col_seen[cc] or num_rows_seen == R)
        logger.debug(
            f"rr = {rr}, cc = {cc}, num_rows_seen = {num_rows_seen}, num_cols_seen = {num_cols_seen}" +
            f"row_irrelevant = {row_irrelevant}, col_irrelevant = {col_irrelevant}"
        )


        if not row_seen[rr]:
            row_seen[rr] = True
            num_rows_seen += 1

        if not col_seen[cc]:
            col_seen[cc] = True
            num_cols_seen += 1

        if not (row_irrelevant and col_irrelevant):
            out = (out * num_colors) % MOD
        if num_rows_seen == R and num_cols_seen == C:
            break

    print(out)





T = nn()
for testID in range(1, T+1):
    R, C, num_colors, num_ops = lm()
    out = solve(R, C, num_colors, num_ops)
