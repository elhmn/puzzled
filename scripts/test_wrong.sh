#!/bin/bash

TEST_WRONG_DIR=./tests/wrong

COLOR_RED="\033[31m"
COLOR_GREEN="\033[32m"
COLOR_RESET="\033[0m"

for f in $(ls -1 $TEST_WRONG_DIR | grep wrong)
	do
		echo ""
		./puzzled -t "$TEST_WRONG_DIR/$f"
		RET=$?
		if [ $RET -ne 0 ]; then
			echo -e "--> $TEST_WRONG_DIR/$f: failed properly : exited with $RET: $COLOR_GREEN OK $COLOR_RESET"
		else
			echo -e "--> $TEST_WRONG_DIR/$f: exited with $RET: $COLOR_RED FAILURE $COLOR_RESET"
		fi
done
