#! /usr/bin/bash
set -e

if [ $# -ne 1 ]
then
    echo "Need exactly 1 argument: (problem name)."
    exit
fi

PROBLEM="invalid"
PROBLEM=$1

# any commands needed to prepare the solutions.
# just comment out if one/both uses Python or otherwise doesn't need prep.
g++ --std=c++20 "$PROBLEM".cpp -g -O2 -o a.out \
    -DDCCLYDE_LOCAL
# g++ --std=c++20 -DDCCLYDE_BRUTEFORCE "$PROBLEM".cpp -g -O2 -o b.out \
#     -DDCCLYDE_LOCAL
g++ --std=c++20 D_other.cpp -g -O2 -o b.out \
    -DMATHDUDE42_LOCAL

for((k = 1; k < 100000 ; ++k)); do
    echo $k
    pypy3 gen.py > gen.in
    a.out < gen.in > fast.out \
        # 2> /dev/null
    b.out < gen.in > brute.out \
        # 2> /dev/null
    # pypy3 brute.py < gen.in > brute.out \
    #     # 2> /dev/null

    diff -w fast.out brute.out
done
