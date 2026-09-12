#!/bin/bash

count=$#
echo "Count of args: $count"

sum=0
for arg in "$@"
do
    sum=$(( sum+arg ))
done

average=$(( sum / count ))
echo "Average: $average"
