#!/bin/bash
# Valgrind cannot run binaries built with the sanitizers, so this uses the linux-valgrind preset.
set -e
cmake --preset linux-valgrind
cmake --build --preset linux-valgrind
bin=build/linux-valgrind/bin/Debug
set +e
valgrind --leak-check=full --errors-for-leak-kinds=all --track-origins=yes --log-file=console.log $bin/Console
valgrind --leak-check=full --errors-for-leak-kinds=all --track-origins=yes --log-file=tests.log $bin/DataStructuresAlgorithms.Tests
echo "Done. Please check *.log"
