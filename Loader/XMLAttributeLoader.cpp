#include "XMLAttributeLoader.hpp"
#include "XMLFileLoader.hpp"

XMLAttributeLoaderList::XMLAttributeLoaderList()
 :	m_loaders()
{}

XMLAttributeLoaderList::XMLAttributeLoaderList(IXMLAttributeLoader* loader)
 :	m_loaders()
{
	mt_Add(loader);
}

XMLAttributeLoaderList::XMLAttributeLoaderList(IXMLAttributeLoader* loader1, IXMLAttributeLoader* loader2)
 :	m_loaders()
{
	mt_Add(loader1);
	mt_Add(loader2);
}

XMLAttributeLoaderList::XMLAttributeLoaderList(IXMLAttributeLoader* loader1, IXMLAttributeLoader* loader2, IXMLAttributeLoader* loader3)
 :	m_loaders()
{
	mt_Add(loader1);
	mt_Add(loader2);
	mt_Add(loader3);
}

XMLAttributeLoaderList::XMLAttributeLoaderList(std::vector<IXMLAttributeLoader*> loaders)
 :	m_loaders()
{
	for (auto& a : loaders)
		mt_Add(a);
}

void XMLAttributeLoaderList::mt_Add(IXMLAttributeLoader* loader)
{
	if (loader != nullptr)
		m_loaders.push_back(std::unique_ptr<IXMLAttributeLoader>(loader));
}

bool XMLAttributeLoaderList::mt_Load(const XML_Element& element)
{
	bool l_b_ret(true);

	for (auto l_it = m_loaders.begin(); (l_it != m_loaders.end()) && (l_b_ret == true); l_it++)
		l_b_ret = l_it->get()->mt_Load(element);

	return l_b_ret;
}


IXMLAttributeLoader::IXMLAttributeLoader(const std::string& attribute_name)
	:m_attribute_name(attribute_name)
{}

IXMLAttributeLoader::~IXMLAttributeLoader()
{}
#if 0
XMLAttributeLoader_Int::XMLAttributeLoader_Int(const std::string& attribute_name, int& data)
	:XMLAttributeLoader<int>(attribute_name, data)
{}

bool XMLAttributeLoader_Int::mt_Load(const XML_Element& element)
{
	return element.mt_Get_Attribute(m_attribute_name, *m_data);
}

XMLAttributeLoader_UnsignedInt::XMLAttributeLoader_UnsignedInt(const std::string& attribute_name, unsigned int& data)
	:XMLAttributeLoader<unsigned int>(attribute_name, data)
{}

bool XMLAttributeLoader_UnsignedInt::mt_Load(const XML_Element& element)
{
	return element.mt_Get_Attribute(m_attribute_name, *m_data);
}

XMLAttributeLoader_String::XMLAttributeLoader_String(const std::string& attribute_name, std::string& data)
	:XMLAttributeLoader<std::string>(attribute_name, data)
{}

bool XMLAttributeLoader_String::mt_Load(const XML_Element& element)
{
	return (element.QueryStringAttribute(m_attribute_name.c_str(), m_data) == TIXML_SUCCESS);
}

XMLAttributeLoader_Float::XMLAttributeLoader_Float(const std::string& attribute_name, float& data)
	:XMLAttributeLoader<float>(attribute_name, data)
{}

bool XMLAttributeLoader_Float::mt_Load(const XML_Element& element)
{
	return (element.QueryFloatAttribute(m_attribute_name.c_str(), m_data) == TIXML_SUCCESS);
}

XMLAttributeLoader_Bool::XMLAttributeLoader_Bool(const std::string& attribute_name, bool& data)
	:XMLAttributeLoader<bool>(attribute_name, data)
{}

bool XMLAttributeLoader_Bool::mt_Load(const XML_Element& element)
{
	return (element.QueryBoolAttribute(m_attribute_name.c_str(), m_data) == TIXML_SUCCESS);
}
#endif
