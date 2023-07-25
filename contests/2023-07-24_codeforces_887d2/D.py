
'''
D:
* entries between -N and N. Nonzero.
* can't include both x and -x.

Exactly a_0 entries satisfy b0 + bj > 0.

~~~~~~~~~~~~

I guess I'm basically just choosing signs and ordering
    for values 1, 2, ..., N.

If N is negative, it'll score 0. If positive, it'll score N.
Then N-1 should score "0" or "N-1", but remember the extra...

The biggest positive value will score N (if it exists).
    No, this is wrong.
    Any positive value will score N - (num bigger negative values)

Number of Ns = number of top positives.




'''

def solve_one():
    N = int(input())
    A = list(map(int, input().split()))
    X = [(x, k) for k, x in enumerate(A)]
    X.sort()
    # print('\t', X)

    out = [None for _ in range(N)]
    goal = N
    v = N
    negatives_placed = 0

    # 2 pointers
    L = 0
    R = N-1
    while v > 0:
        # print(out)
        x, k = X[R]
        # print('\t', (x,k), goal, (L,R), v, negatives_placed)
        if x == goal:
            out[k] = v
            v -= 1
            R -= 1
        else:
            # there must be some negatives here.
            num_negatives = goal - x
            # print('\t', num_negatives)
            for j in range(num_negatives):
                lscore, lpos = X[L]
                computed_score = N-v - negatives_placed
                # print('\t\t', j, lscore, computed_score)
                if lscore != computed_score:
                    print("NO")
                    return
                out[lpos] = -v
                negatives_placed += 1
                v -= 1
                L += 1
            goal = x

    print("YES")
    print(' '.join(str(x) for x in out))



T = int(input())
for _ in range(T):
    out = solve_one()
    # print(out)
