#!/bin/bash
valgrind --leak-check=yes --log-file=valgrind.log Debug/Console
echo "Done. Please check valgrind.log"
