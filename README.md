# Data Structures and Algorithms

C++-latest data structures and algorithms using only standard libraries. This answers many of the challenges in HackerRank, LeetCode and some in Codility.

## Windows

- It uses Visual Studio 2022 IDE, latest Windows SDK and ISO C++20 Standard.

## Ubuntu

- Visual Studio Code with the following extensions:

  - C/C++
  - CMake Tools extension for VS Code

- To convert Visual Studio solution `.sln` and included `.vcxproj` to `CMakeLists.txt`:
  - https://github.com/pavelliavonau/cmakeconverter
  - `cmake-converter -s DataStructuresAlgorithms.sln `

- Install the following packages on Ubuntu:
  - build-essential
  - gdb
  - g++-latest (https://code.visualstudio.com/docs/cpp/cmake-linux)
  - libtbb-dev (Intel® Threading Building Blocks)
  - libgtest-dev
