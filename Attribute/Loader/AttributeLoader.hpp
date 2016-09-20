#ifndef _ATTRIBUTE_LOADER_HPP
#define _ATTRIBUTE_LOADER_HPP 1

#include "Loader\Loader.hpp"
#include "Miscellaneous.hpp"

class IAttribute;

class AttributeLoader : public Loader
{
public:
	AttributeLoader(const std::string& element_name);
	virtual ~AttributeLoader();

	std::unique_ptr<IAttribute> load(const TiXmlElement& element);
	virtual bool isValid(const TiXmlElement& element) = 0;

protected:
	virtual std::unique_ptr<IAttribute> loadAttribute(const TiXmlElement& element) = 0;

	/** \fn IAttribute* load(const TiXmlElement& element)
		\brief Create an object of type IAttribute from the element
		\return nullptr on fail
		\details if element is valid, try to create the attribute
	**/
	/** \fn bool isValid(const TiXmlElement& element)
		\brief Checks if the element is valid
		\return true on success
	**/
	/** \fn IAttribute* loadAttribute(const TiXmlElement& element)
		\brief Parse the element in the aim to create the attribute
		\return nullptr on fail
	**/
};

#endif // !_ATTRIBUTE_LOADER_HPP
