
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


def solve(dat):
    N = len(dat)
    if dat[0] == 0 or dat[-1] == 0:
        return 'IMPOSSIBLE'

    assert sum(dat) == N

    dests = []
    for k, q in enumerate(dat):
        dests += [k for x in range(q)]

    assert len(dests) == N
    assert dests[0] == 0
    assert dests[N-1] == N-1

    out = []
    curr = [k for k in range(N)]
    future = copy.deepcopy(curr)
    while curr != dests:
        row = ['.' for x in range(N)]
        for k in range(N):
            if curr[k] == dests[k]:
                future[k] = curr[k]
            elif curr[k] < dests[k]:
                row[curr[k]] = '\\'
                future[k] = curr[k] + 1
            elif curr[k] > dests[k]:
                row[curr[k]] = '/'
                future[k] = curr[k] - 1
            else:
                assert False, ':('
        out.append(''.join(row))
        curr, future = future, curr
    out.append('.' * N)

    out = [str(len(out))] + out
    return '\n'.join(out)


T = nn()
for testID in range(1, T+1):
    C = nn()
    dat = lm()
    out = solve(dat)
    print('Case #{}: {}'.format(testID, out))
