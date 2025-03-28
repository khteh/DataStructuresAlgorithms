# Data Structures and Algorithms

C++-latest data structures and algorithms using only standard libraries. This answers many of the challenges in HackerRank, LeetCode and some in Codility. > 1000 Google Test cases and counting.

## Dependencies

### Permuted Congruential Generator-64 (PCG64)

- Download the zip file from https://www.pcg-random.org/download.html#cpp-implementation
- Extract the zip file and put all the `.hpp` into `src/` folder

## Windows

- Use Visual Studio 2022, latest Windows SDK and ISO C++23 Standard.
- Download googletest from https://github.com/google/googletest/releases and extract to C:\Projects\C++\googletest
- Intel oneAPI toolkits: https://www.intel.com/content/www/us/en/docs/onetbb/get-started-guide/2021-6/install-onetbb-on-windows-os.html
- Run `C:\Program Files (x86)\Intel\oneAPI\setvars.bat`

### Google Test

To use the latest version of Google Test, use vcpkg to install it: https://github.com/microsoft/vcpkg

```
git clone https://github.com/microsoft/vcpkg
cd vcpkg
bootstrap-vcpkg.bat
vcpkg integrate install
vcpkg.exe install gtest:x64-windows
```

## Ubuntu

- Visual Studio Code with the following extensions:

  - C/C++
  - CMake Tools extension for VS Code (https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/how-to.md)
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
  - Intel oneAPI toolkits: https://www.intel.com/content/www/us/en/docs/oneapi/installation-guide-linux/2024-2/overview.html
  - Add the following to `/etc/profile`:

  ```
  [ -f "/opt/intel/oneapi/setvars.sh" ] && . /opt/intel/oneapi/setvars.sh
  ```

- Download googletest from https://github.com/google/googletest/releases and extract to /usr/src/googletest

### Build

- Press `CTRL + SHFT + P`, type `CMAKE: Select Variant` to choose the target build type. For example, "Debug" or "Release".
- Press `CTRL + SHFT + B` and select one of the options

### Run Without Debug

- Press `CTRL + F5`

### Debug

- Press `SHIFT + F5`
