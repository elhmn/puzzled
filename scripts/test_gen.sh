#!/bin/bash

TEST_GEN_DIR=./gen/

COLOR_RED="\033[31m"
COLOR_GREEN="\033[32m"
COLOR_RESET="\033[0m"

for f in $(ls -1 $TEST_GEN_DIR | grep grid)
	do
		echo ""
		./puzzled -t "$TEST_GEN_DIR/$f" -q
done
