
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

def one_axis(start, end, bound):
    result_1 = end - start
    result_2 = bound - start + bound - end
    mod = 2 * (bound - 1)
    return {result_1 % mod, result_2 % mod}

    if start <= end:
        return end - start
    return bound - start + bound - end

'''
# TODO I see how to do this but I'm sleepy and won't finish it right now.
I think I should find the indices that work from row perspective (mod 2*(R-1))
and same for column perspective (mod 2*(C-1)).
Then add all the contributions for row perspective (mod LCM) and same for col
    and subtract the contributions that overlap if any
Then do some additional annoying fiddling using mod inverses
so I can do all the above math in integers.
'''

def solve():
    R, C, rstart, cstart, rend, cend = lm()


    result_r = one_axis(rstart, rend, R)
    result_c = one_axis(cstart, cend, C)

    out = min(result_r, result_c)
    print(out)


T = nn()
for testID in range(1, T+1):
    solve()

