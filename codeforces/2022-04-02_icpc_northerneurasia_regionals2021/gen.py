import random

MAX_N = 6
MAX_ELEMENT = 1000
assert MAX_N * MAX_ELEMENT < (1<<31)

def gen_test():
    N = random.randint(1, MAX_N)
    D = random.randint(0, 9)
    dat = [random.randint(1, MAX_ELEMENT) for _ in range(N)]
    dat.sort()
    print(N, D)
    print(' '.join(str(x) for x in dat))


gen_test()
