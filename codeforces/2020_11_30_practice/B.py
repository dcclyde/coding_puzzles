
import copy
from collections import defaultdict
from collections import deque
import math
import sys
import pickle
import bz2
import base64

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


def solve(N):
    # find smallest k such that 1+2+...+k >= N.
    lo = 0
    hi = N
    while hi-lo > 1:
        curr = (lo + hi) // 2
        if curr * (curr + 1) // 2 < N:
            # curr is too small.
            lo = curr
        else:
            hi = curr
    k = hi
    total = k * (k+1) // 2
    if total == N+1:
        return k+1
    else:
        return k

T = nn()
for testID in range(1, T+1):
    N = nn()
    out = solve(N)
    print(out)
