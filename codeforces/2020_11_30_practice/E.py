
import copy
from collections import defaultdict
from collections import deque
import math
import sys
import pickle
import bz2
import base64

import itertools

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

def median_kinda(li, s):
    li.sort()
    li[2] -= s
    li[3] -= s
    li.sort()
    return li[1]

def dist(p, q):
    assert len(p) == len(q)
    return sum(abs(p[k] - q[k]) for k in range(len(p)))

def solve(dat):
    x_min = min(q[0] for q in dat)
    x_max = max(q[0] for q in dat)
    y_min = min(q[1] for q in dat)
    y_max = max(q[1] for q in dat)

    dx = x_max - x_min
    dy = y_max - y_min


    if dy > dx:
        # we have a vertical rectangle.
        s = dx
        botleft_x = x_min
        botleft_y = median_kinda([q[1] for q in dat], s)
    else:
        s = dy
        botleft_y = y_min
        botleft_x = median_kinda([q[0] for q in dat], s)

    final = [
        [botleft_x + s*jj, botleft_y + s*kk]
        for jj in range(2)
        for kk in range(2)
    ]

    # print(s, botleft_x, botleft_y)

    best_cost = int(1e18)
    for perm in itertools.permutations(range(4)):
        cost = sum(
            dist(
                dat[k],
                final[perm[k]],
            )
            for k in range(4)
        )
        best_cost = min(cost, best_cost)

    return best_cost


T = nn()
for testID in range(1, T+1):
    dat = []
    for k in range(4):
        dat.append(lm())
    out = solve(dat)
    print(out)
