#ifndef _BASIC_ATTRIBUTE_LOADER_HPP
#define _BASIC_ATTRIBUTE_LOADER_HPP 1

#include "AttributeLoader.hpp"

class IAttribute;

AttributeLoader* createBasicAttributeLoader(void);
void deleteBasicAttributeLoader(AttributeLoader*);

class BasicAttributeLoader : public AttributeLoader
{
public:
	BasicAttributeLoader();
	~BasicAttributeLoader();

	friend class CompositeAttributeLoader;

protected:
	bool isValid(const TiXmlElement& element);
	std::unique_ptr<IAttribute> loadAttribute(const TiXmlElement& element);
};

#endif // !_BASIC_ATTRIBUTE_LOADER_HPP