clang++ -std=c++11 -o chesspp.exe -isystem lib/boost/boost/ -isystem lib/SFML/include/ -isystem lib/json-parser/ -Llib/SFML/lib/ -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-system -lsfml-window lib/json-parser/json.c src/*.cpp src/board/*.cpp
pause
