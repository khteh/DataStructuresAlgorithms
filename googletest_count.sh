#!/bin/bash
#set -x
testcases=${1:?"Please provide the number of test cases to filter"}
echo Searching for test suites with less than $testcases test cases...
./Debug/DataStructuresAlgorithms.Tests --gtest_list_tests | awk '/^[^ ]/ { if (suite != "" && count < '$testcases') print suite; suite=$testcases; count=0; next } /^[ ]/ { count++ } END { if (count < '$testcases') print suite }'
