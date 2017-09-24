#ifndef _ATTRIBUTE_LIST_LOADER_HPP
#define _ATTRIBUTE_LIST_LOADER_HPP 1

#include "Loader/Loader.hpp"
#include "Attribute/IAttribute.hpp"
#include "Attribute/Loader/AttributeLoaderFactory.hpp"

#include <vector>

class AttributeListLoader : public Loader
{
public:
	AttributeListLoader(const AttributeLoaderFactory& attribute_loader_factory);

	void mt_Load(const TiXmlElement& element, std::vector<std::unique_ptr<IAttribute>>& attributes);

private:
	const AttributeLoaderFactory& m_attribute_loader_factory;
	std::pair<const TiXmlElement*, std::vector<std::unique_ptr<IAttribute>>> m_attributes;
};

#endif // !_ATTRIBUTE_LIST_LOADER_HPP
