
import copy
from collections import defaultdict
from collections import deque
import math
import sys
import pickle
import bz2
import base64

sys.setrecursionlimit(10**6)

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
            base64.b64decode(
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


def solve_small(R, C, dat_pre, dat_post):
    swap_options = defaultdict(list)
    already_ok = 0
    for r in range(R):
        for c in range(C):
            if dat_pre[r][c] == dat_post[r][c]:
                already_ok += 1
                continue
            for dr, dc in [(-1, 0), (0, -1), (1, 0), (0, 1)]:
                rr = r + dr
                cc = c + dc
                if rr < 0 or cc < 0 or rr >= R or cc >= C:
                    continue

                # is this a helpful swap?
                if (
                    dat_pre[r][c] != dat_pre[rr][cc]
                    and
                    dat_pre[rr][cc] != dat_post[rr][cc]
                ):
                    swap_options[(r, c)].append((rr, cc))

    out = R*C - already_ok - len(swap_options)
    while True:
        # print(swap_options)
        if len(swap_options) == 0:
            break
        leaves = [(x, opts[0]) for x, opts in swap_options.items() if len(opts) == 1]
        if len(leaves) > 0:
            # apply the first leaf.
            (r, c), (rr, cc) = leaves[0]
        else:
            # just do some random swap?
            stuff = list(swap_options.items())
            (r, c), options = stuff[0]
            (rr, cc) = options[0]
        # print(f"Swapping {r} {c} with {rr} {cc}")
        dat_pre[r][c] = dat_post[r][c]
        dat_pre[rr][cc] = dat_post[rr][cc]
        out += 1
        del swap_options[(r, c)]
        del swap_options[(rr, cc)]
        for q in list(swap_options.keys()):
            swap_options[q] = [
                (rrr, ccc)
                for rrr, ccc in swap_options[q]
                if (rrr, ccc) not in {(r, c), (rr, cc)}
            ]
            if len(swap_options[q]) == 0:
                del swap_options[q]
                # print(f"Changing {r} {c} the hard way.")
                out += 1
    return out

T = nn()
for testID in range(1, T+1):
    R, C, F, S = lm()
    dat_pre = []
    for r in range(R):
        dat_pre.append(list(input().strip()))
    dat_post = []
    for r in range(R):
        dat_post.append(list(input().strip()))
    out = solve_small(R, C, dat_pre, dat_post)
    print('Case #{}: {}'.format(testID, out))
