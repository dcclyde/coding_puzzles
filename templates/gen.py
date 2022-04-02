import random

MAX_A = 0
MAX_SLOPE = 0
MAX_X = 5
NUM_POINTS = 4

def gen_test():
    N = random.randint(3, NUM_POINTS)
    # pick N-1 colinear points.
    a = random.randint(0, MAX_A)
    b = random.randint(-MAX_SLOPE, MAX_SLOPE)
    dat = []
    for _ in range(N-1):
        x = random.randint(-MAX_X, MAX_X)
        y = a*x + b
        dat.append((x, y))

    # pick one non-colinear point.
    x = 0
    y = b
    while a*x + b == y:
        x = random.randint(-MAX_X, MAX_X)
        y = random.randint(-MAX_X, MAX_X)
    dat.append((x, y))
    random.shuffle(dat)

    K = random.randint(1, N)

    print(N, K)
    for q in dat:
        print(q[0], q[1])


gen_test()
