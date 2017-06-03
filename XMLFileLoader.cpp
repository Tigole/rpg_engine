#include "XMLFileLoader.hpp"

XMLFileLoader::XMLFileLoader()
 :	m_files(),
	m_current_file_it(m_files.end()),
	m_loading_struct()
{}

void XMLFileLoader::setFile(const std::string& file_path)
{
	LoadingStructure l_loading_struct;
	TiXmlDocument l_document;
	TiXmlElement* l_root;
	XML_CallbackContainer l_callback_container;

	if (l_document.LoadFile(file_path) == true)
	{
		l_root = l_document.RootElement();
		if (l_root != nullptr)
		{
			m_current_file_it = m_files.find(file_path);
			if (m_current_file_it == m_files.end())
			{
				if (exploreDocument(*l_root, l_loading_struct, l_callback_container) == true)
				{
					m_current_file_it = m_files.emplace(file_path, std::make_pair(l_loading_struct.m_element_count, l_callback_container)).first;
				}
			}
		}
	}
}

void XMLFileLoader::work(void)
{
	TiXmlDocument l_document;

	if (m_current_file_it != m_files.end())
	{
		if (l_document.LoadFile(m_current_file_it->first))
		{
			exploreDocument(*l_document.RootElement(), m_loading_struct, m_current_file_it->second.second);
		}
	}

	done();
}

bool XMLFileLoader::exploreDocument(TiXmlElement& root, LoadingStructure& loading_struct, XML_CallbackContainer& callbacks)
{
	bool l_ret(true);
	XML_CallbackContainer::iterator l_callback_it(callbacks.end());
	TiXmlElement* l_current_element(nullptr);
	std::stack<TiXmlElement*> l_elements_stack;
	std::string l_element_path("/");

	l_current_element = &root;
	l_element_path += l_current_element->ValueStr();

	loading_struct.m_element_count = 0;

	while((l_current_element != nullptr) && (l_ret == true))
	{
		loading_struct.m_element_count++;

		l_callback_it = callbacks.find(l_element_path);
		if (l_callback_it != callbacks.end())
		{
			l_ret = (l_callback_it->second)(*l_current_element);
		}

		if (l_ret == false)
		{
			loading_struct.m_error = "Error while loading element in \"" + l_element_path + "\"";
		}

		l_current_element = getNextElement(l_current_element, l_elements_stack, l_element_path);
	}

	return l_ret;
}

TiXmlElement* XMLFileLoader::getNextElement(TiXmlElement* current_element, std::stack<TiXmlElement*>& elements_stack, std::string& current_element_path)
{
	TiXmlElement* l_previous_element(current_element);

	if (current_element != nullptr)
	{
		current_element = current_element->FirstChildElement();

		if (current_element != nullptr)
		{
			current_element_path += "/" + current_element->ValueStr();
			elements_stack.push(l_previous_element);
		}

		while((current_element == nullptr) && (elements_stack.size() != 0))
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
	return current_element;
}

