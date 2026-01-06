#!/bin/sh
"$1" <<EOF
color validcolor 123456
style canary background #f0f0f0 foreground #202020
style style-name background #f0f0f0 foreground #202020 fonz fixed
EOF
if [ "$?" = 0 ]
then
    printf "expecting EXIT_FAILURE result"
    exit 1
fi
exit 0
