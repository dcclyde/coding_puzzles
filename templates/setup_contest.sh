#! /usr/bin/bash

template_dir="$(dirname $(realpath "$0"))"

if [ $# -ne 1 ]
then
    echo "Need exactly one argument (contest folder name)."
    exit
fi

mkdir -p "$1"
cp "$template_dir/gen.py" "$1/"
cp "$template_dir/compare.sh" "$1/"
for PROBLEM in A B C D E F G H
do
    cp "$template_dir/template.py"  "$1/$PROBLEM.py"
    cp "$template_dir/template.cpp" "$1/$PROBLEM.cpp"
    touch "$1/$PROBLEM.in"
    touch "$1/$PROBLEM.thinking"
done
cd "$1"
