
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

'''
2: Each shelf should be "all even" or "all odd".
3: Each shelf should be like 111111 or 0120120120 or 021021021 mod 3.

Can I actually accomplish the 012012012 version?

0 2 4 6 8 10

'''

def solve(num_shelves, shelf_width):
    out = [
        [
            k * num_shelves + j
            for k in range(shelf_width)
        ]
        for j in range(1, num_shelves + 1)
    ]
    curr = 0
    for k, q in enumerate(out[0]):
        curr += q
        if curr % (k+1) != 0:
            return "NO"

    out = ['YES'] + [
        ' '.join(str(x) for x in q) for q in out
    ]
    return '\n'.join(out)

T = nn()
for testID in range(1, T+1):
    num_shelves, shelf_width = lm()
    out = solve(num_shelves, shelf_width)
    print(out)
