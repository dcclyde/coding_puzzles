
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
    out = []
    for k in range(0, len(dat), 2):
        out += [dat[k+1], -dat[k]]

    return out

T = nn()
for testID in range(1, T+1):
    N = nn()
    dat = lm()
    assert len(dat) == N
    out = solve(dat)
    print(' '.join([str(x) for x in out]))
