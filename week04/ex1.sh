#!/bin/sh

gcc ex1.c -o ex1 # compile program if it wasn't

for i in 1 2 3 4 5 6 7 8 9 10
do
    echo "Run #$i ======================================"
    ./ex1
    echo "\n"
done
