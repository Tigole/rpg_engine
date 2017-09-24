#ifndef _XML_FILE_LOADER_HPP
#define _XML_FILE_LOADER_HPP 1

#include "Thread/ThreadTask.hpp"

#include <tinyxml.h>

#include <map>
#include <string>
#include <functional>
#include <stack>

class XML_Element
{
public:
	XML_Element(TiXmlElement& target);
	bool mt_Get_Attribute(const std::string& attribute_name, std::string& attribute_value) const;
	bool mt_Get_Attribute(const std::string& attribute_name, int& attribute_value) const;
	bool mt_Get_Attribute(const std::string& attribute_name, unsigned int& attribute_value) const;
	bool mt_Get_Attribute(const std::string& attribute_name, float& attribute_value) const;
	bool mt_Get_Value(std::string& element_value) const;

private:
	TiXmlElement& m_target;
};

using XML_Callback = std::function<bool(const XML_Element&)>;
using XML_CallbackContainer = std::map<std::string, XML_Callback>;
struct XML_FileHandlerData
{
	XML_FileHandlerData() : m_element_count(0), m_on_entry_callbacks(), m_on_exit_callbacks(){}
	size_t m_element_count;
	XML_CallbackContainer m_on_entry_callbacks;
	XML_CallbackContainer m_on_exit_callbacks;
};
using XML_FileHandler = std::map<std::string, XML_FileHandlerData>;

class XMLFileLoader : public ThreadTask
{
public:
	XMLFileLoader();

	void mt_Set_File(const std::string& file_path);
	template<class C>
	void mt_Add_On_Entry_Callback(const std::string xml_path, bool(C::*callback)(const XML_Element&), C* object)
	{
		if (m_current_file_it != m_files.end())
		{
			mt_Add_On_Entry_Callback(m_current_file_it->first, xml_path, callback, object);
		}
	}
	template<class C>
	void mt_Add_On_Entry_Callback(const std::string& file_path, const std::string xml_path, bool(C::*callback)(const XML_Element&), C* object)
	{
		XML_FileHandler::iterator l_file_it;

		mt_Add_File(file_path);

		l_file_it = m_files.find(file_path);
		if (l_file_it != m_files.end())
		{
			mt_Add_Callback(l_file_it->second.m_on_entry_callbacks, xml_path, callback, object);
		}
	}
	template<class C>
	void mt_Add_On_Exit_Callback(const std::string xml_path, bool(C::*callback)(const XML_Element&), C* object)
	{
		if (m_current_file_it != m_files.end())
		{
			mt_Add_On_Exit_Callback(m_current_file_it->first, xml_path, callback, object);
		}
	}
	template<class C>
	void mt_Add_On_Exit_Callback(const std::string& file_path, const std::string xml_path, bool(C::*callback)(const XML_Element&), C* object)
	{
		XML_FileHandler::iterator l_file_it;

		mt_Add_File(file_path);

		l_file_it = m_files.find(file_path);
		if (l_file_it != m_files.end())
		{
			mt_Add_Callback(l_file_it->second.m_on_exit_callbacks, xml_path, callback, object);
		}
	}

protected:
	template<class C>
	void mt_Add_Callback(XML_CallbackContainer& callback_container, const std::string& xml_path, bool(C::*callback)(const XML_Element&), C* object)
	{
		callback_container.emplace(xml_path, std::bind(callback, object, std::placeholders::_1));
	}
	void mt_Add_File(const std::string& file_path);
	struct LoadingStructure
	{
		LoadingStructure():m_error(), m_element_count(0){}
		std::string m_error;
		size_t m_element_count;
	};
	void mt_Work(void);
	bool mt_Explore_Document(TiXmlElement& root, LoadingStructure& loading_struct, XML_CallbackContainer& on_entry_callbacks, XML_CallbackContainer& on_exit_callbacks);
	bool mt_Get_Next_Element(TiXmlElement*& current_element, std::stack<TiXmlElement*>& elements_stack, std::string& current_element_path, XML_CallbackContainer& on_exit_callbacks);
	bool mt_Manage_Callback(const std::string& element_path, XML_CallbackContainer& callback_container, TiXmlElement* current_element);
	XML_FileHandler m_files;
	XML_FileHandler::iterator m_current_file_it;
	LoadingStructure m_loading_struct;
};

#endif // _XML_FILE_LOADER_HPP
