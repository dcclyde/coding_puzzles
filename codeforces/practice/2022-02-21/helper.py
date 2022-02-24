
import random

N = 10**7
MIN_LEN = 3
MAX_LEN = 10

print(N)

for _ in range(N):
    local_len = random.randint(MIN_LEN, MAX_LEN)
    print(local_len)
    out = []
    for k in range(local_len):
        out.append(random.randint(1,100))
    print(' '.join(str(x) for x in out))

