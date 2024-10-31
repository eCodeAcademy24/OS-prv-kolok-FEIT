#!/bin/bash

files=$(ls .)
i=0
required=2
arguments=""

for file in $files
do
    if [ $file != "Problem" ] && [ $file != "2.sh" ]
    then
        arguments="$arguments $file"
        i=$(expr $i + 1)

        if [ $i -eq $required ]
        then
            echo $(python3 "../Problem 1/Problem 1.py" $arguments) >> "Output.txt"
            i=0
            arguments=""
        fi
    fi
done