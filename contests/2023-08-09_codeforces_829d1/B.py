
N, X = tuple(map(int, input().split()))
A = list(map(int, input().split()))
A.sort()
A.append(X)

m = 0
b = 1
for x in A:
    while b < x:
        '''
        If I have 12 * 1! and the next term is 3!, I should do:
            12 * 1!
            6 * 2!
            2 * 3!
            then add 1.
        '''
        if m % (b+1) != 0:
            print("No")
            exit(0)
        m //= (b+1)
        b += 1
    m += 1

print("Yes")
exit(0)
