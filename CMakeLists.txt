
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

# Add C++11 definitions -- list(append...) will not always work.
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if(APPLE)
        # Building with Clang (on OS x at least) requires -stdlib=libc++ flag
        set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
    endif()
endif()
 
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

# Application bundle if on an apple machine
if(APPLE)
    # Optionally build application bundle
    set(BUILD_APPBUNDLE TRUE CACHE BOOL "Build into OS x Application Bundle.")
    if(BUILD_APPBUNDLE)
        # Set bundle properties
        set(MACOSX_BUNDLE_BUNDLE_NAME ChessPlusPlus)
        set(MACOSX_BUNDLE_INFO_STRING ChessPlusPlus)
        set(MACOSX_BUNDLE_SHORT_VERSION_STRING 0.0.1)
        set(MACOSX_BUNDLE_BUNDLE_VERSION 0.0.1)
        set(MACOSX_BUNDLE_GUI_IDENTIFIER com.cplusplus.chesspp)

        # Throw all the resource paths into a variable
        file(GLOB_RECURSE CHESSPP_RESOURCES
            ${PROJECT_SOURCE_DIR}/res/*
            ${PROJECT_SOURCE_DIR}/config/*)

        # Make sure each resource file gets put in the right directory
        # in the application bundle
        FOREACH(file ${CHESSPP_RESOURCES})
            file(RELATIVE_PATH relPath ${PROJECT_SOURCE_DIR} ${file})
            string(FIND ${relPath} "/" inSubDirectory REVERSE)
            if(${inSubDirectory} GREATER 0)
                string(SUBSTRING ${relPath} 0 ${inSubDirectory} relDir)
                set(PACKAGE_LOCATION Resources/${relDir})
            else()
                set(PACKAGE_LOCATION Resources)
            endif()
            set_source_files_properties(
                ${file}
                PROPERTIES
                MACOSX_PACKAGE_LOCATION
                ${PACKAGE_LOCATION}
                )
        ENDFOREACH()

        add_executable(
            chesspp 
            MACOSX_BUNDLE 
            ${CHESSPP_SOURCES} 
            ${CHESSPP_RESOURCES}
            )
    endif()
endif()
if(NOT APPLE OR NOT BUILD_APPBUNDLE)
    # Copy resources to build directory if build directory is 
    # different from source directory.
    if(NOT ${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
        file(COPY config/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/config/)
        file(COPY res/    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)
    endif()
    add_executable(chesspp ${CHESSPP_SOURCES})
endif()

target_link_libraries(chesspp ${SFML_LIBRARIES} ${Boost_LIBRARIES})