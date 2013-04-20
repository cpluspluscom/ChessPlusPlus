#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

#include <cstring>
#include <cstdint>
#include <boost/algorithm/string/replace.hpp>

#if defined(__linux__)
    #include <unistd.h>
#elif defined(_WIN32)
    #include <Windows.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#endif


#include "Exception.hpp"
#include "XMLReader.hpp"
#include "board/logger.hpp"

namespace chesspp
{
    namespace configuration
    {
        class configuration
        {
        protected:
            std::string res_path;

            //Linux and Windows, resource path is defined as the absolute path the folder where the application executable is stored.
            //    <exe_location>/res/img/... should be where resources are stored.
            //OS x, resource path is defined as the absolute path to the Resources folder of the .app structure.
            //    <.app>/Contents/Resources/res/img... should be where resources are stored.
            std::string getResourcePath()
            {
                const uint32_t SIZE = 1024;
                char buf[SIZE];
                memset(buf, 0, SIZE);
                std::string ret;
                #if defined(__linux__)
                     if(readlink("/proc/self/exe", buf, SIZE) == -1)
                         throw chesspp::exception("Unable to determine executable path on Linux.");
                     ret = buf;
                     ret = ret.substr(0, ret.find_last_of('/')+1);

                #elif defined(_WIN32)
                     if(GetModuleFileNameA(NULL, buf, SIZE) == 0)
                         throw chesspp::exception("Unable to determine executable path on Windows.");
                     ret = buf;
                     boost::replace_all(ret, "\\", "/");
                     ret = ret.substr(0, ret.find_last_of('/')+1);

                #elif defined(__APPLE__)
                     if (_NSGetExecutablePath(buf, &size) != 0)
                         throw chesspp::exception("Unable to determine executable path on OS x. (Buffer size too small?)");
                     ret = buf;
                     ret = ret.substr(0, ret.find_last_of('/')+1) + "../Resources/";
                     //Need to go up one directory because the exe is stored in <.app>/Contents/MacOS/,
                     //And we need <.app>/Contents/Resources

                #else
                      throw chesspp::exception("Unknown OS. Unable to determine executable path.");
                #endif

                return ret;
            }

            XMLReader reader;
        public:
            configuration(const std::string &configFile) : res_path(getResourcePath()), reader(getResourcePath() + configFile) {}
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
                initial_layout = res_path + reader.getProperty<std::string>("chesspp.data.board.initial_layout");
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
                path_board = res_path + reader.getProperty<std::string>("chesspp.images.board");
                path_pieces = res_path + reader.getProperty<std::string>("chesspp.images.pieces");
                path_validMove = res_path + reader.getProperty<std::string>("chesspp.images.validMove");
            }

            std::string getSpritePath_board() { return path_board; }
            std::string getSpritePath_pieces() { return path_pieces; }
            std::string getSpritePath_validMove() { return path_validMove; }
        };
    }
}

#endif
