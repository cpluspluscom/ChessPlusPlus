#ifndef ChessPlusPlusConfigurationManagerClass_HeaderPlusPlus
#define ChessPlusPlusConfigurationManagerClass_HeaderPlusPlus

#include "Exception.hpp"
#include "util/JsonReader.hpp"

#include <cstring>
#include <cstdint>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <fstream>

namespace chesspp
{
    namespace config
    {
        class Configuration
        {
        protected:
            static std::string executablePath();

            std::string res_path;
            util::JsonReader reader;

        private:
            std::string validateConfigFile(std::string const &configFile)
            {
                static std::string exe_path = executablePath();

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
            Configuration(std::string const &configFile) noexcept(false)
            : reader(std::ifstream(validateConfigFile(configFile)))
            {
            }
            virtual ~Configuration() = default;
        };
    }
}

#endif
