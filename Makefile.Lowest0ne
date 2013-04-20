# A MinGW Makefile
# As it uses -std=c++, g++ must be at least Version 4.7  ( $ g++ --version )
# I ended up downloading this: http://nuwen.net/mingw.html

CC = g++
FLAGS = -Wall -std=c++11
OFLAG = $(FLAGS) -c

INCLUDE = -I../../include
LIBDIR  = -L../../lib/sfml
SOURCEDIR = ./src/

ODIR = ./obj/
OBJECTS = $(ODIR)Application.o $(ODIR)AppStateGame.o $(ODIR)Graphics.o\
$(ODIR)Main.o $(ODIR)Pawn.o $(ODIR)Rook.o $(ODIR)Knight.o $(ODIR)Bishop.o\
$(ODIR)Queen.o $(ODIR)King.o $(ODIR)Logger.o $(ODIR)Piece.o $(ODIR)Position.o\
$(ODIR)Board.o
EXECUTABLE = ChessPlusPlus.exe

LIBS =  -lsfml-system -lsfml-window -lsfml-graphics

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(EXECUTABLE)  $(LIBDIR) $(LIBS)

$(ODIR)Application.o: $(SOURCEDIR)Application.cpp $(SOURCEDIR)Application.hpp
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)Application.cpp -o $(ODIR)Application.o

$(ODIR)AppStateGame.o: $(SOURCEDIR)AppStateGame.cpp $(SOURCEDIR)AppStateGame.hpp
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)AppStateGame.cpp -o $(ODIR)AppStateGame.o

$(ODIR)Graphics.o: $(SOURCEDIR)Graphics.cpp $(SOURCEDIR)Graphics.hpp
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)Graphics.cpp -o $(ODIR)Graphics.o

$(ODIR)Main.o: $(SOURCEDIR)Main.cpp 
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)Main.cpp -o $(ODIR)Main.o

$(ODIR)Pawn.o: $(SOURCEDIR)board/Pawn.cpp $(SOURCEDIR)board/Pawn.hpp
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)board/Pawn.cpp -o $(ODIR)Pawn.o

$(ODIR)Rook.o: $(SOURCEDIR)board/Rook.cpp $(SOURCEDIR)board/Rook.hpp
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)board/Rook.cpp -o $(ODIR)Rook.o

$(ODIR)Knight.o: $(SOURCEDIR)board/Knight.cpp $(SOURCEDIR)board/Knight.hpp
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)board/Knight.cpp -o $(ODIR)Knight.o

$(ODIR)Bishop.o: $(SOURCEDIR)board/Bishop.cpp $(SOURCEDIR)board/Bishop.hpp
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)board/Bishop.cpp -o $(ODIR)Bishop.o

$(ODIR)Queen.o: $(SOURCEDIR)board/Queen.cpp $(SOURCEDIR)board/Queen.hpp
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)board/Queen.cpp -o $(ODIR)Queen.o

$(ODIR)King.o: $(SOURCEDIR)board/King.cpp $(SOURCEDIR)board/King.hpp
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)board/King.cpp -o $(ODIR)King.o

$(ODIR)Logger.o: $(SOURCEDIR)board/Logger.cpp $(SOURCEDIR)board/Logger.hpp
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)board/Logger.cpp -o $(ODIR)Logger.o

$(ODIR)Piece.o: $(SOURCEDIR)board/Piece.cpp $(SOURCEDIR)board/Piece.hpp
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)board/Piece.cpp -o $(ODIR)Piece.o

$(ODIR)Position.o: $(SOURCEDIR)board/Position.cpp $(SOURCEDIR)board/Position.hpp
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)board/Position.cpp -o $(ODIR)Position.o

$(ODIR)Board.o: $(SOURCEDIR)board/Board.cpp $(SOURCEDIR)board/Board.hpp
	$(CC) $(OFLAG) $(INCLUDE) $(SOURCEDIR)board/Board.cpp -o $(ODIR)Board.o


clean:
	rm $(OBJECTS) $(EXECUTABLE)