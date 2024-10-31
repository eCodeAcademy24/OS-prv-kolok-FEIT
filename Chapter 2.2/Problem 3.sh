#!/bin/bash
path=$(find . -name "Input.txt")

if [ -n "$path" ]
then
    if [ "$path" != "./Input.txt" ]
    then
        mv $path .
    fi

    lines=$(wc -l < "Input.txt")
    echo "The input file has $lines lines in it." >> "Output.txt"
else
    echo "File couldn't be found in this directory!"
fi