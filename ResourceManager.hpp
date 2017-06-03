#ifndef _RESOURCE_MANAGER_HPP
#define _RESOURCE_MANAGER_HPP 1

#include <string>

template<class Derived, typename ResourceType>
class ResourceManager
{
public:
	virtual ~ResourceManager(){}

	ResourceType* getResource(const std::string& resource_id)
	{
		//
	}
	void releaseResource(const std::string& resource_id)
	{
		//
	}

protected:
	bool load(const std::string& file_path)
	{
		return static_cast<Derived*>(this)->load(file_path);
	}
};

#endif // _RESOURCE_MANAGER_HPP
