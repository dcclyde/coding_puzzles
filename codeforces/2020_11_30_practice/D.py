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


def solve(N, X, dat):
    prefix_less_than_x_end = -1
    sorted_suffix_beginning = N - 1
    num_swaps = 0
    for i in reversed(range(N - 1)):
        if dat[i] > dat[i + 1]:
            break
        else:
            sorted_suffix_beginning = i


    # print(f"ssb: {sorted_suffix_beginning}")


    for i in range(N):
        if i >= sorted_suffix_beginning:
            if i > 0 and dat[i] < dat[i - 1]:
                return -1
            return num_swaps
        if dat[i] <= X:
            # not allowed to do anything here.
            pass
        else:
            # do a swap.
            (X, dat[i]) = (dat[i], X)
            num_swaps += 1

        if i > 0 and dat[i] < dat[i - 1]:
            return -1




    for i in range(N):
        if dat[i] <= X:
            if i > 0 and dat[i] < dat[i - 1]:
                return -1
            if i >= sorted_suffix_beginning:
                return num_swaps
            continue
        temp = dat[i]
        (X, dat[i]) = (dat[i], X)
        num_swaps += 1
    return num_swaps



    for i in range(N):
        if i > 0 and dat[i] < dat[i-1] and X < dat[i-1]:
            return -1
        if i >= sorted_suffix_beginning:
            return num_swaps
        if dat[i] <= X:
            continue
        (X, dat[i]) = (dat[i], X)
        num_swaps += 1
    return num_swaps





T = nn()
for testID in range(1, T+1):
    N, X = lm()
    dat = lm()
    out = solve(N, X, dat)
    print(out)
