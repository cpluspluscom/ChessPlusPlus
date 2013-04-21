clang++ -std=c++11 -o chesspp.exe -isystem lib/boost/boost/ -isystem lib/SFML/include/ -Llib/SFML/lib/ -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-system -lsfml-window src/*.cpp src/board/*.cpp
pause
