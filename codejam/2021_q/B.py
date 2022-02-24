
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


def solve(X, Y, dat):
    recent = '.'
    out = 0
    for c in dat:
        if c not in 'JC':
            continue
        if c != recent:
            if recent == '.':
                recent = c
                continue
            recent = c
            if c == 'C':
                out += Y
            else:
                out += X

    return out

T = nn()
for testID in range(1, T+1):
    line = input()
    X, Y, dat = line.split()
    X = int(X)
    Y = int(Y)
    out = solve(X, Y, dat)
    print('Case #{}: {}'.format(testID, out))
