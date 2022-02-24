
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


# return the max possible size of remaining subtree.
def helper(graph, curr, parent):
    if len(graph[curr] - {parent}) <= 1:
        # print(f"parent {parent}, curr {curr}, result 1")
        return 1
    subqueries = {
        q:
        helper(graph, q, curr)
        for q in graph[curr] if q != parent
    }
    sq2 = list(subqueries.items())
    sq2.sort(key=lambda x: -x[1])

    out = sq2[0][1] + sq2[1][1] + 1
    # print(f"parent {parent}, curr {curr}, result {out}")
    return out



def master(graph, root):
    # print(f"Current root is {root}.")
    return helper(graph, root, -1)


'''
Basic plan:
1) Build the graph in a more useful form.
2) For each possible root node, do a recursive pass over the tree.
'''
def solve(N, dat):
    # Step 1: Build the graph.
    graph = [set() for k in range(N)]
    for a, b in dat:
        graph[a].add(b)
        graph[b].add(a)

    # for k in range(N):
    #     print(f"{k}: {graph[k]}")
    # print('')
    # now start iterating I guess?
    vals = [master(graph, root) for root in range(N)]

    return N - max(vals)


T = nn()
for testID in range(1, T+1):
    N = nn()
    dat = []
    for k in range(N-1):
        a, b = lm()
        dat.append((a-1, b-1))
    out = solve(N, dat)
    print('Case #{}: {}'.format(testID, out))
