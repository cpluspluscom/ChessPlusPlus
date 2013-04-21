clang++ -std=c++11 -o chesspp.exe -isystem lib/boost/boost/ -isystem lib/SFML/include/ -isystem lib/json-parser/ -Llib/SFML/lib/ -lsfml-audio-s -lsfml-graphics-s -lsfml-main -lsfml-system-s -lsfml-window-s lib/json-parser/json.c src/*.cpp src/chesspp/*.cpp src/chesspp/board/*.cpp src/chesspp/graphics/*.cpp src/chesspp/log/*.cpp
pause
