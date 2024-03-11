# Data Structures and Algorithms

C++-latest data structures and algorithms using only standard libraries. This answers many of the challenges in HackerRank, LeetCode and some in Codility.

## Windows

- Use Visual Studio 2022, latest Windows SDK and ISO C++23 Standard.
- Download googletest from https://github.com/google/googletest/releases and extract to C:\Projects\C++\googletest

## Ubuntu

- Visual Studio Code with the following extensions:

  - C/C++
  - CMake Tools extension for VS Code
  - https://marketplace.visualstudio.com/items?itemName=matepek.vscode-catch2-test-adapter

- To convert Visual Studio solution `.sln` and included `.vcxproj` to `CMakeLists.txt`:

  - https://github.com/pavelliavonau/cmakeconverter
  - `cmake-converter -s DataStructuresAlgorithms.sln`

- Install the following packages on Ubuntu:

  - build-essential
  - gdb
  - g++-latest (https://code.visualstudio.com/docs/cpp/cmake-linux)
  - libtbb-dev (Intel® Threading Building Blocks)
  - libgtest-dev
  - ninja-build

- Download googletest from https://github.com/google/googletest/releases and extract to /usr/src/googletest

### Build

- Press `CTRL + SHFT + B` and select one of the options

### Run

- Press `CTRL + F5`
