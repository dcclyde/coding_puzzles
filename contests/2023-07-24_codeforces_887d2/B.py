'''
non-decreasing, non-negative integers.

Kth item needs to equal N.

Well, start with a, b.

a
b
a+b
(1, 2)
(2, 3)
(3, 5)


a*F_{k-1} + b*F_k == N
also need b > a.

Find one solution using xgcd.
Then jump around as needed.


// usage: auto [g, coeffs] = gcdExtended(a, b);
pair<ll,pair<ll,ll>> gcdExtended(ll a, ll b) {
    if (b == 0) return {a, {1, 0}};
    auto [d, p] = gcdExtended(b, a % b);
    return {d, {p.second, p.first - p.second * (a / b)}};
}
'''

fib_helper = [1, 0]
def fib(n):
    while len(fib_helper) <= n:
        if fib_helper[-1] > 3e5: return fib_helper[-1]
        fib_helper.append(fib_helper[-1] + fib_helper[-2])
    return fib_helper[n]

def solve_one():
    N, K = list(map(int, input().split()))
    fa = fib(K-1)
    fb = fib(K)
    if fa > N: return 0

    # extended gcd
    p, pa, pb = (fa, 1, 0)
    q, qa, qb = (fb, 0, 1)
    while True:
        if q % p == 0: break
        m = q // p
        r, ra, rb = q%p, qa - m*pa, qb - m*pb

        q, qa, qb = p, pa, pb
        p, pa, pb = r, ra, rb

    assert p == 1
    # pa * fa + pb * fb == 1.

    a = pa * N
    b = pb * N
    '''
    I can get more solutions via
        a += fb
        b -= fa

    I need to count solution pairs that satisfy
        0 <= a
        a <= b
    '''

    # make a barely >= 0.
    if a < 0:
        m = (-a + fb-1) // fb
        a += m*fb
        b -= m*fa
    else:
        m = a // fb
        a -= m*fb
        b += m*fa

    # now, how far could we go before we'd get a > b?
    if a > b: return 0

    starting_difference = b - a
    step_size = fa + fb
    out = starting_difference // step_size + 1
    return out

T = int(input())
for _ in range(T):
    out = solve_one()
    print(out)


'''
OK that might be "correct" but it's clearly not the intended strat.


'''
