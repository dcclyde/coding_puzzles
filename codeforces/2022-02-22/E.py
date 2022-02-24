
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

'''
def solve(N, dat):
    # how much slack?
    nd = sum(1 for c in dat if c == 'D')
    nr = len(dat) - nd

    sd = N - nd - 1
    sr = N - nr - 1
    logger.debug((N, nd, nr, sd, sr))

    v = 1
    h = 1
    out = 1
    for k, c in enumerate(dat):
        if c == 'D':
            if v == 1:
                v_contrib = sd + 1
                v = sd + 1
            else:
                v_contrib = 1
            h_contrib = h

        else:  # c == 'R'
            if h == 1:
                h_contrib = sr + 1
                h = sr + 1
            else:
                h_contrib = 1
            v_contrib = v

        delta = v_contrib * h_contrib
        out += delta
        logger.debug(f"k = {k}, c = {k}, v = {v}, h = {h}, v_contrib = {v_contrib}, h_contrib = {h_contrib}, delta = {delta}, out = {out}")
    
    print(out)





T = nn()
for testID in range(1, T+1):
    N = nn()
    dat = input().strip()
    out = solve(N, dat)
