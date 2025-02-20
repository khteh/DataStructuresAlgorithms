cmake_minimum_required(VERSION 3.30.3 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)
project(DataStructuresAlgorithms CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "Debug")

# ###############################################################################
# Global compiler options
# https://stackoverflow.com/questions/79444534/vscode-cmake-configure-does-not-generate-cmakecache-txt-from-cmakelists-txt
# CMAKE_CXX_COMPILER_ID is set only at the project() call, when CMake actually detect compilers.
# ###############################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    message("-- Setting GNU options from CMakeLists.txt")
    set(CMAKE_CXX_FLAGS "-std=gnu++23" CACHE STRING "CXX build flags" FORCE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -ggdb3 -Og" CACHE STRING "Debug build flags" FORCE)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG" CACHE STRING "Release build flags" FORCE)
endif()

# ###############################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
# ###############################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()

message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32"
    OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

# ###############################################################################
# Global configuration types
# ###############################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "Configuration" FORCE
)

# ###############################################################################
# Global linker options
# ###############################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

# ###############################################################################
# Nuget packages function stub.
# ###############################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
        "Package \"${PACKAGE}\" with version \"${VERSION}\" "
        "for target \"${TARGET}\" is ignored!")
endfunction()

# ###############################################################################
# Common utils
# ###############################################################################
include(CMake/Utils.cmake)

# ###############################################################################
# Additional Global Settings(add specific info there)
# ###############################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)
include(CTest)
enable_testing()

# ###############################################################################
# Use solution folders feature
# ###############################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# set(BUILD_STATIC_LIBS ON)

# ###############################################################################
# Sub-projects
# ###############################################################################
add_subdirectory(Console)
add_subdirectory(src)
add_subdirectory(test)