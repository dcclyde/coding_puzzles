
import copy
from collections import defaultdict
from collections import deque
import math
import sys
import pickle
import bz2
import base64

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
            base64.b64encode(
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

MAX = 501
ff = [[None for x in range(MAX)] for y in range(MAX)]

ff[0][0] = 0.
ff[1][0] = 3.
ff[0][1] = 3.
ff[1][1] = 4.

'''
Along edge:
f(x, 0) = 1/2 f(x-1, 0) + 1/2 f(x, 1) + 1

Otherwise:
f(x, 1) = 1/2 f(x-1, 1) + 1/2 f(x, 0) + 1


'''
for k in range(2, MAX):
    ff[k][0] = ff[0][k] = 2./3 * ff[k-1][0] + 1./3 * ff[k-1][1] + 2.
    ff[k][1] = ff[1][k] = 1./3 * ff[k-1][0] + 2./3 * ff[k-1][1] + 2.

for r in range(2, MAX):
    for c in range(2, MAX):
        ff[r][c] = 1./2 * ff[r-1][c] + 1./2 * ff[r][c-1] + 1.


def solve(X, Y):

    return ff[abs(X)][abs(Y)]



T = nn()
for testID in range(1, T+1):
    X, Y = lm()
    out = solve(X, Y)
    print('Case #{}: {}'.format(testID, out))
