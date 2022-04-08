
import random
import numpy as np

MAX = 10**5
NUM_TRIALS = 1000

def run_trial():
    curr = 0
    out = 0
    while curr != MAX:
        curr = random.randint(curr + 1, MAX)
        out += 1
    return out

dat = [run_trial() for k in range(NUM_TRIALS)]
print(np.mean(dat))
