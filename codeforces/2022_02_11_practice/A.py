
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

'''
After K steps, there are 2^K copies of the original string.
Some are reversed though.
If dat is palindrome, output 1.

'''
def solve(dat, K):
    if K == 0:
        return 1
    if dat == dat[::-1]:
        return 1
    return 2

T = nn()
for testID in range(1, T+1):
    # N <= 100
    # K <= 1000
    N, K = lm()
    dat = input().strip()
    assert len(dat) == N
    out = solve(dat, K)
    print(out)
