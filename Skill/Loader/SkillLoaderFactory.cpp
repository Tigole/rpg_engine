#include "SkillLoaderFactory.hpp"
#include "BasicSkillLoader.hpp"

SkillLoaderFactory::SkillLoaderFactory(AttributeLoaderFactory& attribute_factory)
	:LoaderFactory<SkillLoader>()
{
	BasicSkillLoader basic_loader;

	basic_loader.mt_Set_AttributeLoaderFactory(&attribute_factory);

	m_creators[basic_loader.mt_Get_Element_Name()] = LoaderCreator<SkillLoader>(&createBasicSkillLoader, &deleteBasicSkillLoader);
}
