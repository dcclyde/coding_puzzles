import random

N_RANGE = (2, 4)
LR_RANGE = (1, 8)
S_RANGE = (1, 50)

def ri(q):
    return random.randint(q[0], q[1])

def gen_test():
    N = ri(N_RANGE)
    S = ri(S_RANGE)
    print(N, S)
    for _ in range(N):
        L = ri(LR_RANGE)
        R = ri(LR_RANGE)
        if L > R:
            L, R = R, L
        print(L, R)


gen_test()
