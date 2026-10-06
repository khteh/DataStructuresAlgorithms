# Data Structures and Algorithms

C++-latest data structures and algorithms using only standard libraries. This answers many of the challenges in HackerRank, LeetCode and some in Codility. > 1400 Google Test cases and counting.

## Dependencies

### Permuted Congruential Generator-64 (PCG64)

- Download the header files from https://github.com/brt-v/pcg-cpp
- Put all the `.hpp` into `src/` folder

## Windows

- Use Visual Studio 2022, latest Windows SDK and ISO C++26 Standard.
- Download googletest from https://github.com/google/googletest/releases and extract to C:\Projects\C++\googletest
- Intel oneAPI toolkits: https://www.intel.com/content/www/us/en/docs/onetbb/get-started-guide
- Intel oneAPI TBB: https://www.intel.com/content/www/us/en/developer/tools/oneapi/onetbb-download.html
- Run `C:\Program Files (x86)\Intel\oneAPI\<version>\oneapi-vars.bat`
- Run `C:\Program Files (x86)\Intel\oneAPI\setvars.bat`

### Google Test

#### Build the latest GTest and GMock libraries from source

1. Download GoogleTest source code from https://github.com/google/googletest/releases
2. To build dynamically-link library with address sanitizer, open Developer Command Prompt in Visual Studio and run the following commands in sequence:

   i.  `rmdir /s /q build`
   ii. `cmake -S . -B build -G "Visual Studio 18 2026" -A x64 -DBUILD_SHARED_LIBS=ON -Dgtest_force_shared_crt=ON -Dgtest_build_tests=OFF -Dgmock_build_tests=OFF -DCMAKE_CXX_FLAGS="/fsanitize=address" -DCMAKE_C_FLAGS="/fsanitize=address"`
   iii.`cmake --build build --config Debug --target gtest`. Copy `build/bin/Debug/gtest.dll` to `test/x64/Debug`.
   iv. `cmake --build build --config Release --target gtest`. Copy `build/bin/Release/gtest.dll` to `test/x64/Release`.
	
   Note: `gtest_main.dll` is not required for the application to link against the library.
		 The `gtest_main` target simply provides a tiny boilerplate main function that initializes GoogleTest and runs the tests automatically. 
		 Because we skipped building it to bypass the MSVC C2491 compiler error, use `main.cpp` to provide own entry point.
3. Create a Google Test project, manage nuget packages and uninstall the package Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn
4. Set the property page
   ```
   C/C++ > General > Additional Include Directories: adds the googletest/include and googlemock/include paths.
   Linker > General > Additional Library Directories: point to the path of the compiled .lib file (e.g. googletest\build\lib\Debug OR googletest\build\lib\Release).
   Linker > Input > Additional Dependencies: adds gtest.lib.
   C/C++ > Code Generation > Run Library: match the compilation configuration of the Googletest libraries (e.g. MTd for Debug mode)
   ```
5. Then the Google Test project can be built successfully.

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

## Address Sanitizer

### Google Test

- Add the following to `CMakeSettings.json` in the downloaded source of google test:

  ```
  "addressSanitizerEnabled": true,
  ```

- Add the path of `clang_rt.asan_dynamic-x86_64.dll` to User and System environment variables. At the time of this writing and for Visual Studio 2026, the path is `C:\Program Files\Microsoft Visual Studio\18\Insiders\VC\Tools\MSVC\14.51.36231\bin\Hostx64\x64`

## Ubuntu

- Visual Studio Code with the following extensions:
  - C/C++
  - CMake Tools extension for VS Code (https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/how-to.md)
  - https://marketplace.visualstudio.com/items?itemName=matepek.vscode-catch2-test-adapter

- To convert Visual Studio solution `.slnx` and included `.vcxproj` to `CMakeLists.txt`:
  - https://github.com/pavelliavonau/cmakeconverter
  - `cmake-converter -s DataStructuresAlgorithms.slnx`

- Install the following packages on Ubuntu:
  - build-essential
  - gdb
  - g++-latest (https://code.visualstudio.com/docs/cpp/cmake-linux)
  - libtbb-dev (Intel® Threading Building Blocks)
  - libgtest-dev
  - ninja-build
  - Intel oneAPI toolkits:
    - https://www.intel.com/content/www/us/en/docs/oneapi/installation-guide-linux
    - https://www.intel.com/content/www/us/en/docs/oneapi-toolkit/installation-guide-linux/latest/install-oneapi-toolkit-with-apt.html
  - Intel oneAPI TBB: https://www.intel.com/content/www/us/en/developer/tools/oneapi/onetbb-download.html
  - Add the following to `/etc/profile`:
    ```
    [ -f "/opt/intel/oneapi/setvars.sh" ] && . /opt/intel/oneapi/setvars.sh
    ```

- Optional: Download googletest from https://github.com/google/googletest/releases and extract to /usr/src/googletest
- To check the `libgtest-dev` installed:
  ```
  $ dpkg -s libgtest-dev | grep Version
  ```

### Build

The build configurations are defined in `CMakePresets.json`:

| Configure preset | Build / test presets                         | Sanitizers | Binaries                          |
| ---------------- | -------------------------------------------- | ---------- | --------------------------------- |
| `linux-asan`     | `linux-asan-debug`, `linux-asan-release`     | On         | `./Debug`, `./Release`            |
| `linux-release`  | `linux-release`                              | Off (LTO)  | `build/linux-release/bin/Release` |
| `linux-valgrind` | `linux-valgrind`                             | Off        | `build/linux-valgrind/bin/Debug`  |
| `windows-msvc`   | `windows-msvc-debug`, `windows-msvc-release` | n/a        | `.\Debug`, `.\Release`            |

Put machine-specific presets in `CMakeUserPresets.json` (git-ignored).

#### Command line

```
$ cmake --list-presets
$ cmake --preset linux-asan
$ cmake --build --preset linux-asan-debug
$ ctest --preset linux-asan-debug
```

- `./valgrind.sh` configures and builds the `linux-valgrind` preset and runs Valgrind on it.

#### Visual Studio Code

- Press `CTRL + SHFT + P` + `CMAKE: Select Configure Preset` and choose a preset. For example, "Linux GCC + sanitizers". This replaces `CMAKE: Select Variant`.
- Press `CTRL + SHFT + P` + `CMAKE: Select Build Preset` to choose the target build type. For example, "Debug + sanitizers".
- Press `CTRL + SHFT + P` + `CMAKE: Configure` - This needs to be done after `rm -rf build/` folder.
- Press `CTRL + SHFT + B` and select one of the options
- The launch configurations in `.vscode/launch.json` debug the binaries in `./Debug`, i.e. the `linux-asan-debug` build preset.

### Debug / Run

| Key       | What it runs                                               | Under gdb? |
| --------- | ---------------------------------------------------------- | ---------- |
| F5        | The selected launch.json entry                             | Yes        |
| CTRL + F5 | "CMake: Debug" on the pane's debug target                  | Yes        |
| SHFT + F5 | "CMake: Run Without Debugging" on the pane's launch target | No         |

- The entries in `launch.json` only run with `F5`, using whichever one is selected in the "Run and Debug" dropdown.

## Continuous Integration:

- Integrated with CircleCI
