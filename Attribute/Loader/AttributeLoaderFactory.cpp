#include "AttributeLoaderFactory.hpp"
#include "BasicAttributeLoader.hpp"
#include "CompositeAttributeLoader.hpp"

AttributeLoaderFactory::AttributeLoaderFactory() : LoaderFactory<AttributeLoader>()
{
	BasicAttributeLoader basic_attribute_loader;
	CompositeAttributeLoader composite_attribute_loader;

	m_creators[basic_attribute_loader.mt_Get_Element_Name()] = LoaderCreator<AttributeLoader>(&createBasicAttributeLoader, &deleteBasicAttributeLoader);
	m_creators[composite_attribute_loader.mt_Get_Element_Name()] = LoaderCreator<AttributeLoader>(&createCompositeAttributeLoader, deleteCompositeAttributeLoader);
}
