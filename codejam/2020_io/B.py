
import copy
from collections import defaultdict
from collections import deque
import math
import sys
import pickle
import bz2
import base64
import itertools

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


def solve(dat):

    N = len(dat)


    for option in range(2**N):
        choices = []
        working = option
        for k in range(N):
            choices.append(
                'R' if working % 2 == 0 else 'L'
            )
            working //= 2

        # now check it...

    ######################################################

    for option in itertools.combinations(range(N), N//2):
        choices = ['L' for k in range(N)]
        for q in option:
            choices[q] = 'R'

        choices = [
            'L' if k in option else 'R'
            for k in range(N)
        ]








    return ' '.join(str(q) for q in (N, L, R))



T = nn()
for testID in range(1, T+1):
    N = nn()
    dat = lm()
    out = solve(dat)
    print('Case #{}: {}'.format(testID, out))
