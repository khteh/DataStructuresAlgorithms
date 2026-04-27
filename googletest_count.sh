#!/bin/bash
#set -x
if [ $# -eq 1 -a -n "$1" ]; then
  testcases=$1
  echo Searching for test suites with less than $testcases test cases...
  ./Debug/DataStructuresAlgorithms.Tests --gtest_list_tests | awk '/^[^ ]/ { if (suite != "" && count < '$testcases') print suite; suite=$1; count=0; next } /^[ ]/ { count++ } END { if (count < '$testcases') print suite }'
else
  echo "Please provide the number of test cases to filter"
fi
