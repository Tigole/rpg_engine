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

	std::unique_ptr<IAttribute> load(const TiXmlElement& element);
protected:
	BasicAttributeLoader m_basic_loader;
};

#endif // !_COMPOSITE_ATTRIBUTE_LOADER_HPP
