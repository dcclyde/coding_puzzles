import random

MIN_N = 3*10**3
MAX_N = MIN_N
MAX_C = max(5, MIN_N // 10)

def gen_test_v1():
    N = random.randint(MIN_N, MAX_N)
    dat = [random.randint(1, MAX_C) for _ in range(N)]
    print(1)
    print(N)
    print(' '.join(str(x) for x in dat))


def gen_test_v2():
    N = random.randint(MIN_N, MAX_N)
    counts = [0 for x in range(N)]
    counts.append(20)
    dat = []
    for _ in range(N):
        curr = N
        while counts[curr] >= 20:
            curr = random.randint(1, MAX_C)
        dat.append(curr)
        counts[curr] += 1

    print(1)
    print(N)
    print(' '.join(str(x) for x in dat))


def gen_test_v3():
    NUM_TESTS = 37
    print(NUM_TESTS)
    for _ in range(NUM_TESTS):
        N = 80
        total_count = 0
        counts = [0]
        while total_count < N:
            curr_count = min(20, N - total_count)
            counts.append(curr_count)
            total_count += curr_count

        todo = set(range(N))
        dat = [-1 for k in range(N)]
        for k, count in enumerate(counts):
            indices = random.sample(todo, count)
            for q in indices:
                dat[q] = k
                todo.remove(q)

        dat = [1, 2, 3, 4] * 20
        print(N)
        print(' '.join(str(x) for x in dat))


gen_test_v3()
