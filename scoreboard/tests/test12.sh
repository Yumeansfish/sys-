if "$1" 100000 <<EOF
EOF
then 
    exit 0
else
    echo "your program should have returned a success exit code (EXIT_SUCCESS)" 1>&2
    exit 1
fi
if "$1" 1000000 <<EOF
EOF
then 
    exit 0
else
    echo "your program should have returned a success exit code (EXIT_SUCCESS)" 1>&2
    exit 1
fi
