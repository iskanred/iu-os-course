#!/bin/bash

FILE=./integer.txt		            # file to to read and write
LOCK="${FILE}.lock"                 # lock file


# Check if file exists
if [ ! -f $FILE ]; then
    echo 0 > $FILE
fi

for i in {1..100}
do
    # Check if there is another proccess using this file
    while [ -f $LOCK ]                  # while lock file exists
    do 
        :				                # do nothing
    done

    ln $FILE $LOCK                      # link lock file

    LASTINT=$( tail -n 1 integer.txt )  # take the last integer from file
    NEWINT=$(( $LASTINT + 1 ))          # add 1 to this integer
    echo "${NEWINT}" >> $FILE           # output the new integer into file

    rm $LOCK                            # remove file
done
