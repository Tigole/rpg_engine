#ifndef _ATTRIBUTE_LOADER_HPP
#define _ATTRIBUTE_LOADER_HPP 1

#include "Loader/Loader.hpp"
#include "Miscellaneous.hpp"

class IAttribute;

class AttributeLoader : public Loader
{
public:
	AttributeLoader(const std::string& element_name);
	virtual ~AttributeLoader();

	virtual std::unique_ptr<IAttribute> mt_Load(const TiXmlElement& element) = 0;

	/** \fn IAttribute* load(const TiXmlElement& element)
		\brief Create an object of type IAttribute from the element
		\return nullptr on fail
		\details if element is valid, try to create the attribute
	**/
};

#endif // !_ATTRIBUTE_LOADER_HPP
