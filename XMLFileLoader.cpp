#include "XMLFileLoader.hpp"

XML_Element::XML_Element(TiXmlElement& target)
 :	m_target(target)
{}

bool XML_Element::mt_Get_Attribute(const std::string& attribute_name, std::string& attribute_value) const
{
	return m_target.QueryStringAttribute(attribute_name.c_str(), &attribute_value) == TIXML_SUCCESS;
}

bool XML_Element::mt_Get_Attribute(const std::string& attribute_name, int& attribute_value) const
{
	return m_target.QueryIntAttribute(attribute_name.c_str(), &attribute_value) == TIXML_SUCCESS;
}

bool XML_Element::mt_Get_Attribute(const std::string& attribute_name, unsigned int& attribute_value) const
{
	return m_target.QueryUnsignedAttribute(attribute_name.c_str(), &attribute_value) == TIXML_SUCCESS;
}

bool XML_Element::mt_Get_Attribute(const std::string& attribute_name, float& attribute_value) const
{
	return m_target.QueryFloatAttribute(attribute_name.c_str(), &attribute_value) == TIXML_SUCCESS;
}

bool XML_Element::mt_Get_Value(std::string& element_value) const
{
	element_value = m_target.ValueStr();
	return true;
}

XMLFileLoader::XMLFileLoader()
 :	m_files(),
	m_current_file_it(m_files.end()),
	m_loading_struct()
{}

void XMLFileLoader::mt_Set_File(const std::string& file_path)
{
	LoadingStructure l_loading_struct;
	TiXmlDocument l_document;
	TiXmlElement* l_root;
	XML_FileHandlerData l_xml_file_handler_data;

	if (l_document.LoadFile(file_path) == true)
	{
		l_root = l_document.RootElement();
		if (l_root != nullptr)
		{
			m_current_file_it = m_files.find(file_path);
			if (m_current_file_it == m_files.end())
			{
				if (mt_Explore_Document(*l_root, l_loading_struct, l_xml_file_handler_data.m_on_entry_callbacks, l_xml_file_handler_data.m_on_exit_callbacks) == true)
				{
					l_xml_file_handler_data.m_element_count = l_loading_struct.m_element_count;
					m_current_file_it = m_files.emplace(file_path, l_xml_file_handler_data).first;
				}
			}
		}
	}
}

void XMLFileLoader::mt_Add_File(const std::string& file_path)
{
	XML_FileHandler::iterator l_file_it;

	l_file_it = m_files.find(file_path);

	if (l_file_it == m_files.end())
	{
		l_file_it = m_current_file_it;
		mt_Set_File(file_path);
		m_current_file_it = l_file_it;
	}
}

void XMLFileLoader::mt_Work(void)
{
	TiXmlDocument l_document;

	if (m_current_file_it != m_files.end())
	{
		if (l_document.LoadFile(m_current_file_it->first))
		{
			mt_Explore_Document(*l_document.RootElement(), m_loading_struct, m_current_file_it->second.m_on_entry_callbacks, m_current_file_it->second.m_on_exit_callbacks);
		}
	}

	mt_Done();
}

bool XMLFileLoader::mt_Explore_Document(TiXmlElement& root, LoadingStructure& loading_struct, XML_CallbackContainer& on_entry_callbacks, XML_CallbackContainer& on_exit_callbacks)
{
	bool l_ret(true);
	TiXmlElement* l_current_element(nullptr);
	std::stack<TiXmlElement*> l_elements_stack;
	std::string l_element_path("/");

	l_current_element = &root;
	l_element_path += l_current_element->ValueStr();

	loading_struct.m_element_count = 0;

	while((l_current_element != nullptr) && (l_ret == true))
	{
		loading_struct.m_element_count++;

		l_ret = mt_Manage_Callback(l_element_path, on_entry_callbacks, l_current_element);

		if (l_ret == false)
		{
			loading_struct.m_error = "Error while loading (on entry) element in \"" + l_element_path + "\"";
		}

		if (l_ret == true)
		{
			l_ret = mt_Get_Next_Element(l_current_element, l_elements_stack, l_element_path, on_exit_callbacks);

			if (l_ret == false)
			{
				loading_struct.m_error = "Error while loading (on exit) element in \"" + l_element_path + "\"";
			}
		}
	}

	return l_ret;
}

bool XMLFileLoader::mt_Get_Next_Element(TiXmlElement*& current_element, std::stack<TiXmlElement*>& elements_stack, std::string& current_element_path, XML_CallbackContainer& on_exit_callbacks)
{
	bool l_b_ret;
	TiXmlElement* l_previous_element(current_element);

	if (current_element != nullptr)
	{
		current_element = current_element->FirstChildElement();

		if (current_element != nullptr)
		{
			current_element_path += "/" + current_element->ValueStr();
			elements_stack.push(l_previous_element);
		}

		l_b_ret = true;

		/** Going backward **/
		while((current_element == nullptr) && (elements_stack.size() != 0) && (l_b_ret == true))
		{
			l_b_ret = mt_Manage_Callback(current_element_path, on_exit_callbacks, current_element);
			if (l_b_ret == true)
			{
				current_element = l_previous_element->NextSiblingElement();
				current_element_path.erase(current_element_path.rfind('/'));
				if (current_element != nullptr)
				{
					current_element_path += "/" + current_element->ValueStr();
				}
				else
				{
					l_previous_element = elements_stack.top();
					elements_stack.pop();
				}
			}
		}
	}
	else
	{
		l_b_ret = false;
	}

	return l_b_ret;
}

bool XMLFileLoader::mt_Manage_Callback(const std::string& element_path, XML_CallbackContainer& callback_container, TiXmlElement* current_element)
{
	bool l_ret;
	XML_CallbackContainer::iterator l_callback_it;

	l_callback_it = callback_container.find(element_path);
	if (l_callback_it != callback_container.end())
	{
		l_ret = (l_callback_it->second)(XML_Element(*current_element));
	}
	else
	{
		l_ret = true;
	}

	return l_ret;
}
