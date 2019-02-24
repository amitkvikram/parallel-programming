#!/bin/sh

for i in 1 2 4 8 16 20
do 
    for j in 1 2 3 4 5
    do
        ./$1 $i < $2 
    done
done