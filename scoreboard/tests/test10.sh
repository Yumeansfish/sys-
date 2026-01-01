#!/bin/sh
if "$1" 2 <<EOF
aaaaaaaaaaaaaaaaaaaa bbbbbbbbbbbbbbbbbbbb 0 0
cccccccccccccccccccc dddddddddddddddddddd 0 0
eeeeeeeeeeeeeeeeeeee fffffffffffffffffffff 0 0
gggggggggggggggggggg hhhhhhhhhhhhhhhhhhhh 0 0
iiiiiiiiiiiiiiiiiiii jjjjjjjjjjjjjjjjjjjj 0 0
EOF
then 
    echo "the input contains a team name with more than 20 characters" 1>&2
    echo "your program should have failed with exit code EXIT_FAILURE" 1>&2
    exit 1
fi
