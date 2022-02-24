
'''
If all distinct lengths in binary, it's impossible.
(This does NOT cover all impossible cases.)

If 3 consecutive with same binary length, it's possible and answer is 1.

So we only care about cases with 0, 1, 2 of each binary length.

Say we have consecutive items A, B, C with length X, Y, Y.
If length < X, done.
If B ^ C has length > X, we should look somewhere else.

Imagine iterating downward from the top.
Skip until we find 2 consecutive with same length.
DO MYSTERY CHECK TO SEE IF THERE'S A SUITABLE RUN WITH 1 IN 2ND BLOCK.
Combine them and move along.
If next item has smaller length, give up.
If next item has bigger length, this is a potential solution, record it.
If next item has same length, need to do the MYSTERY CHECK again;
    if not, add it to our pile and move on.

'''

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


import math

def binlen(x):
    # I want minimum k such that 2**(k-1) <= x
    base = math.ceil(math.log(x) / math.log(2.))
    base = int(base)
    while (1 << base) > x:
        base -= 1
    while (1 << (base+1)) <= x:
        base += 1
    return base + 1


def solve(out):
    N = len(out)

    '''
    Initial checks:
    If there are 3 in a row of same length, answer is 1.
    '''
    current_len = -1
    num_same = 0
    for q in out:
        new_len = binlen( q )
        if new_len == current_len:
            num_same += 1
            if num_same >= 3:
                return 1
        else:
            current_len = new_len
            num_same = 1

    # If we got this far, there are no 3 in a rows and we have at most ~60 elements.

    prefix_xors = [0]  # px[k] is xor of first k items, from 0 to k-1.
    for q in out:
        prefix_xors.append( prefix_xors[-1] ^ q )
    # prefix_xors = prefix_xors[1:]

    INFINITY = N+1
    best = INFINITY
    for a in range(N):
        for b in range(a+1, N):
            for c in range(b+1, N+1):
                first_xor = prefix_xors[b] ^ prefix_xors[a]
                second_xor = prefix_xors[c] ^ prefix_xors[b]
                if first_xor > second_xor:
                    cost = c-a-2
                    best = min(best, cost)


    if best == INFINITY:
        return -1
    return best




    return ' '.join(str(q) for q in (N, L, R))

N = nn()
dat = lm()
out = solve(dat)
print(out)
