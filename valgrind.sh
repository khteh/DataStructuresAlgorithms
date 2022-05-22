#!/bin/bash
valgrind --leak-check=yes --log-file=valgrind.log x64/Debug/DataStructuresAlgorithms
echo "Done. Please check valgrind.log"
