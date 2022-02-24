
import copy
from collections import defaultdict
from collections import deque
import math
import sys
import pickle
import bz2
import base64

import logging
logger = None
# change DEBUG to INFO to block all the debug-level messages.
numeric_log_level = getattr(logging, 'DEBUG', None)
logging.basicConfig(
    stream=sys.stderr,
    format='%(asctime)s.%(msecs)d %(levelname)-8s [%(filename)s:%(lineno)d] %(message)s',
)
logger = logging.getLogger('PUZZLES')
logger.setLevel(numeric_log_level)


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


flip = {'0': '1', '1': '0'}

def solve(source, target):
    N = len(source)
    L = len(source[0])

    targets_set = set(target)

    best = L + 1

    # where does source[0] go?
    for chosen in target:
        flipped = [source[0][k] == chosen[k] for k in range(L)]
        flipped_source = set()
        for k in range(N):
            curr = list(source[k])
            for l in range(L):
                if source[0][l] != chosen[l]:
                    curr[l] = flip[curr[l]]
            curr_str = ''.join(curr)
            if k == 0:
                assert curr_str == chosen
            flipped_source.add(curr_str)

        if flipped_source == targets_set:
            best = min(best, sum(1 for k in range(L) if source[0][k] != chosen[k]))

    if best > L:
        return 'NOT POSSIBLE'
    else:
        return best


T = nn()
for testID in range(1, T+1):
    N, L = lm()
    # Grab N space-separated chunks of length L.
    source = list(input().strip().split())
    target = list(input().strip().split())

    assert len(source) == N
    assert len(target) == N
    for k in range(N):
        assert len(source[k]) == L
        assert len(target[k]) == L

    out = solve(source, target)
    print('Case #{}: {}'.format(testID, out))
