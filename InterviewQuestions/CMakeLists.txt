set(PROJECT_NAME InterviewQuestions)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "Call.h"
    "CallHandler.h"
    "Card.h"
    "CircularLinkedList.h"
    "CMatrix.h"
    "DiamondProblem.h"
    "DisJointSet.h"
    "Edge.h"
    "Employee.h"
    "Error.h"
    "FunctionObject.h"
    "Graph.h"
    "Heap.h"
    "interval_map.h"
    "InterviewQuestions.h"
    "KDTree.h"
    "LinkedList.h"
    "ListRangeSum.h"
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
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "Call.cpp"
    "CallHandler.cpp"
    "Card.cpp"
    "CircularLinkedList.cpp"
    "CMatrix.cpp"
    "DiamondProblem.cpp"
    "DisJointSet.cpp"
    "Edge.cpp"
    "Employee.cpp"
    "Error.cpp"
    "FunctionObject.cpp"
    "Graph.cpp"
    "Heap.cpp"
    "interval_map.cpp"
    "InterviewQuestions.cpp"
    "KDTree.cpp"
    "LinkedList.cpp"
    "ListRangeSum.cpp"
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
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

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
  #include_directories("InterviewQuestions")
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

