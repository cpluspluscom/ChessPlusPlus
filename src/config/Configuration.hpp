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
            std::string validateConfigFile(std::string const &configFile);

        public:
            Configuration(std::string const &configFile) noexcept(false);
            virtual ~Configuration() = default;
        };
    }
}

#endif
