
# ChessPlusPlus
#
# Configuration options:
# -DCMAKE_BUILD_TYPE=Release|Debug
# -DSTATIC_BUILD=1|0

cmake_minimum_required (VERSION 2.8)

project (CHESSPP)

if(WIN32)
set(SFMLROOT "" CACHE STRING "Path to SFML root directory")
option(STATIC_BUILD "Link statically")
endif()

if(NOT JSONLIB)
    set(JSONLIB ${CHESSPP_SOURCE_DIR}/lib/json-parser)
endif()
if(NOT BOOSTLIB)
    set(BOOSTLIB ${CHESSPP_SOURCE_DIR}/lib/boost)
endif()
if(NOT SFMLLIB)
    set(SFMLLIB ${CHESSPP_SOURCE_DIR}/lib/SFML)
endif()

include_directories (${JSONLIB}) 
include_directories (${BOOSTLIB})
include_directories (${SFMLLIB}/include)

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
link_directories(${SFMLROOT}/lib)
add_executable (chessplusplus ${CHESSPP_SOURCES})

set(SFMLLIBS sfml-graphics sfml-window sfml-audio sfml-network sfml-system)

if(STATIC_BUILD)
    add_definitions(-DSFML_STATIC)
    foreach(_lib ${SFMLLIBS})
        set(_lib "${_lib}-s")
        list(APPEND TEMPLIBS ${_lib})
    endforeach()
    set(SFMLLIBS ${TEMPLIBS})
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    foreach(_lib ${SFMLLIBS})
        set(_lib "${_lib}-d")
        list(APPEND TEMPLIBS2 ${_lib})
    endforeach()
    set(SFMLLIBS ${TEMPLIBS2})
endif()

target_link_libraries(chessplusplus ${SFMLLIBS} boost_system boost_filesystem)
