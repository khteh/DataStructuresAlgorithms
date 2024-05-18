set(PROJECT_NAME DataStructuresAlgorithmsTests)

# ###############################################################################
# Source groups
# ###############################################################################
set(Headers
    "pch.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "AnagramTests.cpp"
    "ArithmeticOperationTests.cpp"
    "ArrayNegativePositiveSeriesTests.cpp"
    "BinarySearchTreeTests.cpp"
    "BinaryTreeTests.cpp"
    "CircularLinkedListTests.cpp"
    "DisJointSetTests.cpp"
    "DynamicProgrammingTests.cpp"
    "EulerianPathTests.cpp"
    "GameTheoryTests.cpp"
    "GraphTests.cpp"
    "GreedyAlgorithmTests.cpp"
    "HeapTests.cpp"
    "HIndexTests.cpp"
    "IncreasingSequenceTests.cpp"
    "KnapsackTests.cpp"
    "LinkedListTests.cpp"
    "ListPermutationTests.cpp"
    "LongestCommonSubsequenceTests.cpp"
    "LRUCacheTests.cpp"
    "MatrixTests.cpp"
    "MaxZeroProductTests.cpp"
    "NumbersTests.cpp"
    "PalindromeTests.cpp"
    "pch.cpp"
    "PrefixTrieTests.cpp"
    "QueueTests.cpp"
    "SearchTests.cpp"
    "SortTests.cpp"
    "SparseNumberTests.cpp"
    "StackTests.cpp"
    "StringPermutationTests.cpp"
    "RangeTests.cpp"
    "ReversePolishNotationTests.cpp"
    "SuffixTreeTests.cpp"
    "TreeTests.cpp"
    "TrieTests.cpp"
    "TweeterAPITests.cpp"
    "WordsLadderTests.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

# ###############################################################################
# Target
# ###############################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})
target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)

# ###############################################################################
# MSVC runtime library
# ###############################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        $<$<CONFIG:Debug>:
        MultiThreadedDebugDLL
        >
        $<$<CONFIG:Release>:
        MultiThreadedDLL
        >
        $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        $<$<CONFIG:Debug>:
        MultiThreadedDebugDLL
        >
        $<$<CONFIG:Release>:
        MultiThreadedDLL
        >
        $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
    )
endif()

# set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 23)

# ###############################################################################
# Compile definitions
# ###############################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "UNICODE;"
    "_UNICODE"
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG"
        ">"
        "X64;"
        "_CONSOLE"
    )
endif()

# ###############################################################################
# Compile and link options
# ###############################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /Od;
            /RTC1;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            $<$<CONFIG:Release>:
            /Zi
            >
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /Od;
            /RTC1;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            $<$<CONFIG:Release>:
            /Zi
            >
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()

    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

# ###############################################################################
# Dependencies
# ###############################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    DataStructuresAlgorithms
    gtest
    gtest_main
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    use_package(${PROJECT_NAME} Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn 1.8.1.5)
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    include(GoogleTest) # To use gtest_discover_tests
    gtest_discover_tests(${PROJECT_NAME}) # Runs GTest with CTest
endif()