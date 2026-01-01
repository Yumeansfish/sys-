#!/bin/sh
if "$1" 2 <<EOF
team3 team2 10 2
team2 team1 1 0
team1 team3 100 101
EOF
then 
    echo "the command-line argument specifies a maximum of 2 teams" 1>&2
    echo "but the input contains three teams, therefore" 1>&2
    echo "your program should have failed with exit code EXIT_FAILURE" 1>&2
    exit 1
fi
if "$1" <<EOF
team3 team2 10 2
team2 team1 1 0
team1 team3 100 101
team1 team4 0 0
team1 team5 0 0
team1 team6 0 0
team1 team7 0 0
team1 team8 0 0
team1 team9 0 0
team1 team10 0 0
team1 team11 0 0
EOF
then 
    echo "the default maximum number of teams is 10" 1>&2
    echo "but the input contains 11 teams, therefore" 1>&2
    echo "your program should have failed with exit code EXIT_FAILURE" 1>&2
    exit 1
fi

