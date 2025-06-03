set(PROJECT_NAME DataStructuresAlgorithms.Core)

# ###############################################################################
# Source groups
# ###############################################################################
set(Headers
    "Arithmetic.h"
    "Call.h"
    "CallHandler.h"
    "Card.h"
    "CircularLinkedList.h"
    "cout128.h"
    "DataStructuresAlgorithms.h"
    "DiamondProblem.h"
    "Dijkstra.h"
    "DisJointSet.h"
    "DynamicProgramming.h"
    "Edge.h"
    "Employee.h"
    "Error.h"
    "FenwickTree.h"
    "FunctionObject.h"
    "GameTheory.h"
    "GenericConstraints.h"
    "Graph.h"
    "Greedy.h"
    "Heap.h"
    "IIterator.h"
    "InterleavingIterator.h"
    "IntervalMap.h"
    "KDTree.h"
    "Knapsack.h"
    "LinkedList.h"
    "ListRangeSum.h"
    "LongestCommonSubsequence.h"
    "LRUCache.h"
    "Matrix.h"
    "MyQueue.h"
    "MyStack.h"
    "NameHidingExample.h"
    "Node.h"
    "pcg_extras.hpp"
    "pcg_random.hpp"
    "pcg_uint128.hpp"
    "Palindrome.h"
    "pch.h"
    "Permutation.h"
    "Poker.h"
    "PrefixTrie.h"
    "PriorityQueueMedian.h"
    "Range.h"
    "Search.h"
    "Singleton.h"
    "Sort.h"
    "Square.h"
    "SuffixTree.h"
    "targetver.h"
    "Tower.h"
    "TreasureGame.h"
    "Tree.h"
    "Trie.h"
    "Twitter.h"
    "VariantVisitor.h"
    "Vertex.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "Arithmetic.cpp"
    "Call.cpp"
    "CallHandler.cpp"
    "Card.cpp"
    "CircularLinkedList.cpp"
    "cout128.cpp"
    "DataStructuresAlgorithms.cpp"
    "DiamondProblem.cpp"
    "Dijkstra.cpp"
    "DisJointSet.cpp"
    "DynamicProgramming.cpp"
    "Edge.cpp"
    "Employee.cpp"
    "Error.cpp"
    "FenwickTree.cpp"
    "FunctionObject.cpp"
    "GameTheory.cpp"
    "Graph.cpp"
    "Greedy.cpp"
    "Heap.cpp"
    "InterleavingIterator.cpp"
    "IntervalMap.cpp"
    "KDTree.cpp"
    "Knapsack.cpp"
    "LinkedList.cpp"
    "ListRangeSum.cpp"
    "LongestCommonSubsequence.cpp"
    "LRUCache.cpp"
    "Matrix.cpp"
    "MyQueue.cpp"
    "MyStack.cpp"
    "NameHidingExample.cpp"
    "Node.cpp"
    "Palindrome.cpp"
    "pch.cpp"
    "Permutation.cpp"
    "Poker.cpp"
    "PrefixTrie.cpp"
    "PriorityQueueMedian.cpp"
    "Range.cpp"
    "Search.cpp"
    "Singleton.cpp"
    "Sort.cpp"
    "Square.cpp"
    "SuffixTree.cpp"
    "Tower.cpp"
    "TreasureGame.cpp"
    "Tree.cpp"
    "Trie.cpp"
    "Twitter.cpp"
    "VariantVisitor.cpp"
    "Vertex.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

set(BUILD_STATIC_LIBS ON)

# ###############################################################################
# Target
# ###############################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>"
    PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/DataStructuresAlgorithms.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE DataStructuresAlgorithms.Core)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()

# ###############################################################################
# MSVC runtime library
# ###############################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
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
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "WIN32;"
        "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    message("-- Setting GNU options from src/CMakeLists.txt")
    include_directories("/opt/intel/oneapi/tbb/latest/include")
    link_directories(${CMAKE_SOURCE_DIR}/lib/x86_64-linux-gnu)
    target_link_libraries(${PROJECT_NAME} tbb)
endif()

# ###############################################################################
# Compile and link options
# ###############################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /std:C++23;
            /permissive-;
            /sdl;
            /arch:AVX;
            /Y-
            >
            $<$<CONFIG:Release>:
            /std:C++23;
            /O2;
            /Oi;
            /Gy
            >
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()

    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
            /std:C++23;
            /DEBUG;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
            >
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()
