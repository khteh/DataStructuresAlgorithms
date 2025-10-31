# Data Structures and Algorithms

C++-latest data structures and algorithms using only standard libraries. This answers many of the challenges in HackerRank, LeetCode and some in Codility. > 1000 Google Test cases and counting.

## Dependencies

### Permuted Congruential Generator-64 (PCG64)

- Download the header files from https://github.com/brt-v/pcg-cpp
- Put all the `.hpp` into `src/` folder

## Windows

- Use Visual Studio 2022, latest Windows SDK and ISO C++26 Standard.
- Download googletest from https://github.com/google/googletest/releases and extract to C:\Projects\C++\googletest
- Intel oneAPI toolkits: https://www.intel.com/content/www/us/en/docs/onetbb/get-started-guide/2022-2/overview.html
- Run `C:\Program Files (x86)\Intel\oneAPI\setvars.bat`

### Google Test

#### Build the latest GTest and GMock libraries from source

1. Download GoogleTest source code from https://github.com/google/googletest/releases
2. Open the project folder using VS and generate CMake cache, click “Build All” and it will generate lib files.
3. Create a Google Test project, manage nuget packages and uninstall the package Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn
4. Set the property page

C/C++ > General > Additional Include Directories: adds the googletest/include and googlemock/include paths.
Linker > General > Additional Library Directories: point to the path of the compiled .lib file (e.g. googletest-1.17.0\out\build\x64-debug\lib).
Linker > Input > Additional Dependencies: adds gtest.lib and gtest_main.lib.
C/C++ > Code Generation > Run Library: match the compilation configuration of the Googletest libraries (e.g. MTd for Debug mode)
(5) Then the Google Test project can be built successfully.

#### Use vcpkg

- Use vcpkg to download (Note: Currently in vcpkg, gtest version is 1.14.0)

```
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg integrate install
vcpkg.exe install gtest:x64-windows
Use ‘vcpkg list’ to view installed Google Test versions
Create a Google Test project, manage nuget packages and uninstall the package Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn and then build it.
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
  - Intel oneAPI toolkits: https://www.intel.com/content/www/us/en/docs/oneapi/installation-guide-linux
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
