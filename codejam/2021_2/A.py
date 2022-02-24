
import copy
from collections import defaultdict
from collections import deque
import math
import sys
import pickle
import bz2
import base64

sys.setrecursionlimit(10**6)

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

'''
Naive strategy:
Just do insertion sort.
Ask where the smallest element is, then put it at front, then ask for next smallest, etc.
First cost is 1e8 / N.
Then 1e8 / (N-1).

seems legit?
'''

def solve(N):
    for curr_pos in range(N-1):  # ZERO INDEXED!
        # query what the next min should be.
        print(f"M {curr_pos+1} {N}", flush=True)
        next_min_pos = nn()
        # swap that one into position.
        if next_min_pos != curr_pos + 1:
            print(f"S {curr_pos+1} {next_min_pos}", flush=True)
            dummy_one = nn()

    print("D", flush=True)
    dummy_one = nn()
    if dummy_one != 1:
        exit()

    return


T, N = lm()
for testID in range(1, T+1):
    solve(N)
