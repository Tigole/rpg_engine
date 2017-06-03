#ifndef _XML_FILE_LOADER_HPP
#define _XML_FILE_LOADER_HPP 1

#include "Thread/ThreadTask.hpp"

#include <tinyxml.h>

#include <map>
#include <string>
#include <functional>
#include <stack>

using XML_Callback = std::function<bool(const TiXmlElement&)>;
using XML_CallbackContainer = std::map<std::string, XML_Callback>;
using XML_FileHandler = std::map<std::string, std::pair<size_t, XML_CallbackContainer>>;

class XMLFileLoader : public ThreadTask
{
public:
	XMLFileLoader();

	void setFile(const std::string& file_path);
	template<class C>
	void addCallback(const std::string xml_path, bool(C::*callback)(const TiXmlElement&), C* object)
	{
		if (m_current_file_it != m_files.end())
		{
			addCallback(m_current_file_it->first, xml_path, callback, object);
		}
	}
	template<class C>
	void addCallback(const std::string& file_path, const std::string xml_path, bool(C::*callback)(const TiXmlElement&), C* object)
	{
		XML_FileHandler::iterator l_file_it;

		l_file_it = m_files.find(file_path);
		if (l_file_it != m_files.end())
		{
			l_file_it->second.second.emplace(xml_path, std::bind(callback, object, std::placeholders::_1));
		}
	}

protected:
	struct LoadingStructure
	{
		LoadingStructure():m_error(), m_element_count(0){}
		std::string m_error;
		size_t m_element_count;
	};
	void work(void);
	bool exploreDocument(TiXmlElement& root, LoadingStructure& loading_struct, XML_CallbackContainer& callbacks);
	TiXmlElement* getNextElement(TiXmlElement* current_element, std::stack<TiXmlElement*>& elements_stack, std::string& current_element_path);

	XML_FileHandler m_files;
	XML_FileHandler::iterator m_current_file_it;
	LoadingStructure m_loading_struct;
};

#endif // _XML_FILE_LOADER_HPP
