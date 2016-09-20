#ifndef _LOADER_FACTORY_HPP
#define _LOADER_FACTORY_HPP 1

#include "Miscellaneous.hpp"
#include "Loader\Loader.hpp"

#include <string>
#include <map>

class TiXmlElement;

template<typename LoadedType>
struct LoaderCreator
{
	typedef LoadedType*(*TypeConstuctor)(void);
	typedef void(*TypeDestructor)(LoadedType*);
	LoaderCreator() : m_creator(nullptr), m_deleter(nullptr) {}
	LoaderCreator(TypeConstuctor creator, TypeDestructor deleter) : m_creator(creator), m_deleter(deleter) {}
	LoaderCreator(const LoaderCreator& cp) : m_creator(cp.m_creator), m_deleter(cp.m_deleter) {}
	LoaderCreator& operator=(const LoaderCreator& cp) { m_creator = cp.m_creator; m_deleter = cp.m_deleter; return *this; }

	TypeConstuctor m_creator;
	TypeDestructor m_deleter;
};

template<typename LoadedType>
class LoaderFactory : public ILoader
{
public:
	typedef LoaderCreator<LoadedType> LoaderCreator;
	LoaderFactory() : m_creators(){ /** Nothing **/ }
	virtual ~LoaderFactory(){ /** Nothing **/ }
	bool getLoader(const std::string& element_name, LoaderCreator& creator) const
	{
		bool l_ret(false);
		auto it(m_creators.find(element_name));

		l_ret = it != m_creators.end();
		if (l_ret)
		{
			creator = it->second;
		}

		return l_ret;
	}
	bool load(const TiXmlElement& element, misc::DLL_Loader& dll_loader)
	{
		bool l_ret(false);
		std::vector<std::string> attributes;

		attributes.push_back("element_name");
		attributes.push_back("library_name");
		attributes.push_back("creator_name");
		attributes.push_back("deleter_name");

		l_ret = checkChildren(element, std::vector<std::string>(1, "Creator"));

		if (l_ret == true)
		{
			l_ret = checkAttributes(element, attributes);
			if (l_ret == true)
			{
				l_ret = loadCreator(element, dll_loader);
			}
			else
			{
				log().entranceFunction(FUNCTION_NAME);
				log() << "Some attributes are missing\n";
				log().exitFunction();
			}
		}
		else
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "Some children are missing\n";
			log().exitFunction();
		}


		return l_ret;
	}
protected:
	std::map<std::string, LoaderCreator> m_creators;
private:
	bool loadCreator(const TiXmlElement& element, misc::DLL_Loader& dll_loader)
	{
		bool l_ret(false);
		int query_return(TIXML_SUCCESS);
		std::vector<std::pair<std::string, std::string*>> attributes;
		std::string element_name, library_name, creator_name, deleter_name;
		LoaderCreator::TypeConstuctor creator;
		LoaderCreator::TypeDestructor deleter;

		attributes.push_back(std::make_pair("element_name", &element_name));
		attributes.push_back(std::make_pair("library_name", &library_name));
		attributes.push_back(std::make_pair("creator_name", &creator_name));
		attributes.push_back(std::make_pair("deleter_name", &deleter_name));

		for (auto& a : attributes)
			if (query_return == TIXML_SUCCESS)
				query_return = element.QueryStringAttribute(a.first.c_str(), a.second);

		if (query_return == TIXML_SUCCESS)
		{
			creator = dll_loader.getFunction(library_name, creator_name);
			deleter = dll_loader.getFunction(library_name, deleter_name);

			if ((creator != nullptr) && (deleter != nullptr))
			{
				if (m_creators.find(element_name) == m_creators.end())
					m_creators[element_name] = LoaderCreator(creator, deleter);
				else
				{
					log().entranceFunction(FUNCTION_NAME);
					log() << "Element name \"" << element_name << "\" already exists\n";
					log().exitFunction();
				}
			}
			else
			{
				l_ret = false;
				log().entranceFunction(FUNCTION_NAME);
				log() << "Can't get creator \"" << creator_name << "\" or deleter \"" << deleter_name << "\" from library \"" << library_name << "\"\n";
				log().exitFunction();
			}
		}
		else
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "Error while getting attributes from element\n";
			log().startBlock("Attributes");
			for (auto& a : attributes)
				log() << "Attribute name : \"" << a.first << "\"\tAttribute value : \"" << a.second << "\"\n";
			log().endBlock();
			log().exitFunction();
		}

		return l_ret;
	}
};

#endif // !_LOADER_FACTORY_HPP
