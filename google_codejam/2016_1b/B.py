
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


def solve(A, B):
    '''
    Suppose the first forced difference is at position k.
    Things to try:
    1) Starting at position k-1, {make A 1 larger, make B 1 larger} and then 0s / 9s from there.
    2) Starting at position k+1, use 0s and 9s.
    '''
    A = list(A)
    B = list(B)

    # what's the first required difference?
    frd = 0
    while frd < len(A) and (A[frd] == '?' or B[frd] == '?' or A[frd] == B[frd]):
        frd += 1

    if frd == len(A):
        assert False, 'Special case: make em match!'


    flip = False
    if A[frd] > B[frd]:
        flip = True
        A, B = B, A

    assert False, 'Remember to flip back if necessary!'

    options = []

    # ok, we can assume A is smaller in slot frd.
    # First, try making A "barely smaller" overall.
    A_curr = copy.deepcopy(A)
    B_curr = copy.deepcopy(B)
    make_match(A_curr, B_curr, 0, frd)
    make_small(B_curr, frd, len(B_curr))
    make_big(A_curr, frd, len(A_curr))
    sac = ''.join(A_curr)
    sbc = ''.join(B_curr)
    iac = int(sac)
    ibc = int(sbc)
    delta = abs(iac - ibc)
    options.append(
        delta,  # first tiebreaker: smallest delta wins.
        iac if not flip else ibc,  # tb2: smallest first score wins.
        ibc if not flip else iac,  # tb3: smallest 2nd score wins.
    )

    # Now try making A "barely bigger".
    A_curr = copy.deepcopy(A)
    B_curr = copy.deepcopy(B)
    # find most recent position where we can make A bigger.
    idx = frd - 1
    while idx >= 0 and (A[idx] == '0' or B[idx] == '9' or (A[idx] != '?' and B[idx] != '?')):
        idx -= 1
    if idx == -1:
        return f"{options[0][1]} {options[0][2]}"






T = nn()
for testID in range(1, T+1):
    [A, B] = input().strip().split()
    out = solve(A, B)
    print('Case #{}: {}'.format(testID, out))
