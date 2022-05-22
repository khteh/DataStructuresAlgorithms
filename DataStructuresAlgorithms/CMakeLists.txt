set(PROJECT_NAME InterviewQuestions)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "CMatrix.h"
    "Error.h"
    "LRUCache.h"
    "Poker.h"
    "Trie.h"
    "Call.h"
    "FunctionObject.h"
    "LinkedList.h"
    "PrefixTrie.h"
    "Twitter.h"
    "CallHandler.h"
    "Graph.h"
    "ListRangeSum.h"
    "PriorityQueueMedian.h"
    "Vertex.h"
    "Card.h"
    "Heap.h"
    "LongestCommonSubsequence.h"
    "Singleton.h"
    "interval_map.h"
    "CircularLinkedList.h"
    "IIterator.h"
    "MaxSubsetSumData.h"
    "Square.h"
    "stdafx.h"
    "DiamondProblem.h"
    "InterleavingIterator.h"
    "MyQueue.h"
    "SuffixTree.h"
    "targetver.h"
    "DisJointSet.h"
    "InterviewQuestions.h"
    "MyStack.h"
    "Tower.h"
    "Edge.h"
    "KDTree.h"
    "NameHidingExample.h"
    "TreasureGame.h"
    "Employee.h"
    "KnapSack.h"
    "Node.h"
    "Tree.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "CMatrix.cpp"
    "FunctionObject.cpp"
    "LongestCommonSubsequence.cpp"
    "Square.cpp"
    "Call.cpp"
    "Graph.cpp"
    "MaxSubsetSumData.cpp"
    "SuffixTree.cpp"
    "CallHandler.cpp"
    "Heap.cpp"
    "MyQueue.cpp"
    "Tower.cpp"
    "Card.cpp"
    "InterleavingIterator.cpp"
    "MyStack.cpp"
    "TreasureGame.cpp"
    "CircularLinkedList.cpp"
    "InterviewQuestions.cpp"
    "NameHidingExample.cpp"
    "Tree.cpp"
    "DiamondProblem.cpp"
    "KDTree.cpp"
    "Node.cpp"
    "Trie.cpp"
    "DisJointSet.cpp"
    "KnapSack.cpp"
    "Poker.cpp"
    "Twitter.cpp"
    "Edge.cpp"
    "LRUCache.cpp"
    "PrefixTrie.cpp"
    "Vertex.cpp"
    "Employee.cpp"
    "LinkedList.cpp"
    "PriorityQueueMedian.cpp"
    "interval_map.cpp"
    "Error.cpp"
    "ListRangeSum.cpp"
    "Singleton.cpp"
    "stdafx.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

add_precompiled_header(${PROJECT_NAME} "stdafx.h" "stdafx.cpp")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE InterviewQuestions)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    message("=== x64 Platform ===")
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
    message("-- x64 --")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /permissive-;
                /std:c++20;
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
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

