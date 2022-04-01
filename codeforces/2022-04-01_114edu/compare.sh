#! /usr/bin/bash

set -e
# maybe_local="DCCLYDE_LOCAL"
maybe_local="DUMMY"
g++ --std=c++2a "-D$maybe_local" C.cpp -o a.out
g++ --std=c++2a "-D$maybe_local" -DDCCLYDE_BRUTEFORCE C.cpp -o b.out

for((k = 1; k < 100000 ; ++k)); do
    echo $k
    pypy3 gen.py > gen.in
    # a.out < gen.in > fast.out 2> /dev/null
    # b.out < gen.in > brute.out 2> /dev/null
    a.out < gen.in > fast.out
    b.out < gen.in > brute.out
    diff -w fast.out brute.out
done
