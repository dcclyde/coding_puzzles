#! /usr/bin/bash

cf_dir="$(dirname $(realpath "$0"))"

if [ $# -ne 1 ]
then
    echo "Need exactly one argument (contest folder name)."
    exit
fi

mkdir -p "$1"
for PROBLEM in A B C D E F G H
do
    cp "$cf_dir/cftemplate.py"  "$1/$PROBLEM.py"
    cp "$cf_dir/cftemplate.cpp" "$1/$PROBLEM.cpp"
    touch "$1/$PROBLEM.in"
done
cd "$1"
