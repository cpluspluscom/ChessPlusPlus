#ifndef ChessPlusPlusConfigurationManagerClass_HeaderPlusPlus
#define ChessPlusPlusConfigurationManagerClass_HeaderPlusPlus

#include "Exception.hpp"
#include "util/JsonReader.hpp"

#include <cstring>
#include <cstdint>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <fstream>

#if defined(__linux__)
#include <unistd.h>
#elif defined(_WIN32)
#include <Windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

namespace chesspp
{
    namespace config
    {
        class Configuration
        {
        protected:
            //Linux and Windows, resource path is defined as the absolute path the folder where the application executable is stored.
            //<exe_location>/res/img/... should be where resources are stored.
            //OS x, resource path is defined as the absolute path to the Resources folder of the .app structure.
            //<.app>/Contents/Resources/res/img... should be where resources are stored.
            static std::string getExecutablePath()
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

            std::string res_path;
            util::JsonReader reader;

        private:
            std::string validateConfigFile(std::string const &configFile)
            {
                static std::string exe_path = getExecutablePath();

                if(boost::filesystem::extension(configFile) != ".json")
                {
                    throw Exception("Configuration cannot read non-json config files.");
                }

                if(boost::filesystem::exists(configFile))
                {
                    res_path = "";
                }
                else
                {
                    res_path = exe_path;
                }
                return res_path + configFile;
            }

        public:
            Configuration(const std::string &configFile) noexcept(false)
            : reader(std::ifstream(getExecutablePath() + configFile))
            {
            }
            virtual ~Configuration() = default;
        };
    }
}

#endif
