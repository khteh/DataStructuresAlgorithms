#!/bin/bash
valgrind --leak-check=full --errors-for-leak-kinds=all --log-file=console.log Debug/Console
valgrind --leak-check=full --errors-for-leak-kinds=all --log-file=tests.log Debug/DataStructuresAlgorithms.Tests
echo "Done. Please check *.log"
