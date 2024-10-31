#!/bin/bash
counter=$1

while [ $counter -gt 0 ]
do
    if [ $counter -eq 1 ]
    then
        echo "$counter second remaining..."
    else
        echo "$counter seconds remaining..."
    fi

    counter=$((counter-1))
    sleep 1
done

echo "The match has officially begun"