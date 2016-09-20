#ifndef _COMPOSITE_ATTRIBUTE_LOADER_HPP
#define _COMPOSITE_ATTRIBUTE_LOADER_HPP 1

#include "AttributeLoader.hpp"
#include "BasicAttributeLoader.hpp"

AttributeLoader* createCompositeAttributeLoader(void);
void deleteCompositeAttributeLoader(AttributeLoader* object);

class CompositeAttributeLoader : public AttributeLoader
{
public:
	CompositeAttributeLoader();
	~CompositeAttributeLoader();

protected:
	bool isValid(const TiXmlElement& element);
	std::unique_ptr<IAttribute> loadAttribute(const TiXmlElement& element);

	BasicAttributeLoader m_basic_loader;
};

#endif // !_COMPOSITE_ATTRIBUTE_LOADER_HPP
