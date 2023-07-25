'''
Want the array to be NOT sorted.
Operation: Add 1 to some nontrivial prefix and subtract 1 from the rest.
'''

def solve_one():
    N = int(input())
    A = list(map(int, input().split()))
    min_delta = A[1] - A[0]
    for k in range(1, N-1):
        min_delta = min(min_delta, A[k+1] - A[k])

    # if min_delta is 5, answer is 3.
    # 6 --> 4
    # < 0: 0
    if min_delta < 0: return 0
    else: return min_delta // 2 + 1


T = int(input())
for _ in range(T):
    out = solve_one()
    print(out)