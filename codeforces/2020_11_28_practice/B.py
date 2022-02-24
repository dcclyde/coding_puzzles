
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


def solve(rows, cols, M, N):
    '''
    Approach:
    - Pick any row, find its first element in a column somewhere. That's now col 1.
    - slot in all the other rows based on where their first element is in column 1.
    '''

    # Find where the 1st element of rows[0] appears in cols.
    fcol = None
    for first_col_idx in range(len(cols)):
        for q in cols[first_col_idx]:
            if q == rows[0][0]:
                fcol = cols[first_col_idx]
                break
        if fcol is not None:
            break

    # Need inverse map for the special column.
    fcol_inv = {
        val: idx
        for idx, val in enumerate(fcol)
    }

    out = [[] for k in range(len(rows))]
    for q in rows:
        # where does rows[k] go?
        pos = fcol_inv[q[0]]
        out[pos] = q

    return out

T = nn()
for testID in range(1, T+1):
    M, N = lm()
    rows = []
    for k in range(M):
        rows.append(lm())
        assert len(rows[-1]) == N
    cols = []
    for k in range(N):
        cols.append(lm())
        assert len(cols[-1]) == M

    out = solve(rows, cols, M, N)
    print(
        '\n'.join(
            ' '.join(
                str(q) for q in row
            )
            for row in out
        )
    )
