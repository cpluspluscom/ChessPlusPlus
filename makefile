#usage 
# make CFG=release

CPP = g++
CC = gcc
CPPFLAGS += -std=c++11 -Wall -Wextra -pedantic-errors
INCLUDE = -isystem lib/json-parser/ -Isrc

LIB = `pkg-config --libs sfml-all` lib/json-parser/json.a

ifeq ($(CFG),)
CFG=debug
endif

ifeq ($(CFG),debug)
CPPFLAGS += -ggdb -DDEBUG
else
CPPFLAGS += -O2
endif
CPPFLAGS += $(INCLUDE)


VPATH=src:src/board/:src/config/:src/graphics/:src/log/:src/util/
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
	$(CPP) $^ $(LIBDIR) $(LIB) -o $@

test:
	echo $(OBJ)
	echo $(DEP)


deps.$(CFG)/%.d: %.cpp
	mkdir -p $(dir $@)
	$(CPP) -MM -MP $(CPPFLAGS) $< | perl -pe 's#^(.*\.o)#deps.$(CFG)/$$1 objs.$(CFG)/$$1#' > $@

objs.$(CFG)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) -c $(CPPFLAGS) $< -o $@

.PHONY: clean deps

clean:
	-rm -r objs.debug deps.debug bin.debug
	-rm -r objs.release deps.release bin.release



# Unless "make clean" is called, include the dependency files
# which are auto-generated. Don't fail if they are missing
# (-include), since they will be missing in the first invocation!
-include ${DEP}
