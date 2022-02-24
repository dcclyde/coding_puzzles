
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
    # logic logic logic

    out = 0
    for j in range(len(dat) - 1):
        k = j
        for x in range(j, len(dat)):
            if dat[x] < dat[k]:
                k = x

        dat[j:k+1] = reversed(dat[j:k+1])
        out += k+1-j
        # print(f"j: {j}, k = {k}, out: {out}, dat: {dat}")

    return str(out)

T = nn()
for testID in range(1, T+1):
    N = nn()
    dat = lm()
    out = solve(dat)
    print('Case #{}: {}'.format(testID, out))
