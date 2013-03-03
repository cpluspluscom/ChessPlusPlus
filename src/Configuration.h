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
    namespace configuration
    {
        class configuration
        {
        protected:
            std::string executable_path;
            std::string getExecutablePath()
            {
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

            XMLReader reader;
        public:
            configuration(const std::string &configFile) : executable_path(getExecutablePath()), reader(executable_path + "/" + configFile) {}
            virtual ~configuration() {}
        };

        class BoardConfig : public configuration
        {
            std::string initial_layout;
            uint8_t board_width, board_height;
            uint16_t cell_width, cell_height;

        public:
            BoardConfig() : configuration("config.xml") 
            {
                initial_layout = reader.getProperty<std::string>("chesspp.data.board.initial_layout");
                board_width = reader.getProperty<uint8_t>("chesspp.data.board.width");
                board_height = reader.getProperty<uint8_t>("chesspp.data.board.height");
                cell_width = reader.getProperty<uint16_t>("chesspp.data.board.cell_width");
                cell_height = reader.getProperty<uint16_t>("chesspp.data.board.cell_height");
            }
            
            std::string getInitialLayout() { return initial_layout; }
            uint8_t     getBoardWidth() { return board_width; }
            uint8_t     getBoardHeight() { return board_height; }
            uint16_t    getCellWidth() { return cell_width; }
            uint16_t    getCellHeight() { return cell_height; }
        };

        class GraphicsConfig : public configuration
        {
            std::string path_board, path_pieces, path_validMove;

        public:
            GraphicsConfig() : configuration("config.xml")
            {
                path_board = reader.getProperty<std::string>("chesspp.images.board");
                path_pieces = reader.getProperty<std::string>("chesspp.images.pieces");
                path_validMove = reader.getProperty<std::string>("chesspp.images.validMove");
            }

            std::string getSpritePath_board() { return path_board; }
            std::string getSpritePath_pieces() { return path_pieces; }
            std::string getSpritePath_validMove() { return path_validMove; }
        };
    } 
}

#endif