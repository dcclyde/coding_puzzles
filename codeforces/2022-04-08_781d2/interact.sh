#! /usr/bin/bash
set -e
INTERACTIVE_RUNNER="/home/dcclyde/puzzles/code/templates/interactive_runner.py"

PROBLEM="D"

g++ --std=c++2a "$PROBLEM".cpp -o a.out \
    -DDCCLYDE_LOCAL
# g++ --std=c++2a -DDCCLYDE_BRUTEFORCE "$PROBLEM".cpp -o b.out \
#     -DDCCLYDE_LOCAL

for((k = 1; k < 100000 ; ++k)); do
    echo $k
    python -u "$INTERACTIVE_RUNNER" python -u interact.py -- ./a.out
done
