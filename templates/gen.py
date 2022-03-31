import random

def gen_test():
    out = []
    N = random.randint(1, 10)
    out.append(str(N))
    dat = [random.randint(-2, 2) for x in range(N)]
    out.append(' '.join(str(x) for x in dat))

    return ''.join(x + '\n' for x in out)

print(gen_test())
