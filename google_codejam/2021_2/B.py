
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
Given N up to 1e6.
Want to find longest possible chain of divisors 3 <= d1 < d2 < d3 < ...
such that the sum of all dj is exactly N.

Binary search?

d1 needs to be a divisor of N.

dp?
f(d, S) = best num divisors when curr divisor is d and curr sum is S
answer is f(1, 0)
fail if S > N
fail if N-S is not divisible by d

Numbers up to 1e6 have at most 20 factors anyway.
So these trees can only go like 6 steps deep.

How many distinct factors can N have total?
I guess that'd come from primorial?

'''

# def f(d, S, N):
#     if S == N:
#         return 0
#     if S > N:
#         return -1
#     if (N-S) % d != 0:
#         return -1
#     '''
#     If d = 5, N-S = 95 then the plausible steps are basically any factor of 19.
#     '''
#     remaining = (N-S) // d
#     best = -1
#     for next_divisor in factors(remaining):
#         curr = f(d * next_divisor, S + d * next_divisor, N)
#         best = max(best, curr)

#     return 1 + best

# def g(N):
#     if N < 0:
#         return -1
#     best = -1
#     for d in factors(N):
#         curr = g((N-d) // d)
#         best = max(best, curr)
#     return best + 1


MAX = 10**6 + 1
# MAX = 10**3 + 1
# logger.debug("About to generate primes.")
# is_prime = [True for x in range(MAX)]
# primes = []
# for p in range(2, len(is_prime)):
#     primes.append(p)
#     k = 2
#     while k*p < len(is_prime):
#         is_prime[k] = False
#         k += 1
# del is_prime
# logger.debug("Done generating primes.")

def factors(X):
    # prime_factors = defaultdict(int)
    # for p in primes:
    #     while X % p == 0:
    #         prime_factors[p] += 1
    #         X //= p
    #     if X == 1:
    #         break
    # return list(prime_factors.keys())  # ?????

    candidate = 2
    while candidate * candidate <= X:
        if X % candidate == 0:
            yield candidate
            if candidate * candidate != X:
                yield X // candidate
        candidate += 1


# gg = [None for x in range(MAX)]
# gg[0] = 0
# gg[1] = -MAX
# for k in range(2, MAX):
#     g[k] = 1
#     if k % 10 == 0:
#         print(k)
#     for d in factors(k):
#         if d <= 1:
#             continue
#         # print(k, d, (k-d)//d, g[(k-d)//d])
#         g[k] = max(g[k] , g[(k-d)//d] + 1)

gg = {}
gg[0] = 0
gg[1] = -MAX
def g(K):
    if K < 0:
        return -MAX
    if K in gg:
        return gg[K]
    gg[K] = 1
    for d in factors(K):
        if d <= 1:
            continue
        gg[K] = max(gg[K] , g((K-d)//d) + 1)
    return gg[K]


def solve(N):
    # watch out - first factor isn't allowed to be 2.
    out = 1
    for d in factors(N):
        if d < 3:
            continue
        curr = 1 + g((N-d)//d)
        out = max(curr, out)
    return out


T = nn()
for testID in range(1, T+1):
    N = nn()
    out = solve(N)
    print('Case #{}: {}'.format(testID, out))

# for k, v in gg.items():
#     print(k, v)
