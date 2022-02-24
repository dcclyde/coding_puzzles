
import copy
from collections import defaultdict
from collections import deque
import math
import sys
import pickle
import bz2
import base64

sys.setrecursionlimit(10**6)

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


def solve(dat):
    dat = dat[1:-1]
    # fail if we only have 1 pile to work with and it's odd
    if len(dat) == 1 and dat[0] % 2 == 1:
        return -1

    dat = [x for x in dat if x != 0]
    cost = sum(x//2 + (x%2) for x in dat)

    # fail if all nonempty piles are 1s (we can't move)
    if all(x == 1 for x in dat):
        return -1

    # fail if we have just 1 nonempty pile and size is 3
    if len(dat) == 1 and dat[0] == 3:
        return -1

    if len(dat) == 1 and dat[0] % 2 == 1:
        return cost + 1

    return cost



T = nn()
for testID in range(1, T+1):
    N = nn()
    dat = lm()
    out = solve(dat)
    print(out)
