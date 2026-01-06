#!/usr/bin/python3

import sys

def check_words (l, W):
    for w in W:
        if w not in l:
            return False
    return True

W = sys.argv[1:]
if len(W) > 0:
    for l in sys.stdin:
        if check_words (l, W):
            sys.stdout.write(l)
