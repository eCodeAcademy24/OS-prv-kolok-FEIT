#!/bin/bash
file=$1

if [ -n "$file" ]
then
    cat $file
else
    path=$(find . -name "File.txt")

    if [ -n "$path" ]
    then
        mv $path .
        cat "File.txt"
    else
        echo "File couldn't be found in this directory"
    fi
fi