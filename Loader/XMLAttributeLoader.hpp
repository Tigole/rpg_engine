#ifndef _XML_ATTRIBUTE_LOADER_HPP
#define _XML_ATTRIBUTE_LOADER_HPP 1

#include <string>
#include <vector>
#include <memory>

#include "XMLFileLoader.hpp"

class IXMLAttributeLoader;

class XMLAttributeLoaderList
{
public:
	XMLAttributeLoaderList();
	XMLAttributeLoaderList(IXMLAttributeLoader* loader);
	XMLAttributeLoaderList(IXMLAttributeLoader* loader1, IXMLAttributeLoader* loader2);
	XMLAttributeLoaderList(IXMLAttributeLoader* loader1, IXMLAttributeLoader* loader2, IXMLAttributeLoader* loader3);
	XMLAttributeLoaderList(std::vector<IXMLAttributeLoader*> loaders);

	void mt_Add(IXMLAttributeLoader* loader);
	bool mt_Load(const XML_Element& element);

private:
	std::vector<std::unique_ptr<IXMLAttributeLoader>> m_loaders;
};

class IXMLAttributeLoader
{
public:
	IXMLAttributeLoader(const std::string& attribute_name);
	virtual ~IXMLAttributeLoader();

	virtual bool mt_Load(const XML_Element& element) = 0;

protected:
	std::string m_attribute_name;
};

template <typename T>
class XMLAttributeLoader : public IXMLAttributeLoader
{
public:
	XMLAttributeLoader(const std::string& attribute_name, T& data)
		:IXMLAttributeLoader(attribute_name),
		m_data(&data) {}
	virtual ~XMLAttributeLoader() {}

	virtual bool mt_Load(const XML_Element& element)
	{
		return element.mt_Get_Attribute(m_attribute_name, *m_data);
	}

protected:
	T* m_data;
};
#if 0
class XMLAttributeLoader_Int : public XMLAttributeLoader<int>
{
public:
	XMLAttributeLoader_Int(const std::string& attribute_name, int& data);
	virtual bool mt_Load(const XML_Element& element);
};

class XMLAttributeLoader_UnsignedInt : public XMLAttributeLoader<unsigned int>
{
public:
	XMLAttributeLoader_UnsignedInt(const std::string& attribute_name, unsigned int& data);
	virtual bool mt_Load(const XML_Element& element);
};

class XMLAttributeLoader_String : public XMLAttributeLoader<std::string>
{
public:
	XMLAttributeLoader_String(const std::string& attribute_name, std::string& data);
	virtual bool mt_Load(const XML_Element& element);
};

class XMLAttributeLoader_Float : public XMLAttributeLoader<float>
{
public:
	XMLAttributeLoader_Float(const std::string& attribute_name, float& data);
	virtual bool mt_Load(const XML_Element& element);
};

class XMLAttributeLoader_Bool : public XMLAttributeLoader<bool>
{
public:
	XMLAttributeLoader_Bool(const std::string& attribute_name, bool& data);
	virtual bool mt_Load(const XML_Element& element);
};
#endif // 0
#endif // !_XML_ATTRIBUTE_LOADER_HPP
