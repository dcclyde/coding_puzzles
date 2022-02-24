
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


def solve(R, C, NUM_STUCK_TARGET):

    # logger.info((R, C, NUM_STUCK_TARGET))
    if NUM_STUCK_TARGET == 1:
        return 'IMPOSSIBLE'

    if R * C == 1 and NUM_STUCK_TARGET != 0:
        return 'IMPOSSIBLE'

    dat = [['S' for x in range(C)] for y in range(R)]


    for rr in range(R):
        for cc in range(C):

            if NUM_STUCK_TARGET == 0:
                dat[rr][cc] = 'S'

            elif rr == 0 and cc == 0:
                dat[rr][cc] = 'E' if C > 1 else 'S'
                NUM_STUCK_TARGET -= 1

            elif rr == 0:
                dat[rr][cc] = 'W'
                NUM_STUCK_TARGET -= 1

            else:
                dat[rr][cc] = 'N'
                NUM_STUCK_TARGET -= 1

    # build the output format.
    output_lines = [''.join(q) for q in dat]
    output_lines = ['POSSIBLE'] + output_lines

    return '\n'.join(output_lines)



T = nn()
for testID in range(1, T+1):
    R, C, NUM_ESCAPING_TARGET = lm()
    NUM_STUCK_TARGET = R * C - NUM_ESCAPING_TARGET
    out = solve(R, C, NUM_STUCK_TARGET)
    print('Case #{}: {}'.format(testID, out))
