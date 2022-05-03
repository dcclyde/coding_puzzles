import random

MAX_N = 25
MAX_ELEMENT = 1000
assert MAX_N * MAX_ELEMENT < (1<<31)

def gen_test():
    N = random.randint(1, MAX_N)
    D = random.randint(0, 9)
    dat = [random.randint(1, MAX_ELEMENT) for _ in range(N)]
    prod = 1
    for k, x in enumerate(dat):
        prod *= x
        if prod >= (1<<63) - 10:
            dat = dat[:k]
            break
    N = len(dat)
    dat.sort()
    print(N, D)
    print(' '.join(str(x) for x in dat))


gen_test()
