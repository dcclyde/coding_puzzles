
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

'''
.
1) Keep passing in whatever the robot just said.

Once we've been around the cycle a couple times, use that path to figure out the best word.

2) Say the best word a bunch.
'''

def solve():

    dat = ['AAAAA']
    while len(dat) < 35:
        print(dat[-1])
        sys.stdout.flush()
        robot = input().strip()
        dat.append(robot)

    pair_counts = defaultdict(int)
    for k in range(len(dat) - 1):
        pair_counts[(dat[k], dat[k+1])] += 1

    candidates = [pair for pair, count in pair_counts if count > 1]

    # one of these candidates









    return ' '.join(str(q) for q in (N, L, R))



T, N = lm()
for testID in range(1, T+1):
    solve()
