#! /usr/bin/bash

if [ $# -ne 1 ]
then
    echo "Need exactly one argument (contest folder name)."
    exit
fi

mkdir "$1"
for PROBLEM in A B C D E F G H
do
    cp "./cftemplate.py" "$1/$PROBLEM.py"
    cp "./cftemplate.cpp" "$1/$PROBLEM.cpp"
    touch "$1/$PROBLEM.in"
done
cd "$1"    
