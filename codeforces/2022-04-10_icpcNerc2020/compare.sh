#! /usr/bin/bash
set -e

PROBLEM="A"

g++ --std=c++2a "$PROBLEM".cpp -o a.out \
    -DDCCLYDE_LOCAL
g++ --std=c++2a -DDCCLYDE_BRUTEFORCE "$PROBLEM".cpp -o b.out \
    -DDCCLYDE_LOCAL

for((k = 1; k < 100000 ; ++k)); do
    echo $k
    pypy3 gen.py > gen.in
    a.out < gen.in > fast.out \
        # 2> /dev/null
    b.out < gen.in > brute.out \
        # 2> /dev/null
    diff -w fast.out brute.out
done
