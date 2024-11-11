#!/bin/bash

files=$(ls .)
arguments=""

for file in $files:
do
    if [ $file != "Problem" ] && [ $file != "4.sh" ]
    then
        wordCount=$(wc -w < $file)

        if [ $wordCount -lt 1000 ]
        then
            echo $(python3 "../Problem 3/Problem 3.py" $file) >> "Output.txt"
        else
            arguments="$arguments $file"
        fi
    fi
done

if [ -n "$arguments" ]
then
    echo $(python3 "../Problem 3/Problem 3.py" $arguments) >> "Output.txt"
fi