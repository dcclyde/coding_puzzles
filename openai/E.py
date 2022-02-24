
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

def sum_digits(x):
    out = 0
    while x > 0:
        out += x % 10
        x //= 10
    return out

def solve(S, N):
    S = list(S)
    pwr = 1
    num_chunks = 0
    value = 0
    for q in reversed(S):
        num_chunks += q
        value += q * pwr
        pwr *= 11

    for q in reversed(S):



    chunks = [0] * len(S)
    cascades = [0] * len(S)
    idx = 0
    while idx < len(S) and num_chunks <



def solve_old(S, N):
    S_str = str(S)
    base = sum(int(x) for x in S_str)

    # find a suffix that will contain all the breakups we'll need to cause.
    curr = base
    suffix_len = 1
    digit_sum_lost = 0
    potential_gained = 0
    while True:
        if curr - digit_sum_lost + potential_gained >= N:
            break
        suffix_len += 1
        digit = int(S_str[-suffix_len])
        potential_per_breakup = 10**(suffix_len - 1) - 1
        breakups_needed = (N - curr + potential_per_breakup-1) // potential_per_breakup
        if breakups_needed <= digit:


    # ok, now how many things from that suffix can we rescue?
    count_achievable = base - digit_sum_lost + potential_gained
    num_saveable = (count_achievable - N) // 9




    out = []
    exp = 0
    while S > 0 and len(out) < N:
        if S % 10 > 0:
            S -= 1
            out.append(exp)
        else:
            S //= 10
            exp += 1

    extra = []
    while len(out) < N:
        # find the first position where we can break things up.
        # don't care about speed, N is tiny.
        idx = 0
        while out[idx] == 0:
            idx += 1




    if len(out) == N:
        out[-1] += S
        return ' '.join()







    return ' '.join(str(q) for q in (N, L, R))



T = nn()
for testID in range(1, T+1):
    S, N = lm()
    out = solve(S, N)
    print(out)
