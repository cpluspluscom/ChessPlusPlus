
# ChessPlusPlus
#
# Configuration options:
# -DCMAKE_BUILD_TYPE=Release|Debug
# -DSTATIC_BUILD=1|0

cmake_minimum_required (VERSION 2.8)

project (CHESSPP)

#Set options
if(WIN32)
    set(SFML_ROOT "" CACHE PATH "Path to SFML root directory")
    set(BOOST_ROOT "" CACHE PATH "Path to Boost root directory")
    set(STATIC_BUILD TRUE CACHE BOOL "Link SFML statically") #option(STATIC_BUILD "Link statically" FALSE)    
endif()

#Add json-parser
if(NOT JSONLIB)
    set(JSONLIB ${CHESSPP_SOURCE_DIR}/lib/json-parser)
endif()
include_directories (${JSONLIB}) 

#Get all source files
file(GLOB_RECURSE CHESSPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE CHESSPP_HEADERS "src/*.hpp")
list(APPEND CHESSPP_SOURCES "lib/json-parser/json.c")

set (CHESSPP_INCLUDE_DIRS "")
foreach (_headerFile ${CHESSPP_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND CHESSPP_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES CHESSPP_INCLUDE_DIRS)
include_directories(${CHESSPP_INCLUDE_DIRS})

# Add C++11 definitions
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # Building with Clang (on OS x at least) requires -stdlib=libc++ flag
    set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
endif()
#list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
 
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
if(STATIC_BUILD)
	set(SFML_STATIC_LIBRARIES TRUE)
else()
	set(SFML_STATIC_LIBRARIES FALSE)
endif()
find_package(SFML 2 REQUIRED graphics window network system audio)
include_directories (${SFML_INCLUDE_DIR})
link_directories(${SFML_ROOT}/lib)

#Detect Boost
find_package(Boost 1.54.0 COMPONENTS filesystem system REQUIRED)
include_directories(${BOOST_ROOT})
set(Boost_LIBRARYDIR ${BOOST_ROOT}/lib)
link_directories(${Boost_LIBRARY_DIR})

#Set static runtime for msvc
if(WIN32)
	if(MSVC AND STATIC_BUILD)
        foreach(flag
                CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
            endif()
        endforeach()
    endif()
endif()

add_executable (chesspp ${CHESSPP_SOURCES})
target_link_libraries(chesspp ${SFML_LIBRARIES} ${Boost_LIBRARIES})
