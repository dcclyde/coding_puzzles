
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
len(dat) <= 5000.

I guess let's write down max sum of contiguous subarray of length L.
Then answer for k is max of [M(L) + toadd * min(L, k)].

Should be fine to just run in N^2?
'''

def solve(dat, toadd):
    N = len(dat)
    maxes = [-10**12 for k in range(N+1)]
    maxes[0] = 0
    for front in range(N):
        curr_sum = 0
        for back in range(front, N):
            curr_sum += dat[back]
            length = back - front + 1
            maxes[length] = max(maxes[length], curr_sum)
            logger.debug(f"curr_sum = {curr_sum}, front = {front}, back = {back}, maxes = {maxes}")
    
    logger.debug(maxes)
    out = []
    for k in range(N+1):
        best = 0
        for L in range(N+1):
            curr = maxes[L] + toadd * min(L, k)
            best = max(curr, best)
        out.append(best)
    print(' '.join(str(x) for x in out))



T = nn()
for testID in range(1, T+1):
    N, toadd = lm()
    dat = lm()
    assert len(dat) == N
    out = solve(dat, toadd)
