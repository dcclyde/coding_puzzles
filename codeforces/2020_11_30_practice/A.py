
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


def solve(dat):

    pass

T = nn()
for testID in range(1, T+1):
    N, start, period = lm()
    start -= 1  # 1-indexed to 0-indexed
    dat = input().strip()
    x, y = lm()

    out = solve(dat, N, start, period, x, y)
    print(out)
