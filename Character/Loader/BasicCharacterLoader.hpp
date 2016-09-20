#ifndef _BASIC_CHARACTER_LOADER_HPP
#define _BASIC_CHARACTER_LOADER_HPP 1

#include "CharacterLoader.hpp"
#include "Attribute\Loader\AttributeLoaderFactory.hpp"

class BasicCharacter;

class BasicCharacterLoader : public CharacterLoader
{
public:
	BasicCharacterLoader();

	void setAttributeLoaderFactory(AttributeLoaderFactory* attribute_loader_factory);

protected:
	virtual bool isValid(const TiXmlElement& element);
	virtual std::unique_ptr<ICharacter> loadCharacter(const TiXmlElement& element, SkillManager& sm);

	bool loadSkillList(const TiXmlElement& element, std::vector<std::string>& skill_id);
	bool loadAttributList(const TiXmlElement& element, BasicCharacter& character);

	AttributeLoaderFactory* m_attribute_loader_factory;
};

#endif // !_BASIC_CHARACTER_LOADER_HPP
