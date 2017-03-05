#include "SkillLoaderFactory.hpp"
#include "BasicSkillLoader.hpp"

SkillLoaderFactory::SkillLoaderFactory(AttributeLoaderFactory& attribute_factory)
	:LoaderFactory<SkillLoader>()
{
	BasicSkillLoader basic_loader;

	basic_loader.setAttributeLoaderFactory(&attribute_factory);

	m_creators[basic_loader.getElementName()] = LoaderCreator<SkillLoader>(&createBasicSkillLoader, &deleteBasicSkillLoader);
}
