#!/bin/bash
# Wrapper script to show .cc file paths in test output

TEST_NAME=$(basename "$1")
TEST_DIR=$(dirname "$1")

echo "Source: ${TEST_DIR}/${TEST_NAME}.cc"
echo "----------------------------------------"
"$@"
