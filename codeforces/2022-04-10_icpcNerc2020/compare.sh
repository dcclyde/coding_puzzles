#! /usr/bin/bash
set -e

PROBLEM="D"

# g++ --std=c++2a "$PROBLEM".cpp -o a.out \
#     -DDCCLYDE_LOCAL
# g++ --std=c++2a -DDCCLYDE_BRUTEFORCE "$PROBLEM".cpp -o b.out \
#     -DDCCLYDE_LOCAL

real=0
for((k = 1; k < 100000 ; ++k)); do
    echo "$k    $real"
    pypy3 gen.py > gen.in
    pypy3 D.py < gen.in > fast.out \
        # 2> /dev/null

    # If fast code thinks it's impossible, don't run bruteforce.
    diff -w fast.out dummy.out > /dev/null || continue
    # break
    real=$((real+1))
    pypy3 D_brute.py < gen.in > brute.out \
        2> /dev/null
    echo ""

    diff -w fast.out brute.out
    # python D_verify.py < gen.in
    #     # 2> /dev/null
done
