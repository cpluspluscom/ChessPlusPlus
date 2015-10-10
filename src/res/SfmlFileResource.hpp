#ifndef chesspp_res_SfmlFileResource_HeaderPlusPlus
#define chesspp_res_SfmlFileResource_HeaderPlusPlus

#include "ResourceManager.hpp"
//#include "SFML.hpp"

#include <iostream>

namespace chesspp
{
    namespace res
    {
        /**
         * \brief
         * Wrap an SFML class for use with the ResourceManager as a file resource.
         * 
         * Any SFML class which supports `.loadFromFile()` can be used, such as sf::Sprite and
         * sf::Font.
         * 
         * \tparam The SFML class to wrap.
         */
        template<typename sfmlT>
        class SfmlFileResource
        : public ResourceManager::Resource
        {
        public:
            /**
             * \brief
             * The wrapped SFML class instance.
             */
            sfmlT res;

            /**
             * \brief
             * Construct the wrapper from a file.
             *
             * \note
             * This constructor does not throw, instead it logs an error report to std::cerr
             * 
             * \param file_path The file path.
             */
            SfmlFileResource(std::string const &file_path) noexcept
            {
                if(!res.loadFromFile(file_path))
                {
                    std::cerr << "SFML Resource failed to load \""
                              << file_path << "\" for "
                              << typeid(sfmlT).name() << std::endl;
                }
                else
                {
                    std::clog << "SFML Resource loaded \""
                              << file_path << "\" for "
                              << typeid(sfmlT).name() << std::endl;
                }
            }

            /**
             * \brief
             * Implicitly cast the wrapper to the wrapped resource instance.
             */
            operator sfmlT &() noexcept
            {
                return res;
            }
            /**
             * \brief
             * Implicitly cast the wrapper to the wrapped resource instance.
             */
            operator sfmlT const &() const noexcept
            {
                return res;
            }
        };
    }
}

#endif
