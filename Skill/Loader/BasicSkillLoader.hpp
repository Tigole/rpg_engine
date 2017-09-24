#ifndef _BASIC_SKILL_LOADER_HPP
#define _BASIC_SKILL_LOADER_HPP 1

#include "SkillLoader.hpp"
#include "Attribute/Loader/AttributeLoaderFactory.hpp"

SkillLoader* createBasicSkillLoader(void);
void deleteBasicSkillLoader(SkillLoader* basic_skill_loader);

class BasicSkillLoader : public SkillLoader
{
public:
	BasicSkillLoader();

	void mt_Set_AttributeLoaderFactory(const AttributeLoaderFactory* attribute_loader_factory);
	std::unique_ptr<ISkill> mt_Load(const TiXmlElement& element);

protected:
	void mt_Load_Attributes(const TiXmlElement& element, ISkill& skill) const;

	const AttributeLoaderFactory* m_attribute_loader_factory;
	std::vector<std::string> m_attributes;
	std::map<std::string, void(BasicSkillLoader::*)(const TiXmlElement&, ISkill& skill)const> m_children;
};

#endif // !_BASIC_SKILL_LOADER_HPP
