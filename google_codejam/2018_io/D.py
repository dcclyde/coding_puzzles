
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

def lm():
    return list(map(int, input().split()))

# Tries really hard to serialize + compress any input object as a string.
# Useful if I want to precompute something fat, then compress it, then rebuild it when running on Google servers.
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

# Snippet for printing while flushing output for interactive problems:
# In python3: print(x, flush=True)
# in python2: print(x) and then sys.stdout.flush()


#########################################################################
# Problem specific code usually goes below this line.
#########################################################################

MAX = 102
ff = [
    [
        [0.0 for x in range(MAX)]
        for y in range(MAX)
    ]
    for z in range(MAX)
]

# helper for loading from the dp array while ignoring bad indices
def f(a, b, c):
    try:
        return ff[a][b][c]
    except:
        return 0.0  # shouldn't matter, this should always be multiplied by 0.

# need to find a reasonable order in which to fill these in.
# I guess we can go from smallest to largest number of unseen cards?
order_helper = [
    (a, b, c)
    for a in range(MAX)
    for b in range(MAX)
    for c in range(MAX)
]
order_helper = [
    (a, b, c)
    for a, b, c in order_helper
    if a + b + c <= MAX
]

order_helper.sort(key=lambda q: (3*q[0] + 2*q[1] + q[2]))
# logger.debug(order_helper)


for a, b, c in order_helper:
    # a = num sets with 0 seen, b = num sets with 1 seen, c = num with 2 seen.

    # how many unseen cards?
    u = 3*a + 2*b + c
    if u == 0:
        ff[a][b][c] = 0.0
        continue

    if u == 1:
        ff[a][b][c] = 1.0
        continue

    if u == 2:
        if (a, b, c) == (0, 1, 0):
            ff[a][b][c] = 1.0
        else:
            assert (a, b, c) == (0, 0, 2), (a, b, c)
            ff[a][b][c] = 2.0
        continue

    '''
    Several cases for what we draw.

    1) 2
    2) 0 or 1 then something else
    3) 0 or 1 then same number
    '''


    # always list (probability, value).
    cases = [
        (c / u, f(a, b, c-1) + 1),  # 2 first (then finish it off)

        # 1 then same 1
        ((2*b / u) * (1       / (u-1)), f(a   , b-1, c   ) + 1),

        # 0 then same 0 then....
        ((3*a / u) * (2       / (u-1)) * (1       / (u-2)), f( a-1 , b   , c   ) + 1),  # ...same 0 again
        ((3*a / u) * (2       / (u-1)) * (3*(a-1) / (u-2)), f( a-2 , b+1 , c+1 ) + 1),  # ...another 0
        ((3*a / u) * (2       / (u-1)) * (2*b     / (u-2)), f( a-1 , b-1 , c+2 ) + 1),  # ...1
        ((3*a / u) * (2       / (u-1)) * (c       / (u-2)), f( a-1 , b   , c   ) + 2),  # ...2 (then finish the 2 off)

        # remaining cases.....
        ((3*a / u) * (3*(a-1) / (u-1)), f( a-2 , b+2 , c   ) + 1),  # 0 then 0
        ((3*a / u) * (2*b     / (u-1)), f( a-1 , b   , c+1 ) + 1),  # 0 then 1
        ((3*a / u) * (c       / (u-1)), f( a-1 , b+1 , c-1 ) + 2),  # 0 then 2 (spend extra turn killing the 2)

        ((2*b / u) * (3*a     / (u-1)), f( a-1 , b   , c+1 ) + 1),  # 1 then 0
        ((2*b / u) * (2*(b-1) / (u-1)), f( a   , b-2 , c+2 ) + 1),  # 1 then 1
        ((2*b / u) * (c       / (u-1)), f( a   , b-1 ,  c  ) + 2),  # 1 then 2 (then finish the 2)

    ]


    total_prob = sum(q[0] for q in cases)
    assert abs(total_prob - 1.0) < 1e-6
    ff[a][b][c] = sum(q[0] * q[1] for q in cases)



def solve(N):
    return ff[N][0][0]


T = nn()
for testID in range(1, T+1):
    N = nn()
    out = solve(N)
    print('Case #{}: {}'.format(testID, out))
