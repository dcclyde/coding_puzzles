
import copy
from collections import defaultdict
from collections import deque
import math
import sys
import pickle
import bz2
import base64
import fractions

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


def solve_small(dat):
    # only intends to work for the baby case.
    N = len(dat)
    Q = len(dat[0][0])

    possible = ['']
    while len(possible[0]) < Q:
        new_possible = []
        for q in possible:
            new_possible.append(q + 'T')
            new_possible.append(q + 'F')
        possible = new_possible

    # print(f'Possible: {possible}')

    possible_round_2 = []
    for q in possible:
        ok = True
        for answers, score in dat:
            hypothetical_score = 0
            for k in range(Q):
                if answers[k] == q[k]:
                    hypothetical_score += 1

            if hypothetical_score != score:
                ok = False
                break

        if ok:
            possible_round_2.append(q)

    assert len(possible_round_2) > 0

    expected_score = fractions.Fraction(0, 1)
    guesses = []

    for k in range(Q):
        num_T = 0
        num_F = 0
        for q in possible_round_2:
            c = q[k]
            if c == 'T':
                num_T += 1
            else:
                assert c == 'F'
                num_F += 1

        assert num_T + num_F == len(possible_round_2)

        if num_T >= num_F:
            guesses.append('T')
            expected_score += fractions.Fraction(num_T, num_T + num_F)
        else:
            guesses.append('F')
            expected_score += fractions.Fraction(num_F, num_T + num_F)





    return f"{''.join(guesses)} {expected_score.numerator}/{expected_score.denominator}"



T = nn()
for testID in range(1, T+1):
    N, Q = lm()
    dat = []
    for k in range(N):
        answers, score = input().strip().split()
        dat.append((answers, int(score)))
    out = solve_small(dat)
    print('Case #{}: {}'.format(testID, out))
