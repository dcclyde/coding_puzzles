#! /usr/bin/bash
set -e  # Halt on error throughout this script (e.g. if diff finds a difference)

if [ $# -ne 1 ]
then
    echo "Need exactly 1 argument: (problem name)."
    exit
fi

PROBLEM="invalid"
PROBLEM=$1

# commands needed to prepare the solutions.
# just comment out if one/both uses Python or otherwise doesn't need prep.
g++ --std=c++20 "$PROBLEM".cpp -g -O2 -o a.out \
    -DDCCLYDE_LOCAL
g++ --std=c++20 B_correct.cpp -g -O2 -o b.out \
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
