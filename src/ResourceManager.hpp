#ifndef _RESOURCEMANAGER_H
    #define _RESOURCEMANAGER_H

#include <map>
#include <memory>
#include "Exception.hpp"

#ifdef _DEBUG
    #include <iostream>
    using std::cout; using std::endl;
#endif

namespace chesspp
{
    template <class T, class key_type, class deleter_type = std::default_delete<T>>
    class ResourceManager
    {
    private:
        //no copying
        ResourceManager(const ResourceManager<T, key_type, deleter_type>&);
        ResourceManager<T, deleter_type> &operator=(const ResourceManager<T, key_type, deleter_type>&);

    private:
        typedef std::unique_ptr<T, deleter_type> ptr_t;
        typedef typename std::map<key_type, ptr_t> map_t;
        typedef typename map_t::iterator map_i;

    protected:
        inline ResourceManager() {}
        inline ~ResourceManager() {}

        //pure virtual, defined depending on what is being loaded.
        virtual T *onLoadResource(const key_type &key) = 0;

    public:
        //************************************
        // Method:    Free
        // FullName:  ResourceManager<T, deleter_type>::Free
        // Access:    public
        // Returns:   void
        // Parameter: const std::string & key
        //   Deletes the entry of a key in the resource map.
        //   This will call deleter_type to deallocate the resource from memory as well.
        //************************************
        void Free(const key_type &key) {
            map_i i = m_map.find(key);
            m_map.erase(i);
        }

        //************************************
        // Method:    Load
        // FullName:  ResourceManager<T, deleter_type>::Load
        // Access:    public
        // Returns:   ptr_t
        // Parameter: const std::string & key
        //   Returns a reference to the resource associated with the file name 'key' if it exists in memory.
        //   Otherwise it loads the texture into memory, and returns a reference to the the resource.
        //************************************
        T &Load(const std::string &key)
        {
            map_i i = m_map.find(key);
            if(i != m_map.end())
                return *i->second.get(); //return resource if exists

            //else, load resource
            ptr_t p(onLoadResource(key));
            if(p.get() == NULL)
                throw Exception("Error loading Image at " + key); //figure out better way to throw exceptions later

            m_map.insert(std::make_pair(key, std::move(p)));
            return *m_map[key].get();
        }

    private:
        map_t m_map; //resource map
    };
}

#endif
