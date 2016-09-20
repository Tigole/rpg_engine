#include "BasicSkillLoader.hpp"
#include "Skill/Skill/BasicSkill.hpp"
#include "Attribute\Loader\AttributeLoader.hpp"

#include "Logger\ILogger.h"


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
	m_attributes.push_back("name");
	m_attributes.push_back("target_attribute");
	m_attributes.push_back("formula");

	m_children["AttributeList"] = &BasicSkillLoader::loadAttributes;
}

void BasicSkillLoader::setAttributeLoaderFactory(const AttributeLoaderFactory* attribute_loader_factory)
{
	m_attribute_loader_factory = attribute_loader_factory;
}

bool BasicSkillLoader::isValid(const TiXmlElement& element) const
{
	bool l_ret(false);
	std::vector<std::string> elements;

	for (auto& a : m_children)
		elements.push_back(a.first);

	l_ret = (m_attribute_loader_factory != nullptr);

	if (l_ret == true)
	{
		l_ret = checkAttributes(element, m_attributes);

		if (l_ret == true)
		{
			l_ret = checkChildren(element, elements);

			if (l_ret == true)
			{
				for (const TiXmlNode* l_node = element.FirstChild(); (l_ret == true) && (l_node != nullptr); l_node = l_node->NextSibling())
				{
					const TiXmlElement* l_element(l_node->ToElement());

					if (l_element != nullptr)
					{
						auto it(std::find(elements.begin(), elements.end(), l_element->Value()));
						if (it == elements.end())
						{
							log().entranceFunction(FUNCTION_NAME);
							log() << "Element \"" << l_element->Value() << "\" shouldn't be there\n";
							log().exitFunction();
							l_ret = false;
						}
					}
				}
			}
			else
			{
				log().entranceFunction(FUNCTION_NAME);
				log() << "Some elements are missing\n";
				log().exitFunction();
			}
		}
		else
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "Some attributes are missing\n";
			log().exitFunction();
		}
	}
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "No attribute factory for the object\n";
		log().exitFunction();
	}
	

	return l_ret;
}

std::unique_ptr<ISkill> BasicSkillLoader::loadElement(const TiXmlElement& element)
{
	std::unique_ptr<ISkill> l_ret(nullptr);
	std::string skill_name, target_attribute, formula;
	const char* attribute_value;

	skill_name = element.Attribute("name");
	target_attribute = element.Attribute("target_attribute");
	formula = element.Attribute("formula");

	l_ret = std::unique_ptr<ISkill>(new BasicSkill(skill_name, target_attribute, formula));

	if (l_ret != nullptr)
	{
		for (const TiXmlNode* l_node = element.FirstChild(); (l_ret != nullptr) && (l_node != nullptr); l_node = l_node->NextSibling())
		{
			const TiXmlElement* l_element(l_node->ToElement());
			if (l_element != nullptr)
			{
				auto it(m_children.find(l_element->Value()));
				if (it != m_children.end())
				{
					if ((this->*(it->second))(*l_element, *l_ret) == false)
					{
						log().entranceFunction(FUNCTION_NAME);
						log() << "Error while loading skill's elements\n";
						log().exitFunction();
						l_ret.reset(nullptr);
					}
				}
			}
		}
	}

	return l_ret;
}

bool BasicSkillLoader::loadAttributes(const TiXmlElement& element, ISkill& skill) const
{
	bool l_ret(true);
	AttributeLoaderFactory::LoaderCreator attribute_loader_creator;

	for (const TiXmlNode* l_node = element.FirstChild(); (l_ret == true) && (l_node != nullptr); l_node = l_node->NextSibling())
	{
		const TiXmlElement* l_element(l_node->ToElement());

		if (l_element != nullptr)
		{
			l_ret = m_attribute_loader_factory->getLoader(l_element->Value(), attribute_loader_creator);
			if (l_ret == true)
			{
				std::unique_ptr<AttributeLoader> attribute_loader(attribute_loader_creator.m_creator());

				if (attribute_loader != nullptr)
				{
					std::unique_ptr<IAttribute> skill_attribute(nullptr);

					skill_attribute = attribute_loader->load(*l_element);
					if (skill_attribute != nullptr)
					{
						l_ret = skill.addAttribute(skill_attribute);
					}
					else
					{
						log().entranceFunction(FUNCTION_NAME);
						log() << "Loading atrtibute failed\n";
						log().exitFunction();
						l_ret = false;
					}
				}
			}
			else
			{
				log().entranceFunction(FUNCTION_NAME);
				log() << "Unable to create an AttributeLoader for element \"" << l_element->Value() << "\"\n";
				log().exitFunction();
			}
		}
	}

	return l_ret;
}