#! /usr/bin/bash

template_base="/home/dcclyde/puzzles/code/codeforces/cfteplate"
for file in ./*
do
    # delete files that are unchanged from the template.
    for template_suffix in ".cpp" ".py"
    do
        if cmp "$file" "$template_base$template_suffix" &>/dev/null \
            && [ "$file" != "./cftemplate$template_suffix" ]
        then
            echo "Deleting copy of template: $file"
            rm "$file"
        fi
    done

    # also delete empty files (e.g. *.in)
    if [ ! -s "$file" ]
    then
        echo "Deleting empty file: $file"
        rm "$file"
    fi
done
