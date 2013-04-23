#CXX = g++
CPPFLAGS += -std=c++11 -Wall -Wextra -pedantic-errors
INCLUDE = -I.

ifeq ($(CFG),)
CFG=debug
endif

ifeq ($(CFG),debug)
CPPFLAGS += -ggdb -DDEBUG
else
CPPFLAGS += -O2
endif
CPPFLAGS += $(INCLUDE)


VPATH=src
TARGET=chesscpp.bin

SRC = \
	Queen.cpp \
	Board.cpp \
	Pawn.cpp \
	Position.cpp \
	Bishop.cpp \
	King.cpp \
	Rook.cpp \
	Knight.cpp \
	Piece.cpp \
	Logger.cpp \
	Main.cpp \
	Graphics.cpp \
	Application.cpp \
	AppStateGame.cpp

OBJ = $(patsubst %.cpp, objs.$(CFG)/%.o, ${SRC})
DEP = $(patsubst %.cpp, deps.$(CFG)/%.d, ${SRC})

all: bin.$(CFG)/${TARGET}

bin.$(CFG)/${TARGET}: ${OBJ}
	mkdir -p $(dir $@)
	$(CPP) $^ -o $@

test:
	echo $(OBJ)

deps.$(CFG)/%.d: %.cpp
	mkdir -p $(dir $@)
	$(CPP) -MM -MP $(INCLUDE) $< > $@;

objs.$(CFG)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(cPP) -c $(CPPFLAGS) $< -o $@

.PHONY: clean deps

clean:
	rm -rf objs.$(CFG) bin.$(CFG)


# Unless "make clean" is called, include the dependency files
# which are auto-generated. Don't fail if they are missing
# (-include), since they will be missing in the first invocation!
ifneq ($(MAKECMDGOALS),clean)
-include ${DEP}
endif
