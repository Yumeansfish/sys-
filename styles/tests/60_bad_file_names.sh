#!/bin/sh
"$1" D035_N07_3X15T <<EOF
style canary background #f0f0f0 foreground #202020
EOF
if [ "$?" = 0 ]
then
    printf "expecting EXIT_FAILURE result"
    exit 1
fi
exit 0
