
def learn(S):
    steps = 0
    while len(S) > 1:
        print(steps, ' '.join(str(x) for x in S), sep='\t')
        wip = []
        for k in range(len(S)-1):
            wip += (S[k] * (ord(S[k+1]) - ord('0')))
        S = wip
        steps += 1

    print(steps, ' '.join(str(x) for x in S), sep='\t')
    print('')
    return steps

# learn('1212')

N = int(input())
S = input()
A = [int(x) for x in S]

# if there are consecutive non-1s, process will never end.
for k in range(N-1):
    if A[k] != 1 and A[k+1] != 1:
        print(-1)
        exit(0)

'''
Each number x will create (x-1)*r 1s, where r is the number of times x is still present.
A[N-1]: r = 1
A[N-j]: r = j + number of 1s created so far.
'''

ones_created = 0
for k in reversed(range(1, N)):
    ones_created += (A[k] - 1) * (N-k + ones_created)

print(ones_created + N-1)
print(learn(S))













