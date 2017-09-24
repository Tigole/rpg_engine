#ifndef _RESOURCE_MANAGER_HPP
#define _RESOURCE_MANAGER_HPP 1

#include <string>

template<class Derived, typename ResourceType>
class ResourceManager
{
public:
	virtual ~ResourceManager(){}

	ResourceType* mt_Get_Resource(const std::string& resource_id)
	{
		//
	}
	void mt_Release_Resource(const std::string& resource_id)
	{
		//
	}

protected:
	bool mt_Load(const std::string& file_path)
	{
		return static_cast<Derived*>(this)->mt_Load(file_path);
	}
};

#endif // _RESOURCE_MANAGER_HPP
