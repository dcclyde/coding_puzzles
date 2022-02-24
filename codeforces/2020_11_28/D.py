
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


def solve(R, C, goal_R, goal_C):
    cost = 0
    for base_R in [1, R]:
        for base_C in [1, C]:
            curr = abs(base_R - goal_R) + abs(base_C - goal_C)
            cost = max(cost, curr)
    return cost



T = nn()
for testID in range(1, T+1):
    R, C, goal_R, goal_C = lm()
    out = solve(R, C, goal_R, goal_C)
    print(out)
