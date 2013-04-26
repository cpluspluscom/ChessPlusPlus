#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

#include <map>
#include <memory>
#include "Exception.hpp"

namespace chesspp
{
    template<class T, class key_type, class deleter_type = std::default_delete<T>>
    class ResourceManager
    {
        //no copying
        ResourceManager(const ResourceManager<T, key_type, deleter_type>&) = delete;
        ResourceManager<T, deleter_type> &operator=(const ResourceManager<T, key_type, deleter_type>&) = delete;

        using ptr_t = std::unique_ptr<T, deleter_type>;
        using map_t = typename std::map<key_type, ptr_t>;
        using map_i = typename map_t::iterator;

        map_t m_map; //resource map

    protected:
        ResourceManager() noexcept
        {
        }
        ~ResourceManager() noexcept
        {
        }

        //pure virtual, defined depending on what is being loaded.
        virtual T *onLoadResource(key_type const &key) noexcept = 0;

    public:
        //Deletes the entry of a key in the resource map.
        //This will call deleter_type to deallocate the resource from memory as well.
        void Free(key_type const &key) noexcept
        {
            map_i i = m_map.find(key);
            m_map.erase(i);
        }

        //Returns a reference to the resource associated with the file name 'key' if it exists in memory.
        //Otherwise it loads the texture into memory, and returns a reference to the the resource.
        T &Load(key_type const &key) noexcept(false)
        {
            map_i i = m_map.find(key);
            if(i != m_map.end())
            {
                return *i->second.get(); //return resource if exists
            }

            //else, load resource
            ptr_t p {onLoadResource(key)};
            if(p.get() == NULL)
            {
                throw Exception(std::string("Error loading Image at ") + key);
            }

            m_map.insert(std::make_pair(key, std::move(p)));
            return *m_map[key].get();
        }
    };
}

#endif
