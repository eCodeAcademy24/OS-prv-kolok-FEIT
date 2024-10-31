#!/bin/bash
file=$1

if [ -n "$file" ]
then
    path=$(find . -name "$file")

    if [ -n "$path" ]
    then
        if [ "$path" != "./${file}" ]
        then
            mv $path .
        fi

        words=$(wc -w < "$file")
        echo "There are $words words in the file."
    else
        echo "File couldn't be found in this directory."
    fi
else
    echo "Invalid call to Shell script!"
fi