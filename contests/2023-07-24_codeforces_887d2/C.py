'''
Say I use 2, 5, 10.
I'll remove:
1 3 4 6 7 8 9 11 12 13 14 15        2 5 10
1 4 6 8 9 11 12 14 15 16 17 18      3 7 13
1 6 8 11 12 14 15 17 18 19 20 21    4 9 16
1 8 11 14 15 17 18 20 21            6 12 19

The answer can be big: I could just use 1, 2, 3, 4, 5 and get O(N*K).

Stuff smaller than a_1 is always safe.

Suppose I delete [4, 7] and [10, 11].

~~~~~~~~~

......Hang on, I only need the top1 smallest element.

If 1 is not deleted, just output 1.

Suppose [1, 6] and [10, 12].
K = 5.
[1, 6]: I want to delete first 30 options.


How many numbers <= T will be deleted?
Should be computable within N time?
A = [2, 5, 10]
K = 10
T = 25

10:
    deletes 10, 13, ..., 25.
    Total of 6.

5:
    deletes 5, 7, 9, 12, 15, 18, ..., 24.
    Total of


AAAAAABABABABABABCABCABCABCABC

A A A A A B A B A B A C B A

'''



'''
Trying to debug:
DAYS = 15
A = [1, 5, 12, infinity]
        ^

out = 1
idx = 1
todo = 6

steps_here = 4

out = 6
idx = 2
todo = 2

steps_here = (12-6) // 2 = 3

'''

def solve_one():
    N, DAYS = list(map(int, input().split()))
    A = list(map(int, input().split()))

    if A[0] != 1: return 1
    A.append(int(1e18))
    out = 1
    idx = 1
    todo = DAYS
    while True:
        next_cutoff = A[idx]
        # we'd like to step by idx, todo times.

        # This many steps would take us "to or past" the next cutoff.
        steps_here = (next_cutoff - out + idx-1) // idx
        if todo < steps_here:
            out += idx * todo
            break

        out += idx * (steps_here - 1)
        idx += 1
        todo -= steps_here - 1

    return out




T = int(input())
for _ in range(T):
    out = solve_one()
    print(out)

