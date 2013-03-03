#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

#include <string.h>
#include <stdint.h>
#include <boost/algorithm/string/replace.hpp>

#if defined(__linux__)
    #include <unistd.h>
#elif defined(_WIN32)
    #include <Windows.h>
#endif


#include "Exception.h"
#include "XMLReader.h"

namespace chesspp
{
    class configuration
    {
        struct _board {
            std::string initial_layout;
            int width, height, cell_width, cell_height;
        } board;

        std::string sprite_board, sprite_pieces, sprite_validMove;
        std::string executable_path;

    public:
        configuration() : executable_path(getExecutablePath()) { 
            XMLReader config(executable_path + "/config.xml");
            
            board.initial_layout = executable_path + config.getProperty<std::string>("chesspp.data.board.initial_layout");
            board.width = config.getProperty<int>("chesspp.data.board.width");
            board.height = config.getProperty<int>("chesspp.data.board.height");
            board.cell_width = config.getProperty<int>("chesspp.data.board.cell_width");
            board.cell_height = config.getProperty<int>("chesspp.data.board.cell_height");

            sprite_board = executable_path + config.getProperty<std::string>("chesspp.images.board");
            sprite_pieces = executable_path + config.getProperty<std::string>("chesspp.images.pieces");
            sprite_validMove = executable_path + config.getProperty<std::string>("chesspp.images.validMove");
        }
        static configuration &instance() {
            static configuration instance;
            return instance;
        }

        std::string getBoardInitialLayout() const { return board.initial_layout; }
        int getBoardWidth() const { return board.width; }
        int getBoardHeight() const { return board.height; }
        int getCellWidth() const { return board.cell_width; }
        int getCellHeight() const { return board.cell_width; }

        std::string getSpritePath_board() const { return sprite_board; }
        std::string getSpritePath_pieces() const { return sprite_pieces; }
        std::string getSpritePath_validMove() const { return sprite_validMove; }

        std::string getExecutablePath() {
            char buf[1024];
            memset(buf, 0, sizeof(buf));
            std::string ret;

#if defined(__linux__)
            if(readlink("/proc/self/exe", buf, sizeof(buf)) == -1)
                throw chesspp::exception("Unable to determine executable path on Linux.");
            ret = buf;

#elif defined(_WIN32)
            if(GetModuleFileNameA(NULL, buf, sizeof(buf)) == 0)
                throw chesspp::exception("Unable to determine executable path on Windows.");
            ret = buf;
            boost::replace_all(ret, "\\", "/");

#else
            throw chesspp::exception("Unknown OS. Unable to determine executable path.");
#endif	

            return ret.substr(0, ret.find_last_of('/')+1);
        }
    }; 
}

#endif