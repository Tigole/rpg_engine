#ifndef _LOADER_HPP
#define _LOADER_HPP 1

#include <vector>
#include <string>

class TiXmlElement;

class ILoader
{
public:
	ILoader();
	virtual ~ILoader();
protected:
	bool checkAttributes(const TiXmlElement& element, const std::vector<std::string>& attributes) const;
	bool checkChildren(const TiXmlElement& element, const std::vector<std::string>& children) const;

	/** \fn bool checkAttributes(const TiXmlElement& element, const std::vector<std::string>& attributes) const
		\brief Check if the element has at least one attribute named in "attributes"
		\return true on success
		\example
		XML element: <element attr1="jfdkl" attr2="kd"/>
		std::vector<std::string> attributes(2);
		attributes[0] = "attr1";
		attributes[1] = "attr2";
		checkAttributes(element, attributes) will return true
	**/
	/**
		\fn bool checkChildren(const TiXmlElement& element, const std::vector<std::string>& children) const
		\brief Check if the element has at least one attribute named in "attributes"
		\return true on success
	**/
};

class Loader : public ILoader
{
public:
	Loader(const std::string& element_name);
	virtual ~Loader();

	const std::string& getElementName(void) const;
protected:
	std::string m_element_name;

	/** \fn const std::string& getElementName(void) const
		\brief Get the name of element for a XML file
	**/
};

#endif // _LOADER_HPP
