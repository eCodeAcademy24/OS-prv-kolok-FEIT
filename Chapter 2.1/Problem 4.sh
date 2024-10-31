#!/bin/bash
objectList="Chair Desk Watch Key Glass"

for object in $objectList
do
    if [ $object = "Watch" ] || [ $object = "Glass" ]
    then
        echo "The plural of the noun $object is: ${object}es"
    else
        echo "The plural of the noun $object is: ${object}s"
    fi
done