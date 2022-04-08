
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


def solve(N, target_cost):
    cheap = N - 1
    expensive = N*(N+1) // 2 - 1
    if not (cheap <= target_cost <= expensive):
        return 'IMPOSSIBLE'

    final_array = [None for k in range(N)]
    indices = [k for k in range(N)]

    for k in range(N-1):
        max_local_cost = N - k
        selected_local_cost = min(max_local_cost, target_cost - (N-2-k))

        # print(f"Step {k}, target cost {target_cost}, slc {selected_local_cost}, fa {final_array}, indices {indices}")
        # to get the desired cost, I should put item k in position k + selected_local_cost - 1.
        final_array[indices[k + selected_local_cost - 1]] = k + 1
        indices[k : k + selected_local_cost] = indices[k : k + selected_local_cost][::-1]

        target_cost -= selected_local_cost


    return ' '.join(str(q or N) for q in final_array)



T = nn()
for testID in range(1, T+1):
    N, target_cost = lm()
    out = solve(N, target_cost)
    print('Case #{}: {}'.format(testID, out))
