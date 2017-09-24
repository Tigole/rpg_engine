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
	std::unique_ptr<IAttribute> mt_Load(const TiXmlElement& element);
};

#endif // !_BASIC_ATTRIBUTE_LOADER_HPP
