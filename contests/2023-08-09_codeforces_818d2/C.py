
def solve():
    N = int(input())
    A = list(map(int, input().split()))
    B = list(map(int, input().split()))

    min_pos = B.index(min(B))
    # put that at the end.
    B = B[min_pos+1:] + B[:min_pos+1]
    A = A[min_pos+1:] + A[:min_pos+1]


    if A[-1] > B[-1]:
        print('NO'); return

    for k in reversed(range(N-1)):
        # print(k, (A[k], B[k]), B[k+1])
        if A[k] > B[k]: print('NO'); return
        if A[k] == B[k]: continue
        if B[k] > B[k+1] + 1: print('NO'); return

    print('YES')
    return


T = int(input())
for _ in range(T):
    solve()
