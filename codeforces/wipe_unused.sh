#! /usr/bin/bash

template_base="/home/dcclyde/puzzles/code/codeforces/cftemplate"
for file in ./*
do
    if [ "$file" = "./*" ]
    then
        break
    fi

    # delete empty files (e.g. *.in)
    if [ ! -s "$file" ]
    then
        echo "Deleting empty file: $file"
        rm "$file"
        continue
    fi

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
done

rm -f a.out  # don't show me an error if this doesn't exist.

# if this whole directory is now empty, delete it.
if [ ! "$(ls -A $(pwd -P))" ]
then
    echo "Deleting the whole directory because it's empty."
    rm -r "$(pwd -P)"
fi
