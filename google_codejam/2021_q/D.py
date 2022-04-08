
import copy
from collections import defaultdict
from collections import deque
import math
import sys
import pickle
import bz2
import base64
import random

import logging
logger = None
numeric_log_level = getattr(logging, 'INFO', None)
logging.basicConfig(
    stream=sys.stderr,
    format='%(asctime)s.%(msecs)d %(levelname)-8s [%(filename)s:%(lineno)d] %(message)s',
)
logger = logging.getLogger('Puzzles')
logger.setLevel(numeric_log_level)


if sys.version_info[0] == 2:
    input = raw_input

def nn():
    return int(input())

def li():
    return list(input())

# def mi():
#     return map(int, input().split())

def lm():
    return list(map(int, input().split()))

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

def query(a, b, c):
    print(
        '{} {} {}'.format(a, b, c),
        flush=True,
    )
    reply = input().strip()
    logger.debug(f"Queried {a} {b} {c}, got back {reply}.")
    return int(reply)


def submit(out):
    print(' '.join(str(x) for x in out), flush=True)
    reply = input().strip()
    assert int(reply) == 1
    return


def helper(dat, lo, hi, reference, reference_is_low):
    if hi - lo <= 1:
        return

    if hi - lo >= 10:
        a, b, c = reference, reference, reference
        while reference in [a, b, c]:
            a, b, c = random.sample(dat[lo:hi], 3)
        dp = query(a, b, c)
    else:
        dp = reference
        while dp == reference:
            dp = dat[random.randint(lo, hi-1)]

    logger.debug(f"About to sort {lo} to {hi}, pivot {dp}, reference {reference}, current list is {dat}")


    small = []
    large = []
    for curr in range(lo, hi):
        if dat[curr] == reference:
            if reference_is_low:
                small.append(dat[curr])
            else:
                large.append(dat[curr])
            continue
        if dat[curr] == dp:
            continue
        qout = query(reference, dp, dat[curr])
        if (qout == dp) != reference_is_low:
            # logger.debug(f"Add {dat[curr]} to small.")
            small.append(dat[curr])
        else:
            # logger.debug(f"Add {dat[curr]} to large.")
            large.append(dat[curr])

    logger.debug(f"Pivot {dp}, small is {small}, large is {large}")

    dat[lo:hi] = small + [dp] + large

    helper(dat, lo, lo + len(small), dp, False)
    helper(dat, hi - len(large), hi, dp, True)

    logger.debug(f"Done sorting {lo} to {hi}, current list is {dat}")

    return


def solve(N):
    '''
    50 elements. I get 300 questions on average, or maybe 170 if I wanna be cool.
    Say I pick one element at random (or a median?)
    and then I try to figure out which stuff is on which side of it.

    '''
    dat = [k for k in range(1, N+1)]
    helper(dat, 0, N, 1, True)

    submit(dat)



T, N, Q = lm()
for testID in range(1, T+1):
    solve(N)
