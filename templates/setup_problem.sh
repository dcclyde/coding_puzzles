#! /usr/bin/bash

template_dir="$(dirname $(realpath "$0"))"

if [ $# -ne 1 ]
then
    echo "Need exactly 1 argument (problem name)."
    exit
fi

source_file="$template_dir/template.cpp"
# echo "source_file = $source_file"
if [ ! -s "$source_file" ]
then
    echo "Source file not found: $source_file"
    exit
fi

# now do it, but test if file exists first.
target_file="$1.cpp"
# echo "target_file = $target_file"
if [ -e "$target_file" ]
then
    echo "File $target_file exists. Skipping."
else
    cp "$source_file" "$target_file"
fi

if [ -f "$1.thinking" ]
then
    echo "File $1.thinking exists. Skipping."
else
    cp "$template_dir/template.thinking" "$1.thinking"
fi

touch "$1.in"

code "$1.thinking" "$target_file" "$1.in"
