#!/bin/bash
valgrind --leak-check=yes --log-file=console.log Debug/Console
valgrind --leak-check=yes --log-file=tests.log Debug/DataStructuresAlgorithms.Tests
echo "Done. Please check *.log"
