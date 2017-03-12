#ifndef _LOADER_FACTORY_HPP
#define _LOADER_FACTORY_HPP 1

#include "Miscellaneous.hpp"
#include "Loader/Loader.hpp"
#include "Exception/Exception.hpp"

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
	LoaderFactory() : m_creators(){ /** Nothing **/ }
	virtual ~LoaderFactory(){ /** Nothing **/ }
	LoaderCreator<LoadedType> getLoader(const std::string& element_name) const
	{
		bool l_ret(false);
		auto it(m_creators.find(element_name));

		if (it == m_creators.end())
			throw ExceptionXMLLoadingNoLoader(element_name);

		return it->second;
	}

	void load(const TiXmlElement& element, misc::DLL_Loader<LoadedType>& dll_loader)
	{
		std::vector<std::pair<std::string, std::string*>> attributes;
		std::string element_name, library_name, creator_name, deleter_name;
		typename LoaderCreator<LoadedType>::TypeConstuctor creator;
		typename LoaderCreator<LoadedType>::TypeDestructor deleter;

		attributes.push_back(std::make_pair("element_name", &element_name));
		attributes.push_back(std::make_pair("library_name", &library_name));
		attributes.push_back(std::make_pair("creator_name", &creator_name));
		attributes.push_back(std::make_pair("deleter_name", &deleter_name));

		for (auto& a : attributes)
		{
			if (element.QueryStringAttribute(a.first.c_str(), a.second) != TIXML_SUCCESS)
				throw XMLLoadingExceptionAttributeMissing(element, a.first);
		}

		creator = dll_loader.getFunction(library_name, creator_name);
		if (creator == nullptr)
			throw DLLFunctionNotFound(library_name, creator_name);

		deleter = dll_loader.getFunction(library_name, deleter_name);
		if (deleter == nullptr)
			throw DLLFunctionNotFound(library_name, deleter_name);

		if (m_creators.find(element_name) == m_creators.end())
			m_creators[element_name] = LoaderCreator<LoadedType>(creator, deleter);
		else
			throw ResourceAlradeyExists(element_name, FUNCTION_NAME);
	}
protected:
	std::map<std::string, LoaderCreator<LoadedType>> m_creators;
};

#endif // !_LOADER_FACTORY_HPP
