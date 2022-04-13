#! /usr/bin/bash

for file in ./*
do
    if [ "$file" = "./*" ]
    then
        echo "Don't run this script from the template directory."
        break
    fi

    # delete empty files (e.g. *.in)
    if [ ! -s "$file" ]
    then
        echo "Delete $file (empty)"
        rm "$file"
        continue
    fi

    # delete files that are unchanged from the template.
    for template_file in /home/dcclyde/puzzles/code/templates/*
    do
        if cmp "$file" "$template_file" &> /dev/null \
            && [ "$(realpath $file)" != "$(realpath $template_file)" ]
        then
            echo "Delete $file     (copy of template)"
            rm "$file"
        fi
    done
done

rm -f a.out  # don't show me an error if this doesn't exist.
rm -f _.out

# if this whole directory is now empty, delete it.
if [ ! "$(ls -A $(pwd -P))" ]
then
    echo "Deleting the whole directory because it's empty."
    rm -r "$(pwd -P)"
fi
