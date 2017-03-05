#ifndef _SKILL_LOADER_FACTORY_HPP
#define _SKILL_LOADER_FACTORY_HPP 1

#include "Loader/LoaderFactory.hpp"

class SkillLoader;
class AttributeLoaderFactory;

class SkillLoaderFactory : public LoaderFactory<SkillLoader>
{
public:
	SkillLoaderFactory(AttributeLoaderFactory& attribute_factory);

protected:
	//AttributeLoaderFactory& m_attribute_factory;
};


#endif // !_SKILL_LOADER_FACTORY_HPP
