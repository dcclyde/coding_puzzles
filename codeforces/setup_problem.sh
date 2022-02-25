#! /usr/bin/bash

cf_dir="$(dirname $(realpath "$0"))"

if [ $# -ne 2 ]
then
    echo "Need exactly 2 arguments (file extension, problem name)."
    exit
fi

source_file="$cf_dir/cftemplate.$1"
# echo "source_file = $source_file"
if [ ! -s "$source_file" ]
then
    echo "Source file not found: $source_file"
    exit
fi

# now do it, but test if file exists first.
target_file="$2.$1"
# echo "target_file = $target_file"
if [ -e "$target_file" ]
then
    echo "File already exists so we won't overwrite. Filename: $target_file"
else
    cp "$source_file" "$target_file"
    touch "$2.in"
fi
