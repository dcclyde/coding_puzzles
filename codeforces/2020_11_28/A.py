
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


def solve(dat, N, start, period, X, Y):

    insertion_cost = [None for x in range(N)]
    # I want out[k] = cost to win if our first landing is on space k.
    '''
    Normally we would land first on square "start".
    To land first on square k instead, we need to remove k-start squares.
    '''
    for k in range(N-1, -1, -1):
        # cost_from_initial_deletions = Y * (k-start)
        if k < start:
            insertion_cost[k] = int(1e18)
        insertion_cost[k] = (
            0 if dat[k] == '1' else X
        )
        if k + period < N:
            insertion_cost[k] += insertion_cost[k + period]

    best_cost = int(1e18)

    for k in range(start, N):
        deletion_cost = Y * (k-start)
        curr_cost = deletion_cost + insertion_cost[k]
        best_cost = min(best_cost, curr_cost)
        # print(f"k = {k}, insertion cost = {insertion_cost[k]}, deletion cost = {deletion_cost}")

    return best_cost


T = nn()
for testID in range(1, T+1):
    N, start, period = lm()
    start -= 1  # 1-indexed to 0-indexed
    dat = input().strip()
    x, y = lm()

    out = solve(dat, N, start, period, x, y)
    print(out)
