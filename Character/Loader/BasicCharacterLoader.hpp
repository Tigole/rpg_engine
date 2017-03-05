#ifndef _BASIC_CHARACTER_LOADER_HPP
#define _BASIC_CHARACTER_LOADER_HPP 1

#include "CharacterLoader.hpp"
#include "Attribute/Loader/AttributeLoaderFactory.hpp"

class BasicCharacter;

class BasicCharacterLoader : public CharacterLoader
{
public:
	BasicCharacterLoader();

	void setAttributeLoaderFactory(AttributeLoaderFactory* attribute_loader_factory);
	virtual std::unique_ptr<ICharacter> load(const TiXmlElement& element, SkillManager& sm);

protected:

	void loadSkillList(const TiXmlElement& element, std::vector<std::string>& skill_id);
	void loadAttributList(const TiXmlElement& element, BasicCharacter& character);

	AttributeLoaderFactory* m_attribute_loader_factory;
};

#endif // !_BASIC_CHARACTER_LOADER_HPP
