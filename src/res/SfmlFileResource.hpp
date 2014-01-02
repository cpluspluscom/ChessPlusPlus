#ifndef SfmlFileResourceClass_HeaderPlusPlus
#define SfmlFileResourceClass_HeaderPlusPlus

#include "ResourceManager.hpp"
//#include "SFML.hpp"

#include <iostream>


namespace chesspp
{
    namespace res
    {
        template<typename sfmlT>
        class SfmlFileResource : public ResourceManager::Resource
        {
        public:
            sfmlT res;

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

            operator sfmlT &() noexcept
            {
                return res;
            }
            operator sfmlT const &() const noexcept
            {
                return res;
            }
        };
    }
}

#endif
