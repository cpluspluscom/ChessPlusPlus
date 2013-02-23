#ifndef _RESOURCEMANAGER_H
	#define _RESOURCEMANAGER_H

#include <map>
#include <memory>

#ifdef _DEBUG
	#include <iostream>
	using std::cout; using std::endl;
#endif

template <class T, class deleter_type = std::default_delete<T>>
class ResourceManager
{
private:
	//no copying
	ResourceManager(const ResourceManager<T, deleter_type>&);
	ResourceManager<T, deleter_type> &operator=(const ResourceManager<T, deleter_type>&);

private:
	typedef std::unique_ptr<T, deleter_type> ptr_t;
	typedef typename std::map<std::string, ptr_t> map_t;
	typedef typename map_t::iterator map_i;

protected:
	inline ResourceManager() {}
	inline virtual ~ResourceManager() {}

	//pure virtual, defined depending on what is being loaded.
	virtual T *onLoadResource(const std::string &key) {return NULL;}

public:
	//************************************
	// Method:    Free
	// FullName:  ResourceManager<T, deleter_type>::Free
	// Access:    public 
	// Returns:   void
	// Parameter: const std::string & key
	//   Deletes the entry of a key in the resource map. 
	//   Should only be called when the resource is no longer being used by any other object
	//   Otherwise the resource will not deallocate right away. shared_ptr will only deallocate
	//   A resource once the reference count reaches 0. 
	//************************************
	void Free(const std::string &key) {
		map_i i = m_map.find(key);

		#ifdef _DEBUG //reference count should be 1 before calling Free.
			cout << "Reference count of " << key << " before erase(): " << i->second.use_count() << endl;
		#endif

		m_map.erase(i);
	}

	//************************************
	// Method:    Load
	// FullName:  ResourceManager<T, deleter_type>::Load
	// Access:    public 
	// Returns:   ptr_t
	// Parameter: const std::string & key
	//   Returns a shared_ptr to the resource associated with the file name 'key' if it exists in memory.
	//   Otherwise it loads the texture into memory, and returns a shared_ptr of the resource.
	//************************************
	T *Load(const std::string &key)
	{
		map_i i = m_map.find(key);
		if(i != m_map.end())
			return i->second.get(); //return resource if exists

		//else, load resource
		ptr_t p(onLoadResource(key));
		if(p.get() == NULL)
			throw std::exception("Error loading Image!"); //figure out better way to throw exceptions later

		m_map.insert(std::make_pair(key, std::move(p)));
		return m_map[key].get();
	}

private:
	map_t m_map; //resource map
};

#endif