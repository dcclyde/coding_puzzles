import random

def gen_test():
    out = []
    N = random.randint(2, 10)
    print(N)
    dat = [random.randint(1, 100) for _ in range(N)]
    print(' '.join(str(x) for x in dat))
    D = random.randint(1, 10)
    print(D)
    for d in range(D):
        dragon_att = random.randint(1, 1000)
        dragon_def = random.randint(1, 1000)
        print(dragon_def, dragon_att)
    return

gen_test()
