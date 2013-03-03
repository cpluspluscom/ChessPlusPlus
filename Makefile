UNAME = $(shell uname -s)

COMPILER_Linux = g++
CXX_FLAGS_Linux = -Wall -std=c++11
DEBUG_LIBS_Linux = -lsfml-system-d -lsfml-window-d -lsfml-graphics-d
RELEASE_LIBS_Linux = -lsfml-system -lsfml-window -lsfml-graphics

COMPILER_Darwin = clang++
CXX_FLAGS_Darwin = -Wall -std=c++11 -stdlib=libc++
DEBUG_LIBS_Darwin = -framework SFML -framework sfml-system -framework sfml-window -framework sfml-graphics
RELEASE_LIBS_Darwin = $(DEBUG_LIBS)

COMPILER = $(COMPILER_$(UNAME))
CXX_FLAGS = $(CXX_FLAGS_$(UNAME))
DEBUG_LIBS = $(DEBUG_LIBS_$(UNAME))
RELEASE_LIBS = $(RELEASE_LIBS_$(UNAME))

DEBUG_PREPROCESSOR = -D_DEBUG
RELEASE_PREPROCESSOR = -D_RELEASE

EXECUTABLE = chesspp
TARGETDIR = ../bin
TARGET = $(TARGETDIR)/$(EXECUTABLE)
SOURCE = $(shell cd src ; ls *.cpp) $(shell cd src ; ls board/*.cpp)

all: debug

debug: CXX_PREPROCESSOR=$(DEBUG_PREPROCESSOR)
debug: LIBS=$(DEBUG_LIBS)
debug: main

release: CXX_PREPROCESSOR=$(RELEASE_PREPROCESSOR)
release: LIBS=$(RELEASE_LIBS)
release: main

main: | bin
	cd src; \
	$(COMPILER) $(CXX_FLAGS) $(CXX_PREPROCESSOR) -o $(TARGET) $(SOURCE) $(LIBS)

bin:
	mkdir bin
