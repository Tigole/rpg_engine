#ifndef _RESOURCE_MANAGER_HPP
#define _RESOURCE_MANAGER_HPP 1

#include <string>
#include <unordered_map>
#include <memory>
#include <utility>

#include <SFML/System.hpp>

#include "XMLFileLoader.hpp"

class IResourceManager
{
public:
	virtual ~IResourceManager(){}

	virtual void mt_Load_Resource_Paths(const std::string& conf_file) = 0;
};

template<typename ResourceType>
using ResourcePair = std::pair<std::unique_ptr<ResourceType>, unsigned int>;
template<typename ResourceType>
using ResourceContainer = misc::UnorderedMap<std::string, ResourcePair<ResourceType>>;
using PathContainer = misc::UnorderedMap<std::string, std::string>;

template<class Derived, typename ResourceType>
class ResourceManager : public IResourceManager
{
public:
	ResourceManager(const std::string& resource_path, const std::string& xml_path)
		:m_resources(),
		m_paths(),
		m_resource_path(resource_path),
		m_xml_path(xml_path),
		m_mutex()
	{}
	virtual ~ResourceManager(){}

	bool mt_Require_Resource(const std::string& resource_id)
	{
		sf::Lock(m_mutex);
		ResourcePair* l_resource(nullptr);
		bool l_b_ret;

		l_resource = mt_Find_Resource(resource_id);
		if (l_resource == nullptr)
		{
			l_b_ret = (mt_Load_Resource(resource_id) != nullptr);
		}
		else
		{
			l_b_ret = true;
		}

		return l_b_ret;
	}

	ResourceType* mt_Get_Resource(const std::string& resource_id)
	{
		sf::Lock l_lock(m_mutex);
		ResourcePair<ResourceType>* l_resource;
		ResourceType* l_ret(nullptr);

		l_resource = mt_Find_Resource(resource_id);

		if (l_resource != nullptr)
		{
			l_ret = l_resource->first.get();
			l_resource->second++;
		}
		else
		{
			l_ret = mt_Load_Resource(resource_id);
		}

		return l_ret;
	}
	
	void mt_Release_Resource(const std::string& resource_id)
	{
		sf::Lock l_lock(m_mutex);
		ResourcePair<ResourceType>* l_resource;

		l_resource = mt_Find_Resource(resource_id);

		if (l_resource != nullptr)
		{
			l_resource->second--;
			if (l_resource->second == 0)
			{
				mt_Unload_Resource(resource_id);
			}
		}
	}

	virtual void mt_Load_Resource_Paths(const std::string& conf_file)
	{
		XMLFileLoader l_loader;

		l_loader.mt_Set_File(conf_file);
		l_loader.mt_Add_On_Entry_Callback(conf_file, m_xml_path, &ResourceManager<Derived, ResourceType>::mt_Load_XML_Resource, this);

		l_loader.mt_Start();

		l_loader.mt_Wait_For_Ending();

		mt_Dump();
	}

	void mt_Dump() const
	{
		log().mt_Entrance_Function(FUNCTION_NAME);

		for (const auto& path : m_paths)
			log() << "id : " << path.first << "\t path : " << path.second << "\n";

		log().mt_Exit_Function();
	}

protected:
	bool mt_Load(ResourceType* resource, const std::string& file_path)
	{
		return static_cast<Derived*>(this)->mt_Load(resource, file_path);
	}

private:
	ResourcePair<ResourceType>* mt_Find_Resource(const std::string& resource_id)
	{
		ResourcePair<ResourceType>* l_ret;
		ResourceContainer<ResourceType>::iterator l_it(m_resources.find(resource_id));

		if (l_it != m_resources.end())
		{
			l_ret = &(l_it->second);
		}
		else
		{
			l_ret = nullptr;
		}

		return l_ret;
	}

	ResourceType* mt_Load_Resource(const std::string& resource_id)
	{
		ResourceType* l_ret;
		PathContainer::const_iterator l_it;
		ResourcePair<ResourceType>* l_pair;

		l_it = m_paths.find(resource_id);
		if (l_it != m_paths.end())
		{
			std::unique_ptr<ResourceType> l_resource(std::make_unique<ResourceType>());

			if (mt_Load(l_resource.get(), l_it->second) == true)
			{
				m_resources.emplace(resource_id, std::make_pair(std::move(l_resource), 1));
				l_pair = mt_Find_Resource(resource_id);
				if (l_pair != nullptr)
				{
					l_ret = l_pair->first.get();
				}
				else
				{
					l_ret = nullptr;
				}
			}
			else
			{
				l_ret = nullptr;
			}
		}
		else
		{
			l_ret = nullptr;
		}

		return l_ret;
	}

	void mt_Unload_Resource(const std::string& resource_id)
	{
		ResourceContainer<ResourceType>::iterator l_it(m_resources.find(resource_id));

		if (l_it != m_resources.end())
		{
			m_resources.erase(l_it);
		}
	}

	bool mt_Load_XML_Resource(const XML_Element& resource)
	{
		bool l_b_ret;
		std::string l_id, l_path;

		l_b_ret = resource.mt_Get_Attribute("id", l_id);
		if (l_b_ret == true)
			l_b_ret = resource.mt_Get_Attribute("path", l_path);

		if (l_b_ret == true)
		{
			m_paths.emplace(l_id, m_resource_path + l_path);
		}

		return l_b_ret;
	}

	ResourceContainer<ResourceType> m_resources;
	PathContainer m_paths;
	std::string m_resource_path;
	std::string m_xml_path;

	sf::Mutex m_mutex;
};

#endif // _RESOURCE_MANAGER_HPP
