
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


def solve(dat, K):
    N = len(dat)
    best_cost = N
    for c in range(1, 101):
        cost = 0
        loc = 0
        while loc < N:
            if dat[loc] != c:
                loc += K
                cost += 1
            else:
                loc += 1
        best_cost = min(best_cost, cost)
    return best_cost


T = nn()
for testID in range(1, T+1):
    N, K = lm()
    dat = lm()
    out = solve(dat, K)
    print(out)
