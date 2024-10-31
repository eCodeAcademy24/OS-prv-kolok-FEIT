#!/bin/bash
path=$(find . -name "Input.txt")

if [ -n "$path" ]
then
    if [ "$path" != "./Input.txt" ]
    then
        mv $path .
    fi

    $(sed 's/[0-9][0-9]\/[0-9][0-9]\/[0-9][0-9][0-9][0-9]/Valid Date/' "Input.txt" >> "Output.txt")
    echo "The new contents of the file are"
    cat "Output.txt"
else
    echo "File couldn't be found in this directory!"
fi