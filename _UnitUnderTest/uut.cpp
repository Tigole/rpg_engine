#include "uut.hpp"

#include "Character/Character/DBG_Character.hpp"
#include "Character/Loader/DBG_CharacterLoader.hpp"
#include "Party/Party.hpp"
#include "FightEngine/FightFSM.hpp"
#include "Logger/ILogger.h"
#include "Skill/SkillManager.hpp"
#include "Skill/ISkill.hpp"

#include "Skill/Skill/DamageSkill.hpp"

#include "Skill/Loader/SkillLoader.hpp"
#include "Skill/Loader/DBG_DamageSkillLoader.hpp"
#include "Skill\Loader\BasicSkillLoader.hpp"

#include "Character/CharacterManager.hpp"

#include "Math/ExpressionParser.hpp"

#include "Attribute\Loader\BasicAttributeLoader.hpp"
#include "Attribute\Loader\CompositeAttributeLoader.hpp"
#include "Attribute\Loader\AttributeListLoader.hpp"
#include "Attribute\Loader\AttributeLoaderFactory.hpp"

#include <SFML/Graphics.hpp>

#include <cstdio>

#include <iostream>

namespace uut
{

	void uut_Fight_std(void)
	{
		std::vector<ICharacter*> ennemies;
		DBG_Character hero("Hero", 50), ennemy("Ennemy", 10);
		Fight_States fsm_state(FS_Choose_Skill);
		ICharacter* source_character(nullptr), *target_character(nullptr);

		ennemies.resize(1, &ennemy);
		hero.setEnnemies(ennemies);
		ennemies[0] = &hero;
		ennemy.setEnnemies(ennemies);

		do
		{
			switch (fsm_state)
			{
			case FS_Choose_Skill:
				/** Act **/
				hero.selectSkill();
				ennemy.selectSkill();
				source_character = &hero;
				target_character = &ennemy;
				/** Transition **/
				fsm_state = FS_Use_Skill;
				break;
			case FS_Use_Skill:
				/** Act **/
				source_character->useSkill();
				if (!target_character->isDead())
				{
					std::swap(source_character, target_character);
				}

				/** Transition **/
				if (source_character == &hero)	/** All characters have played **/
				{
					if (hero.isDead())
					{
						fsm_state = FS_Game_Over;
					}
					else if (ennemy.isDead())
					{
						fsm_state = FS_Fight_Won;
					}
					else
					{
						fsm_state = FS_Choose_Skill;
					}
				}

				break;
			case FS_Game_Over:
				log() << "FS_Game_Over\n";
				fsm_state = FS_Done;
				break;
			case FS_Fight_Won:
				log() << "FS_Fight_Won\n";
				fsm_state = FS_Done;
				break;
			case FS_Done:
				log() << "FS_Done\n";
				break;
			default:
				break;
			}
		} while (fsm_state != FS_Done);

	}

	void uut_Fight_obj(void)
	{
		fight::FightFSM fsm;
		int status;
		DBG_Character hero("Hero", 100), ennemy("Ennemy", 50);
		std::vector<ICharacter*> fighters;
		Party hero_party, ennemy_party;
		std::vector<IParty*> ennemies_party;

		log().entranceFunction(FUNCTION_NAME);

		fighters.push_back(&hero);
		fighters.push_back(&ennemy);

		hero_party.addMember(&hero);
		ennemy_party.addMember(&ennemy);
		ennemies_party.push_back(&ennemy_party);

		fsm.initialize(hero_party, ennemies_party);

		do
		{
			status = fsm.process();
		} while (status == fsm::StatusHandlerFSM::STATUS_FSM_RUNNING);

		log() << "fsm ended with status : " << fsm.formatStatus(status) << "\n";
		log().exitFunction();
	}

	void uut_TestLoadingSkills(void)
	{
		SkillManager sm;
		std::vector<std::unique_ptr<SkillLoader>> loaders;
		std::string file_path("C:/Users/Janniere Sylvain/Documents/GitHub/rpg_engine/Resources/Data/Skills.xml");
		std::vector<std::string> skills_names;
		DBG_Character c("JaJa", 50);

		log().entranceFunction(FUNCTION_NAME);

		skills_names.push_back("Attack +1");
		skills_names.push_back("Attack -1");
		skills_names.push_back("Attack *2");
		skills_names.push_back("Attack /2");
		skills_names.push_back("Attack %75");
		skills_names.push_back("Attack 5");

		loaders.push_back(std::unique_ptr<SkillLoader>(new DBG_DamageSkillLoader("DBG_DamageSkill")));

		log() << sm.load(file_path, loaders) << "\n";

		log().startBlock("testing getting skills");

		for (auto& skill_name : skills_names)
		{
			std::unique_ptr<ISkill> skill(nullptr);
			log() << "getting " << skill_name << " : \t";
			skill = std::move(sm.getSkill(skill_name, c));
			log() << skill.get() << "\n";
		}

		log().endBlock();

		log().exitFunction();
	}

	void uut_Test_Sf_String(void)
	{
		std::string title("ééé");
		sf::Font font;
		sf::Text text;
		sf::RenderWindow window(sf::VideoMode(640, 480), "ààà");
		bool font_loaded;
		std::string res_path("C:/Users/Janniere Sylvain/Documents/GitHub/rpg_engine/Resources/");

		log().entranceFunction(FUNCTION_NAME);

		//font_loaded = font.loadFromFile(res_path + "Font/firestarter/FIRESTARTER.ttf");
		font_loaded = font.loadFromFile(res_path + "Font/shaded_larch/ShadedLarch_PERSONAL_USE.ttf");

		window.setTitle(title.c_str());

		// choix de la police à utiliser
		if (font_loaded)
			text.setFont(font); // font est un sf::Font

		// choix de la chaîne de caractères à afficher
		text.setString(sf::String("Hello world éàè@"));

		// choix de la taille des caractères
		text.setCharacterSize(24); // exprimée en pixels, pas en points !

		// choix de la couleur du texte
		text.setColor(sf::Color(0, 100, 0));
		text.setScale(2.0f, 2.0f);

		// choix du style du texte
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color::Green);
			// puis, dans la boucle de dessin, entre window.clear() et window.display()
			window.draw(text);
			window.display();
		}
		log().exitFunction();
	}

	void uut_Loading_Characters(void)
	{
		std::unique_ptr<ICharacter> character(nullptr);
		CharacterManager cm;
		SkillManager sm;
		std::vector<std::unique_ptr<SkillLoader>> skill_loaders;
		std::vector<std::unique_ptr<CharacterLoader>> char_loaders;
		std::string res_path("C:/Users/Janniere Sylvain/Documents/GitHub/rpg_engine/Resources/"),
					skills_file("Data/Skills.xml"),
					characters_file("Data/Mobs.xml"),
					character_to_get("Toto");

		log().entranceFunction(FUNCTION_NAME);

		skill_loaders.push_back(std::unique_ptr<SkillLoader>(new DBG_DamageSkillLoader("DBG_DamageSkill")));
		char_loaders.push_back(std::unique_ptr<CharacterLoader>(new DBG_CharacterLoader("DBG_Character")));

		if (sm.load(res_path + skills_file, skill_loaders))
		{
			if (cm.load(res_path + characters_file, char_loaders, sm))
			{
				character = cm.getCharacter(character_to_get);
				character->dump(log());
			}
			else
				log() << "failed loading characters\n";
		}
		else
			log() << "failed loading skills\n";

		log().exitFunction();
	}
	
	void uut_ExpressionParser(void)
	{
		int res;
		bool parsed_succefull;
		VariableList var_list;
		std::vector<std::string> str_test;

		ExpressionParser<int> parser;

		str_test.push_back("35 + 5 - 6");
		str_test.push_back("-6+35+5");
		str_test.push_back("(1-2+3)*4");
		str_test.push_back("24");
		str_test.push_back("(a-b+c)*d");
		str_test.push_back("owner.attack - target.defense");

		var_list.setVariable("a", "1");
		var_list.setVariable("b", "2");
		var_list.setVariable("c", "3");
		var_list.setVariable("d", "4");
		var_list.setVariable("owner.attack", "10");
		var_list.setVariable("target.defense", "5");

		log().entranceFunction(FUNCTION_NAME);

		for (auto& a : str_test)
		{
			log().startBlock(a.c_str());
			log() << "Evaluating \"" << a << "\"\n";

			parsed_succefull = parser.parse(a, var_list);
			log() << "Parsing..." << parsed_succefull << "\n";
			if (parsed_succefull == true)
			{
				if (parser.getResult(res) == true)
					log() << "\"" << a << "\" = \"" << misc::numberToString(res) << "\"\n";
				else
					log() << "Error : " << parser.getError() << "\n";
			}
			else
			{
				log() << "Error : " << parser.getError() << "\n";
			}

			log().endBlock();
		}		

		log().exitFunction();
	}

	void uut_AttributeLoading(void)
	{
		std::unique_ptr<TiXmlElement> element(nullptr);
		std::unique_ptr<IAttribute> attribute(nullptr);
		std::vector<std::unique_ptr<IAttribute>> attributes;
		int attribute_value;
		BasicAttributeLoader basic_attribute_loader;
		CompositeAttributeLoader composite_attribute_loader;
		AttributeLoaderFactory attribute_loader_factory;
		AttributeListLoader attribute_list_loader(attribute_loader_factory);

		log().entranceFunction(FUNCTION_NAME);
		log().startBlock("BasicAttribute");
		/** BasicAttribute **/
		{
			element.reset(new TiXmlElement(basic_attribute_loader.getElementName()));
			element->SetAttribute("name", "hp");
			element->SetAttribute("value", 10);
			attribute = std::move(basic_attribute_loader.load(*element));

			element->Print(stdout, -1);

			assert(attribute != nullptr);
			assert(attribute->getName() == "hp");
			assert(attribute->getValue(attribute->getName(), attribute_value) == true);
			assert(attribute_value == 10);
		}
		log().endBlock();

		log().startBlock("CompositAttribute");
		/** CompositAttribute **/
		{
			element.reset(new TiXmlElement(composite_attribute_loader.getElementName()));
			element->SetAttribute("name", "hp");
			element->LinkEndChild(new TiXmlElement(basic_attribute_loader.getElementName()));
			element->FirstChildElement()->SetAttribute("name", "current");
			element->FirstChildElement()->SetAttribute("value", 10);
			element->LinkEndChild(new TiXmlElement(basic_attribute_loader.getElementName()));
			element->LastChild()->ToElement()->SetAttribute("name", "max");
			element->LastChild()->ToElement()->SetAttribute("value", 50);

			element->Print(stdout, -1);

			attribute = std::move(composite_attribute_loader.load(*element));
			assert(attribute != nullptr);
			assert(attribute->getName() == "hp");
			assert(attribute->getValue("hp.current", attribute_value) == true);
			assert(attribute_value == 10);
			assert(attribute->getValue("hp.max", attribute_value) == true);
			assert(attribute_value == 50);
			assert(attribute->getValue("hp", attribute_value) == false);
			assert(attribute_value == 50);
		}
		log().endBlock();

		log().startBlock("AttributeList");
		/** AttributeList **/
		{
			element.reset(new TiXmlElement(attribute_list_loader.getElementName()));
			element->LinkEndChild(new TiXmlElement(composite_attribute_loader.getElementName()));
			element->FirstChildElement()->SetAttribute("name", "hp");
			element->FirstChildElement()->LinkEndChild(new TiXmlElement(basic_attribute_loader.getElementName()));
			element->FirstChildElement()->FirstChildElement()->SetAttribute("name", "hp.current");
			element->FirstChildElement()->FirstChildElement()->SetAttribute("value", 10);
			element->LinkEndChild(new TiXmlElement(basic_attribute_loader.getElementName()));
			element->LastChild()->ToElement()->SetAttribute("name", "damages");
			element->LastChild()->ToElement()->SetAttribute("value", 5);

			element->Print(stdout, -1);

			assert(attribute_list_loader.load(*element, attributes) == true);
			assert(attributes.size() == 2);
		}
		log().endBlock();

		log().exitFunction();
	}

	void uut_SkillLoading(void)
	{
		std::unique_ptr<ISkill> basic_skill(nullptr);
		std::unique_ptr<TiXmlElement> element;
		AttributeLoaderFactory attribute_loader_factory;
		BasicSkillLoader basic_skill_loader;

		basic_skill_loader.setAttributeLoaderFactory(&attribute_loader_factory);

		log().entranceFunction(FUNCTION_NAME);
		
		element.reset(new TiXmlElement("BasicSkill"));
		element->SetAttribute("name", "fire_ball");
		element->SetAttribute("target_attribute", "hp.current");
		element->SetAttribute("formula", "(owner.attack - target.defense)*skill.damages");
		element->LinkEndChild(new TiXmlElement("AttributeList"));
		element->FirstChildElement()->LinkEndChild(new TiXmlElement("BasicAttribute"));
		element->FirstChildElement()->FirstChildElement()->SetAttribute("name", "damages");
		element->FirstChildElement()->FirstChildElement()->SetAttribute("value", 5);

		element->Print(stdout, -1);

		basic_skill = std::move(basic_skill_loader.load(*element));
		assert(basic_skill != nullptr);
		assert(basic_skill->getAttribute("damages") != nullptr);

		log().exitFunction();
	}

	void uut_CharacterLoading(void)
	{
		log().entranceFunction(FUNCTION_NAME);
		log().exitFunction();
	}

}
