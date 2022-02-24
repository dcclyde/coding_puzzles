
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

def mi():
    return map(int, input().split())

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


def solve(dat, start, targ):
    num_odd = sum(x%2 for x in dat)
    combination = (start + num_odd + targ) % 2
    if combination == 0:
        return "Alice"
    else:
        return "Bob"


T = nn()
for testID in range(1, T+1):
    N, X, Y = lm()
    dat = lm()
    assert len(dat) == N
    out = solve(dat, X, Y)
    print(out)
