
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

def num_bits_set(x):
    out = 0
    while x > 0:
        out += x&1
        x >>= 1
    return out

def solve():
    # logic logic logic

    dat = input().strip()
    N = len(dat)
    num_queries = nn()
    for _ in range(num_queries):
        num_iterations, idx_to_print = lm()
        idx_to_print -= 1

        len_per_char = 1
        for step in range(num_iterations):
            len_per_char *= 2
            if len_per_char > idx_to_print:
                break

        source_char_idx = idx_to_print // len_per_char
        subidx = idx_to_print % len_per_char
        char_used = ord(dat[source_char_idx]) - ord('A')
        bits_set = num_bits_set( subidx )
        out_char = (char_used + bits_set + num_iterations) % 3
        out = chr(ord('A') + out_char)

        print(out)

    return


T = 1
# T = nn()
for testID in range(1, T+1):
    solve()
