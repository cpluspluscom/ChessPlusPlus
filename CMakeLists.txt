cmake_minimum_required(VERSION 3.3)

project(ChessPlusPlus)

# json-parser
add_library(json-parser
	"deps/json-parser/json.c"
)
set_property(TARGET json-parser PROPERTY C_STANDARD 99)
target_include_directories(json-parser
	PUBLIC "deps/json-parser/"
)
target_compile_definitions(json-parser
	PUBLIC JSON_TRACK_SOURCE
)

# Find Boost
find_package(Boost REQUIRED COMPONENTS filesystem system)

# Find SFML
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/deps/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
if(WIN32)
	find_package(SFML 2 REQUIRED COMPONENTS graphics window system audio main)
else()
	find_package(SFML 2 REQUIRED COMPONENTS graphics window system audio)
endif()

# ChessPlusPlus
if(APPLE) # Application bundle if on an apple machine
	# Optionally build application bundle
	set(BUILD_APPBUNDLE FALSE CACHE BOOL "Build into OS x Application Bundle.")
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
			${PROJECT_SOURCE_DIR}/config/*
		)

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
			set_source_files_properties(${file}
				PROPERTIES
					MACOSX_PACKAGE_LOCATION ${PACKAGE_LOCATION}
			)
		ENDFOREACH()
		add_executable(ChessPlusPlus MACOSX_BUNDLE
			"src/Main.cpp"
		)
	endif()
endif()
if(NOT APPLE OR NOT BUILD_APPBUNDLE)
	# Copy resources to build directory if build directory is different from source directory.
	if(NOT ${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
		file(COPY config/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/config/)
		file(COPY res/	  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)
	endif()
	if(WIN32)
		add_executable(ChessPlusPlus WIN32
			"src/Main.cpp"
		)
	else()
		add_executable(ChessPlusPlus
			"src/Main.cpp"
		)
	endif()
endif()
set_property(TARGET ChessPlusPlus PROPERTY CXX_STANDARD 14)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	if(APPLE)
		# Building with Clang (on OS x at least) requires -stdlib=libc++ flag
		set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
		set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
	endif()
endif()
target_include_directories(ChessPlusPlus PUBLIC
	"src/"
	${SFML_INCLUDE_DIR}
	${Boost_INCLUDE_DIRS}
)
target_link_libraries(ChessPlusPlus json-parser ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${Boost_LIBRARIES})
if(SFML_STATIC_LIBRARIES)
	target_link_libraries(ChessPlusPlus z bz2)
endif()

# options
if(WIN32)
	set(CHESSPP_REDIRECT_OUTPUT_DEFAULT ON)
else()
	set(CHESSPP_REDIRECT_OUTPUT_DEFAULT OFF)
endif()
option(CHESSPP_REDIRECT_OUTPUT "Redirects output to files instead of stdout and stderr" ${CHESSPP_REDIRECT_OUTPUT_DEFAULT})
if(CHESSPP_REDIRECT_OUTPUT)
	target_compile_definitions(ChessPlusPlus
		PRIVATE CHESSPP_REDIRECT_OUTPUT
	)
endif()
include(CMakeDependentOption)
CMAKE_DEPENDENT_OPTION(CHESSPP_TRUNC_LOGS "Truncate the log files at the start of the program" ON
	"CHESSPP_REDIRECT_OUTPUT" ON
)
if(CHESSPP_TRUNC_LOGS)
	target_compile_definitions(ChessPlusPlus
		PRIVATE CHESSPP_TRUNC_LOGS
	)
endif()

# Divvy out work to subdirectories
add_subdirectory("src/")
