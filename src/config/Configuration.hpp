#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

#include <cstring>
#include <cstdint>
#include <boost/algorithm/string/replace.hpp>
#include <fstream>

#if defined(__linux__)
    #include <unistd.h>
#elif defined(_WIN32)
    #include <Windows.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#endif

#include "Exception.hpp"
#include "util/JsonReader.hpp"
#include "log/Logger.hpp"

namespace chesspp
{
    namespace config
    {
        class Configuration
        {
        protected:
            std::string res_path;

            //Linux and Windows, resource path is defined as the absolute path the folder where the application executable is stored.
            //    <exe_location>/res/img/... should be where resources are stored.
            //OS x, resource path is defined as the absolute path to the Resources folder of the .app structure.
            //    <.app>/Contents/Resources/res/img... should be where resources are stored.
            static std::string getResourcePath()
            {
                
                char buf[1024];
                std::uint32_t size = sizeof(buf);
                memset(buf, 0, size);
                std::string ret;
                #if defined(__linux__)
                     if(readlink("/proc/self/exe", buf, size) == -1)
                         throw Exception("Unable to determine executable path on Linux.");
                     ret = buf;
                     ret = ret.substr(0, ret.find_last_of('/')+1);

                #elif defined(_WIN32)
                     if(GetModuleFileNameA(NULL, buf, size) == 0)
                         throw Exception("Unable to determine executable path on Windows.");
                     ret = buf;
                     boost::replace_all(ret, "\\", "/");
                     ret = ret.substr(0, ret.find_last_of('/')+1);

                #elif defined(__APPLE__)
                     if (_NSGetExecutablePath(buf, &size) != 0)
                         throw Exception("Unable to determine executable path on OS x. (Buffer size too small?)");
                     ret = buf;
                     ret = ret.substr(0, ret.find_last_of('/')+1) + "../Resources/";
                     //Need to go up one directory because the exe is stored in <.app>/Contents/MacOS/,
                     //And we need <.app>/Contents/Resources

                #else
                      throw Exception("Unknown OS. Unable to determine executable path.");
                #endif

                return ret;
            }

            util::JsonReader reader;
        public:
            Configuration(const std::string &configFile) noexcept(false) : res_path(getResourcePath()), reader(std::ifstream(getResourcePath() + configFile))
            {
            }
            virtual ~Configuration() noexcept
            {
            }

        };

        class BoardConfig : public Configuration
        {
            std::string initial_layout;
            std::uint8_t board_width, board_height;
            std::uint16_t cell_width, cell_height;

        public:
            BoardConfig()
            : Configuration("config.json")
            , initial_layout (res_path + std::string(reader()["chesspp"]["board"]["initial_layout"]))
            , board_width(reader()["chesspp"]["board"]["width"])
            , board_height(reader()["chesspp"]["board"]["height"])
            , cell_width(reader()["chesspp"]["board"]["cell_width"])
            , cell_height(reader()["chesspp"]["board"]["cell_height"])
            {
            }

            std::string getInitialLayout() { return initial_layout; }
            uint8_t     getBoardWidth() { return board_width; }
            uint8_t     getBoardHeight() { return board_height; }
            uint16_t    getCellWidth() { return cell_width; }
            uint16_t    getCellHeight() { return cell_height; }
        };

        class GraphicsConfig : public Configuration
        {
            std::string path_board, path_pieces, path_validMove;

        public:
            GraphicsConfig()
            : Configuration("config.json")
            , path_board(res_path + std::string(reader()["chesspp"]["board"]["images"]["board"]))
            , path_pieces(res_path + std::string(reader()["chesspp"]["board"]["images"]["pieces"]))
            , path_validMove(res_path + std::string(reader()["chesspp"]["board"]["images"]["validMove"]))
            {
            }

            std::string getSpritePath_board() { return path_board; }
            std::string getSpritePath_pieces() { return path_pieces; }
            std::string getSpritePath_validMove() { return path_validMove; }
        };
    }
}

#endif
