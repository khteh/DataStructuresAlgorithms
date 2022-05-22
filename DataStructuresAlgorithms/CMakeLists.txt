set(PROJECT_NAME DataStructuresAlgorithmsLib)

################################################################################
# Source groups
################################################################################
set(Headers
    "Call.h"
    "CallHandler.h"
    "Card.h"
    "CircularLinkedList.h"
    "CMatrix.h"
    "DataStructuresAlgorithms.h"
    "DiamondProblem.h"
    "DisJointSet.h"
    "Edge.h"
    "Employee.h"
    "Error.h"
    "FunctionObject.h"
    "Graph.h"
    "Heap.h"
    "interval_map.h"
    "KDTree.h"
    "KnapSack.h"
    "LinkedList.h"
    "ListRangeSum.h"
    "LongestCommonSubsequence.h"
    "LRUCache.h"
    "MyQueue.h"
    "MyStack.h"
    "NameHidingExample.h"
    "Node.h"
    "Poker.h"
    "PrefixTrie.h"
    "PriorityQueueMedian.h"
    "Singleton.h"
    "Square.h"
    "stdafx.h"
    "SuffixTree.h"
    "targetver.h"
    "Tower.h"
    "TreasureGame.h"
    "Tree.h"
    "Trie.h"
    "Twitter.h"
    "Vertex.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "Call.cpp"
    "CallHandler.cpp"
    "Card.cpp"
    "CircularLinkedList.cpp"
    "CMatrix.cpp"
    "DataStructuresAlgorithms.cpp"
    "DiamondProblem.cpp"
    "DisJointSet.cpp"
    "Edge.cpp"
    "Employee.cpp"
    "Error.cpp"
    "FunctionObject.cpp"
    "Graph.cpp"
    "Heap.cpp"
    "interval_map.cpp"
    "KDTree.cpp"
    "KnapSack.cpp"
    "LinkedList.cpp"
    "ListRangeSum.cpp"
    "LongestCommonSubsequence.cpp"
    "LRUCache.cpp"
    "MyQueue.cpp"
    "MyStack.cpp"
    "NameHidingExample.cpp"
    "Node.cpp"
    "Poker.cpp"
    "PrefixTrie.cpp"
    "PriorityQueueMedian.cpp"
    "Singleton.cpp"
    "Square.cpp"
    "stdafx.cpp"
    "SuffixTree.cpp"
    "Tower.cpp"
    "TreasureGame.cpp"
    "Tree.cpp"
    "Trie.cpp"
    "Twitter.cpp"
    "Vertex.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)
set(BUILD_STATIC_LIBS ON)
################################################################################
# Target
################################################################################
#add_executable(${PROJECT_NAME} ${ALL_FILES})
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE DataStructuresAlgorithms)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        $<$<CONFIG:Debug>:
            MultiThreadedDebugDLL
        >
        $<$<NOT:$<OR:$<CONFIG:Debug>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
    )
endif()
#set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 20)

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
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
  message("-- Setting GNU options")
  include_directories("/usr/include/tbb")
  link_directories(${CMAKE_SOURCE_DIR}/lib/x86_64-linux-gnu)
  target_link_libraries(${PROJECT_NAME} tbb)
endif()
################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /MP;
                /std:c++20;
                /Od;
                /GT;
                /arch:AVX;
                /ZI;
                /TP;
                /GR;
                /Y-
            >
            $<$<CONFIG:Release>:
                /std:c++20;
                /O2;
                /Gy;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            /Oi;
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /std:c++20;
                /permissive-;
                /sdl;
                /arch:AVX;
                /Y-
            >
            $<$<CONFIG:Release>:
                /std:c++20;
                /O2;
                /Oi;
                /Gy
            >
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /std:c++20;
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /std:c++20;
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /std:c++20;
                /DEBUG;
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

