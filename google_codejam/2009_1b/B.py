
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


def solve(dat_str):

    dat = [int(c) for c in dat_str]
    # find the first place where dat is strictly ascending.
    last_asc = None
    for k in range(len(dat) - 1):
        if dat[k] < dat[k+1]:
            last_asc = k

    if last_asc is None:
        dat.sort()
        first_nonzero = min(k for k in range(len(dat)) if dat[k] != 0)
        out = [first_nonzero] + [0] + dat[:first_nonzero] + dat[first_nonzero + 1:]
        return ''.join(str(q) for q in out)

    out = dat[:last_asc]
    dat = dat[last_asc:]

    # the smallest thing that's bigger than the original start should be the new start.
    new_start = min(q for q in dat if q > dat[0])
    new_start_pos = dat.index(new_start)
    out += [new_start]
    dat = dat[:new_start_pos] + dat[new_start_pos + 1:]
    dat.sort()
    out += dat

    return ''.join(str(q) for q in out)







    return ' '.join(str(q) for q in (N, L, R))



T = nn()
for testID in range(1, T+1):
    dat_str = input().strip()
    out = solve(dat_str)
    print('Case #{}: {}'.format(testID, out))
