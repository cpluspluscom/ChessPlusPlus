#ifndef ChessPlusPlus_Config_ConfigurationManagerClass_HeaderPlusPlus
#define ChessPlusPlus_Config_ConfigurationManagerClass_HeaderPlusPlus

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
        /**
         * \brief
         * Holds configuration settings that affect the behavior of the game.
         * 
         * Configuration files are in JSON format - http://www.json.org/
         */
        class Configuration
        {
        protected:
            /**
             * \brief
             * Get the path to the directory the executable is in.
             * 
             * \return Path to the directory the executable is in.
             */
            static std::string executablePath();

            /**
             * \brief
             * Stores the path to the directory where configuration paths are relative to.
             * 
             * This may not be the same as the directory containing the executable.
             */
            std::string res_path;
            /**
             * \brief
             * The chessp::util::JsonReader for reading the configuration values.
             */
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
            /**
             * \brief
             * Loads the configuration from the given file path.
             * 
             * \param configFile the relative path to the configuration file. Must end in .json
             * \throw chesspp::Exception if the path does not end in .json
             */
            Configuration(std::string const &configFile) noexcept(false)
            : reader{std::ifstream(validateConfigFile(configFile))}
            {
            }
            virtual ~Configuration() = default;

            /**
             * \brief
             * Access values in the configuration.
             * 
             * \param path The path to the value as multiple parameters, e.g. `"a", 1, "c"`
             * \return The requested chesspp::util::JsonReader::NestedValue
             */
            template<typename... Path>
            auto setting(Path const &... path)
            -> decltype(reader.navigate(path...))
            {
                return reader.navigate(path...);
            }
        };
    }
}

#endif
