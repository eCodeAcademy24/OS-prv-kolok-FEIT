#!/bin/bash
if [ "$1" = "1" ]
then
    echo "You have chosen the first option."
elif [ "$1" = "2" ]
then
    echo "You have chosen the second option."
elif [ "$1" = "3" ]
then
    echo "You have chosen the third option."
else
    echo "No valid option chosen."
    echo "Please try again."
fi