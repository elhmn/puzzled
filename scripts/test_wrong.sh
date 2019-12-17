#!/bin/sh

TEST_WRONG_DIR=./tests/wrong

for f in $(ls -1 $TEST_WRONG_DIR | grep wrong)
	do
		echo ""
		./puzzled -t "$TEST_WRONG_DIR/$f"
		RET=$?
		if [ $RET -ne 0 ]; then
			echo "--> $TEST_WRONG_DIR/$f: failed properly : exited with $RET: OK"
		else
			echo "--> $TEST_WRONG_DIR/$f: exited with $RET: FAILURE"
		fi
done
