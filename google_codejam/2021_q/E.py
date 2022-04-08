
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

'''
100 people and 10K questions.
For each person, try to guess his hidden rating?
well, probability of answer 1 given



'''

def solve(dat):
    transpose = [


    # logic logic logic

    return ' '.join(str(q) for q in (N, L, R))

T = nn()
P = nn()
for testID in range(1, T+1):
    dat = []
    for k in range(100):
        dat.append(input().strip())
    out = solve(dat)
    print('Case #{}: {}'.format(testID, out))
