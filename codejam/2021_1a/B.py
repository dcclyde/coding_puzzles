
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

'''
Let S = sum of all available primes.
I think the correct target value needs to be in [S - 3000, S]
    because any list of numbers <= 500 that add to >= 3000 has product >= 1e15.
    (I think the worst case is if you pick 500 a lot, and 500**6 > 1e15.)

So, I guess just try to factor each of those numbers and grab the first one that works?
Note it's easy to factor because I only have to consider the primes in my list.
    If it doesn't factor using only those primes then we don't care anyway.
'''

def try_factor(n, primes):
    factors = defaultdict(int)
    for p in primes:
        while n % p == 0:
            factors[p] += 1
            n //= p

    if n == 1:
        return factors
    else:
        return None


def solve(dat):
    M = len(dat)
    S = sum(count * p for p, count in dat)
    primes = [p for p, count in dat]

    max_target = S
    min_target = max(S - 10**4, 2)
    for target in range(max_target, min_target - 1, -1):
        factors = try_factor(target, primes)
        if factors is None:
            continue

        leftover_sum = 0
        ok = True
        for p, count in dat:
            num_left_over = count - factors[p]
            if num_left_over < 0:
                ok = False
                break
            leftover_sum += num_left_over * p

        if leftover_sum == target and ok:
            return target

    return 0



T = nn()
for testID in range(1, T+1):
    M = nn()
    dat = []
    for k in range(M):
        p, num_of_p = lm()
        dat.append((p, num_of_p))

    out = solve(dat)

    print('Case #{}: {}'.format(testID, out))
