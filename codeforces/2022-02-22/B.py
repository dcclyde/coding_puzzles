
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

ctr = 6
def helper(N, curr, unused):
    global ctr

    if ctr == 0:
        return

    if len(curr) == N:
        print(' '.join(str(x) for x in curr))
        ctr -= 1
        return

    for k in unused:
        if len(curr) >= 2 and curr[-1] + curr[-2] == k:
            continue
        helper(N, curr + [k], unused - {k})
    return


def solve(N):
    global ctr
    ctr = N
    helper(N, [], {k+1 for k in range(N)})

T = nn()
for testID in range(1, T+1):
    N = nn()
    solve(N)
