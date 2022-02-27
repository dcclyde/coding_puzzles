
import numpy as np
import subprocess
import random

num_tests = 10**6
# num_tests = 1
# H = 5
# W = 6
# num_blocks = (H * W) // 2

def pos_to_str(q):
    h = q // W
    w = q % W
    return f"{h+1} {w+1}\n"

for tidx in range(num_tests):
    if tidx % 10**3 == 0:
        print(tidx)
    H = random.randint(3, 6)
    W = random.randint(3, 6)
    num_blocks = random.randint((H*W) // 4, 3*H*W // 4)
    num_blocks = min(num_blocks, H*W - 2)
    first_line = f"{H} {W} {num_blocks}\n"

    perm = np.random.permutation(H * W)
    with open('F_driver.in', 'w') as f:
        f.write(first_line)
        f.writelines(pos_to_str(q) for q in perm[:num_blocks + 2])

    # run_mine = subprocess.run('./F.prog < F_driver.in > F.out')
    # run_theirs = subprocess.run('./F_knowngood.prog < F_driver.in > F_knowngood.out')
    # cmp = subprocess.run('cmp F.out F_knowngood.out')
    result = subprocess.run(
        ' && '.join([
            './F.prog < F_driver.in > F.out',
            './F_knowngood.prog < F_driver.in > F_knowngood.out',
            'cmp F.out F_knowngood.out',
        ]),
        shell=True,
    )
    if result.returncode != 0:
        print('Found a discrepancy.')
        print(result.stdout)
        break

