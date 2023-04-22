#! /usr/bin/bash

template_dir="$(dirname $(realpath "$0"))"

# Default number of problems to set up.
NUM_PROBLEMS=5

# Check that the number of arguments is either 1 or 2.
if [ $# -eq 0 -o $# -gt 2 ]
then
    echo "Need 1-2 arguments (contest folder name, num problems defaults to $NUM_PROBLEMS)."
    exit
fi

if [ $# -eq 2 ]
then
    if ! [[ $2 =~ ^[1-9]$|^1[0-9]$|^2[0-6]$ ]]
    then
        echo "Second argument must be a number between 1 and 26."
        exit
    fi
    NUM_PROBLEMS=$2
fi
echo "Setting up $NUM_PROBLEMS problems."

mkdir -p "$1"
cp "$template_dir/gen.py" "$1/"
cp "$template_dir/compare.sh" "$1/"
# cp "$template_dir/compare.py" "$1/"
cp "$template_dir/interact.sh" "$1/"
cp "$template_dir/interact.py" "$1/"

# Keep a counter of how many problems we've set up,
# so we can break once we've set up NUM_PROBLEMS.
problem_counter=0

# Also, maintain a list of all the files we've created so we can open them all at once at the end.
files_created=""

for PROBLEM in A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
do
    # Break if we've set up enough problems.
    if [ $problem_counter -eq $NUM_PROBLEMS ]
    then
        break
    fi
    problem_counter=$((problem_counter+1))

    # For each file we're about to create, first check if it already exists.
    # If so, don't overwrite it.

    if [ -f "$1/$PROBLEM.thinking" ]
    then
        echo "File $1/$PROBLEM.thinking already exists. Skipping."
    else
        cp "$template_dir/template.thinking" "$1/$PROBLEM.thinking"
    fi
    files_created="$files_created $1/$PROBLEM.thinking"

    if [ -f "$1/$PROBLEM.cpp" ]
    then
        echo "File $1/$PROBLEM.cpp already exists. Skipping."
    else
        cp "$template_dir/template.cpp"  "$1/$PROBLEM.cpp"
    fi
    files_created="$files_created $1/$PROBLEM.cpp"

    if [ -f "$1/$PROBLEM.in" ]
    then
        echo "File $1/$PROBLEM.in already exists. Skipping."
    else
        touch "$1/$PROBLEM.in"
    fi
    files_created="$files_created $1/$PROBLEM.in"
done

# Open the folder $1 in VS Code, and open all the files we created.
code -n "$1"
code -r $files_created
