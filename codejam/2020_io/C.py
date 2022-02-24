
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


def solve_small(dat):
    # build all possible combinations of 4 strings.
    N = len(dat)
    out = 0

    for x in range(4**N):
        plan = [[] for q in range(4)]
        working = x
        for k in range(N):
            curr = working % 4
            working //= 4
            plan[curr].append(dat[k])

        '''
        Require plan[0] to be IOIOIO, plan[1] to be IoIoIo, and so on.
        '''
        ok = True
        bases = ['IO', 'iO', 'Io', 'io']
        for k in range(4):
            joined = ''.join(plan[k])
            if len(joined) % 2 == 1:
                ok = False
                break
            candidate = bases[k] * (len(joined) // 2)
            if candidate != joined:
                ok = False
                break

        if ok:
            out = max(out, len(plan[0]) // 2)

    return out










T = nn()
for testID in range(1, T+1):
    dat = input().strip()
    out = solve_small(dat)
    print('Case #{}: {}'.format(testID, out))
