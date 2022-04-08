
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

# Just to remind myself how to flush input.
# Useful for interactive problems.
def query(a, b, c):
    print(
        '{} {} {}'.format(a, b, c),
        flush=True,
    )
    reply = input().strip()
    logger.debug(f"Queried {a} {b} {c}, got back {reply}.")
    return int(reply)

#########################################################################
# Problem specific code usually goes below this line.
#########################################################################



def solve(dat):
    out = ''
    for c in dat:
        out = max(c + out, out + c)
    return out



T = nn()
for testID in range(1, T+1):
    dat = input().strip()
    out = solve(dat)
    print('Case #{}: {}'.format(testID, out))
