
import copy
from collections import defaultdict
from collections import deque
import math
import sys

# sys.setrecursionlimit(10**6)

if sys.version_info[0] == 2:
    input = raw_input
else:
    input = sys.stdin.readline

def nn():
    return int(input())

def li():
    return list(input())

def lm():
    return list(map(int, input().split()))

# Snippet for printing while flushing output for interactive problems:
# In python3: print(x, flush=True)
# in python2: print(x) and then sys.stdout.flush()


#########################################################################
# Problem specific code usually goes below this line.
#########################################################################


def solve(dat):
    if dat == sorted(dat):
        return 'NO'
    else:
        return 'YES'




T = nn()
for testID in range(1, T+1):
    N = nn()
    dat = lm()
    assert len(dat) == N
    out = solve(dat)
    print(out)
