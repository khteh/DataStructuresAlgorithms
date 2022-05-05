#!/bin/bash
valgrind --leak-check=yes --log-file=valgrind.log x64/Debug/InterviewQuestions
echo "Done. Please check valgrind.log"
