
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


def solve(dat_ints):
    dat = [str(q) for q in dat_ints]
    N = len(dat)

    out = 0
    for k in range(1, N):
        # curr = dat[k]
        # prev = dat[k-1]
        '''
        Want to add the smallest possible suffix to curr such that afterward we have curr > prev.
        '''
        # are we already done?
        if int(dat[k-1]) < int(dat[k]):
            continue

        '''
        If curr is a prefix of prev:
            If the rest of prev is all 9s, we need to make curr longer than prev.
                Use all 0s.
            Otherwise, we can just make curr into prev + 1.

        If curr > prev's prefix:
            Make curr have same length as prev by adding all 0s.

        If we're here, then curr < prev's prefix.
            Make curr have have length 1 more than prev using all 0s.
        '''

        L = len(dat[k])
        if dat[k-1][:L] < dat[k]:
            cost = len(dat[k-1]) - L
            dat[k] += '0' * cost
            out += cost

        elif (
            dat[k-1][:L] == dat[k]
            and
            dat[k-1][L:] != ('9' * (len(dat[k-1]) - L))
        ):
            replacement_int = int(dat[k-1]) + 1
            replacement = str(replacement_int)
            assert replacement.startswith(dat[k])
            cost = len(replacement) - len(dat[k])
            dat[k] = replacement
            out += cost

        else:
            cost = len(dat[k-1]) - L + 1
            dat[k] += '0' * cost
            out += cost

    return out




T = nn()
for testID in range(1, T+1):
    N = nn()
    dat = lm()
    out = solve(dat)
    print('Case #{}: {}'.format(testID, out))
