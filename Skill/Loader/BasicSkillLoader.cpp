#include "BasicSkillLoader.hpp"
#include "Skill/Skill/BasicSkill.hpp"
#include "Attribute/Loader/AttributeLoader.hpp"
#include "Exception/Exception.hpp"

#include "Logger/ILogger.h"


SkillLoader* createBasicSkillLoader()
{
	return new BasicSkillLoader();
}

void deleteBasicSkillLoader(SkillLoader* basic_skill_loader)
{
	delete basic_skill_loader;
}

BasicSkillLoader::BasicSkillLoader()
	:SkillLoader("BasicSkill"),
	m_attribute_loader_factory(nullptr),
	m_attributes(),
	m_children()
{
	m_attributes.push_back("id");
	m_attributes.push_back("target_attribute");
	m_attributes.push_back("formula");

	m_children["AttributeList"] = &BasicSkillLoader::loadAttributes;
}

void BasicSkillLoader::setAttributeLoaderFactory(const AttributeLoaderFactory* attribute_loader_factory)
{
	m_attribute_loader_factory = attribute_loader_factory;
}

std::unique_ptr<ISkill> BasicSkillLoader::load(const TiXmlElement& element)
{
	std::unique_ptr<ISkill> l_ret(nullptr);
	std::string skill_id;
	const char* attribute_value;

	if (element.QueryStringAttribute("id", &skill_id) != TIXML_SUCCESS)
		throw ExceptionXMLLoadingAttributeMissing(element, "id");

	l_ret = std::unique_ptr<ISkill>(new BasicSkill(skill_id));

	if (l_ret != nullptr)
	{
		for (const TiXmlNode* l_node = element.FirstChild(); (l_ret != nullptr) && (l_node != nullptr); l_node = l_node->NextSibling())
		{
			const TiXmlElement* l_element(l_node->ToElement());
			if (l_element != nullptr)
			{
				auto it(m_children.find(l_element->Value()));

				if (it == m_children.end())
					throw ExceptionXMLLoadingNoLoader(l_element->Value());

				(this->*(it->second))(*l_element, *l_ret);
			}
		}
	}

	return l_ret;
}

void BasicSkillLoader::loadAttributes(const TiXmlElement& element, ISkill& skill) const
{
	LoaderCreator<AttributeLoader> attribute_loader_creator;

	for (const TiXmlNode* l_node = element.FirstChild(); l_node != nullptr; l_node = l_node->NextSibling())
	{
		const TiXmlElement* l_element(l_node->ToElement());

		if (l_element != nullptr)
		{
			attribute_loader_creator = m_attribute_loader_factory->getLoader(l_element->Value());
			std::unique_ptr<AttributeLoader> attribute_loader(attribute_loader_creator.m_creator());
			std::unique_ptr<IAttribute> iattribute(attribute_loader->load(*l_element));

			skill.addAttribute(iattribute);
		}
	}
}
