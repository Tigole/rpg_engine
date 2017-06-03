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
#include "Skill/Loader/BasicSkillLoader.hpp"

#include "Character/CharacterManager.hpp"

#include "Math/ExpressionParser.hpp"

#include "Attribute/Loader/BasicAttributeLoader.hpp"
#include "Attribute/Loader/CompositeAttributeLoader.hpp"
#include "Attribute/Loader/AttributeListLoader.hpp"
#include "Attribute/Loader/AttributeLoaderFactory.hpp"

#include "GUI/DialogBox.hpp"
#include "GUI/TextureManager.hpp"

#include "Exception/Exception.hpp"

#include "Map/BasicMap.hpp"
#include "Map/TilesetManager.hpp"
#include "Environment.hpp"
#include "Map/BasicMapLoader.hpp"

#include "ECS_Core\ECS_Entity.hpp"
#include "ECS_Core\ECS_EntityManager.hpp"
#include "ECS_Core/ECS_SystemManager.hpp"
#include "XMLFileLoader.hpp"

#include <SFML/Graphics.hpp>

#include <cstdio>
#include <iostream>

#include <Windows.h>

namespace uut
{

	/** Please change this path for your own working 
		(We're working to make it easier to configure from the project configuration)
	**/
	static std::string g_resource_path("C:/Users/Janniere Sylvain/Dropbox/01-Resources_rpg_engine/Resources/");

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
		std::map<std::string, std::unique_ptr<SkillLoader>> loaders;
		std::string file_path(g_resource_path + "Data/Skills.xml");
		std::vector<std::string> skills_names;
		DBG_Character c("JaJa", 50);

		log().entranceFunction(FUNCTION_NAME);

		skills_names.push_back("Attack +1");
		skills_names.push_back("Attack -1");
		skills_names.push_back("Attack *2");
		skills_names.push_back("Attack /2");
		skills_names.push_back("Attack %75");
		skills_names.push_back("Attack 5");

		loaders["DBG_DamageSkill"] = std::unique_ptr<SkillLoader>(new DBG_DamageSkillLoader("DBG_DamageSkill"));

		sm.load(file_path, loaders);

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
		sf::RenderWindow window(sf::VideoMode(640, 480), sf::String(L"ààà"));
		bool font_loaded;

		log().entranceFunction(FUNCTION_NAME);

		//font_loaded = font.loadFromFile(res_path + "Font/firestarter/FIRESTARTER.ttf");
		font_loaded = font.loadFromFile(g_resource_path + "Graphics/Fonts/shaded_larch/ShadedLarch_PERSONAL_USE.ttf");

		window.setTitle(title.c_str());

		// choix de la police à utiliser
		if (font_loaded)
			text.setFont(font); // font est un sf::Font

		// choix de la chaîne de caractères à afficher
		text.setString(sf::String(L"Hello world éàè@"));

		// choix de la taille des caractères
		text.setCharacterSize(24); // exprimée en pixels, pas en points !

		// choix de la couleur du texte
		text.setColor(sf::Color(0, 100, 0));
		text.setScale(2.0f, 2.0f);

		// choix du style du texte
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);

		window.setFramerateLimit(30);

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
		std::map<std::string, std::unique_ptr<SkillLoader>> skill_loaders;
		std::map<std::string, std::unique_ptr<CharacterLoader>> char_loaders;
		std::string skills_file("Data/Skills.xml"),
					characters_file("Data/Mobs.xml"),
					character_to_get("Toto");

		log().entranceFunction(FUNCTION_NAME);

		skill_loaders["DBG_DamageSkill"] = std::unique_ptr<SkillLoader>(new DBG_DamageSkillLoader("DBG_DamageSkill"));
		char_loaders["DBG_Character"] = std::unique_ptr<CharacterLoader>(new DBG_CharacterLoader("DBG_Character"));

		sm.load(g_resource_path + skills_file, skill_loaders);
		cm.load(g_resource_path + characters_file, char_loaders, sm);
		character = cm.getCharacter(character_to_get);
		character->dump(log());

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
		try
		{
			element.reset(new TiXmlElement(basic_attribute_loader.getElementName()));
			element->SetAttribute("name", "hp");
			element->SetAttribute("value", 10);
			attribute = std::move(basic_attribute_loader.load(*element));

			//element->Print(stdout, -1);

			assert(attribute != nullptr);
			assert(attribute->getName() == "hp");
			attribute->getValue(attribute->getName(), attribute_value);
			assert(attribute_value == 10);
		}
		catch (IException& e)
		{
			log() << e.what() << "\n";
		}
		log().endBlock();

		log().startBlock("CompositAttribute");
		/** CompositAttribute **/
		try
		{
			element.reset(new TiXmlElement(composite_attribute_loader.getElementName()));
			element->SetAttribute("name", "hp");
			element->LinkEndChild(new TiXmlElement(basic_attribute_loader.getElementName()));
			element->FirstChildElement()->SetAttribute("id", "current");
			element->FirstChildElement()->SetAttribute("value", 10);
			element->LinkEndChild(new TiXmlElement(basic_attribute_loader.getElementName()));
			element->LastChild()->ToElement()->SetAttribute("id", "max");
			element->LastChild()->ToElement()->SetAttribute("value", 50);

			//element->Print(stdout, -1);

			attribute = std::move(composite_attribute_loader.load(*element));
			assert(attribute != nullptr);
			assert(attribute->getName() == "hp");
			attribute->getValue("hp.current", attribute_value);
			assert(attribute_value == 10);
			attribute->getValue("hp.max", attribute_value);
			assert(attribute_value == 50);
			attribute->getValue("hp", attribute_value);
			assert(attribute_value == 50);
		}
		catch (IException& e)
		{
			log() << e.what() << "\n";
		}
		log().endBlock();

		log().startBlock("AttributeList");
		/** AttributeList **/
		try
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

			//element->Print(stdout, -1);

			attribute_list_loader.load(*element, attributes);
			assert(attributes.size() == 2);
		}
		catch (IException& e)
		{
			log() << e.what() << "\n";
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
		element->SetAttribute("id", "fire_ball");
		element->SetAttribute("target_attribute", "hp.current");
		element->SetAttribute("formula", "(owner.attack - target.defense)*skill.damages");
		element->LinkEndChild(new TiXmlElement("AttributeList"));
		element->FirstChildElement()->LinkEndChild(new TiXmlElement("BasicAttribute"));
		element->FirstChildElement()->FirstChildElement()->SetAttribute("id", "damages");
		element->FirstChildElement()->FirstChildElement()->SetAttribute("value", 5);

		//element->Print(stdout, -1);

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

	void uut_GUIBackground(void)
	{
		TextureManager texture_manager(g_resource_path);
		texture_manager.load(g_resource_path + "Data/Textures.xml");
		sf::RenderWindow window(sf::VideoMode(640, 480), FUNCTION_NAME);
		GUIBackground gui_bg(texture_manager, "dlg", GUIBackground::TextureData(5));

		gui_bg.setDimensions(350, 250);

		log().entranceFunction(FUNCTION_NAME);

		gui_bg.setScreenPosition(33, 33);

		window.setFramerateLimit(90);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color::Magenta);

			// puis, dans la boucle de dessin, entre window.clear() et window.display()
			window.draw(gui_bg);

			window.display();
		}
		log().exitFunction();

	}

	void uut_DialogBox(void)
	{
		TextureManager texture_manager(g_resource_path);
		texture_manager.load(g_resource_path + "Data/Textures.xml");
		sf::RenderWindow window(sf::VideoMode(640, 480), FUNCTION_NAME);
		GUIBackground gui_bg(texture_manager, "dlg", GUIBackground::TextureData(5));
		std::unique_ptr<IGUIBackground> bg_ptr(gui_bg.clone());
		BasicDialogBox dlg_box_0(bg_ptr, 32, 32+64, 64, 64);
		bg_ptr = gui_bg.clone();
		BasicDialogBox dlg_box_1(bg_ptr, 16, 32, 64*3, 64*2);
		bg_ptr = gui_bg.clone();
		BasicDialogBox dlg_box_2(bg_ptr, 300, 32, 150, 150);
		bool b_hide(false);

		log().entranceFunction(FUNCTION_NAME);

		window.setFramerateLimit(90);

		dlg_box_1.setScreenPosition(32, 64+32);
		dlg_box_0.setScreenPosition(32, 16);

		dlg_box_1.setDimensions(350, 250);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				else if (event.type == sf::Event::KeyPressed)
				{
					if (b_hide == true)
						b_hide = false;
					else
						b_hide = true;
				}
			}
			dlg_box_0.hide(b_hide);

			window.clear(sf::Color::Magenta);
			// puis, dans la boucle de dessin, entre window.clear() et window.display()
			window.draw(dlg_box_0);
			window.draw(dlg_box_1);
			window.draw(dlg_box_2);
			window.display();
		}
		log().exitFunction();
	}

	void uut_TextDialogBox(void)
	{
		TextureManager texture_manager(g_resource_path);
		texture_manager.load(g_resource_path + "Data/Textures.xml");
		sf::Font font;
		sf::RenderWindow window(sf::VideoMode(640, 480), FUNCTION_NAME);
		GUIBackground gui_bg(texture_manager, "dlg", GUIBackground::TextureData(5));
		font.loadFromFile(g_resource_path + "Graphics/Fonts/shaded_larch/ShadedLarch_PERSONAL_USE.ttf");//"Font/firestarter/FIRESTARTER.ttf");
		std::unique_ptr<IGUIBackground> bg_ptr(gui_bg.clone());
		TextDialogBox text_dialog(bg_ptr, TextDialogBox::TextData(font), 32, 32 + 64);

		log().entranceFunction(FUNCTION_NAME);

		window.setFramerateLimit(90);

		text_dialog.setText("Coucou\ntoi !");

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color::Magenta);
			// puis, dans la boucle de dessin, entre window.clear() et window.display()
			window.draw(text_dialog);
			window.display();
		}
		log().exitFunction();
	}

	void uut_Tileset(void)
	{
		TilesetManager tileset_manager(g_resource_path);
		sf::RenderWindow window(sf::VideoMode(640, 480), FUNCTION_NAME);
		Tile top_left, top_right, buttonm_right, buttom_left;

		log().entranceFunction(FUNCTION_NAME);

		tileset_manager.load(g_resource_path + "Data/Tilesets.xml");

		top_left = tileset_manager.getTile("Tileset_0", 0, 0);
		top_right = tileset_manager.getTile("Tileset_0", 1, 0);
		buttonm_right = tileset_manager.getTile("Tileset_0", 1, 1);
		buttom_left = tileset_manager.getTile("Tileset_0", 0, 1);

		window.setFramerateLimit(90);

		top_right.setPosition(50, 0);
		buttonm_right.setPosition(50, 50);
		buttom_left.setPosition(0, 50);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color::Yellow);
			
			window.draw(top_left);
			window.draw(top_right);
			window.draw(buttonm_right);
			window.draw(buttom_left);
			// puis, dans la boucle de dessin, entre window.clear() et window.display()
			window.display();
		}
		log().exitFunction();
	}

	void uut_Map(void)
	{
		Environment env(g_resource_path);
		BasicMap basic_map;
		TiXmlDocument doc;
		//sf::RenderWindow window(sf::VideoMode(640, 480), FUNCTION_NAME);

		log().entranceFunction(FUNCTION_NAME);

		//window.setFramerateLimit(90);

		env.m_tileset_manager.load(g_resource_path + "Data/Tilesets.xml");
		env.m_music_manager.load(g_resource_path + "Data/Musics.xml");

		doc.LoadFile(g_resource_path + "Data/Maps.xml");

		basic_map.load(*doc.FirstChildElement("Maps")->FirstChildElement("BasicMap"), env.m_tileset_manager);

		basic_map.run(env);

#if 0

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color::Magenta);
			// puis, dans la boucle de dessin, entre window.clear() et window.display()
			window.display();
		}
#endif 
		log().exitFunction();
	}
	void uut_MapPManager(void)
	{
		Environment l_environment(g_resource_path);
		std::map<std::string, std::unique_ptr<MapLoader>> l_loaders;
		IMap* l_map;

		l_loaders["BasicMap"].reset(new BasicMapLoader());
		l_environment.m_tileset_manager.load(g_resource_path + "Data/Tilesets.xml");
		l_environment.m_music_manager.load(g_resource_path + "Data/Musics.xml");

		l_environment.m_map_manager.load(g_resource_path + "Data/Maps.xml", l_loaders, l_environment.m_tileset_manager);

		l_map = l_environment.m_map_manager.getMap("PkmnMap");

		l_map->run(l_environment);
	}
	void uut_Environment(void)
	{
		Environment l_environment(g_resource_path);

		l_environment.load();
	}
	
	void uut_ECS_Entity(void)
	{
		TiXmlElement l_xml_element("Brol");

		ECS_EntityGenerator l_entity_generator;
		ECS_Entity l_entity_0;
		ECS_Entity l_entity_1;
		ECS_Entity l_entity_2;

		l_entity_0.save(l_xml_element);

		l_xml_element.Print(stdout, -1);
		std::cout << "\n";

		l_entity_generator.generate(l_entity_1);
		l_entity_1.save(l_xml_element);

		l_xml_element.Print(stdout, -1);
		std::cout << "\n";

		l_xml_element.SetAttribute("entity_id", 45);
		l_entity_2.load(l_xml_element, l_entity_generator);

		l_xml_element.Print(stdout, -1);
		std::cout << "\n";
	}

	void uut_ECS(void)
	{
		ECS_SystemManager l_system_manager;
		ECS_EntityManager l_entity_manager(l_system_manager);
		ECS_EntityGenerator l_entity_generator;
		std::vector<ECS_Entity> l_entities(2, ECS_Entity(l_entity_generator));
	}

	class UUT_XMLFileLoader
	{
	public:
		bool load_El(const TiXmlElement& element)
		{
			std::cout << "load_El\n";
			return true;
		}
		bool load_Data(const TiXmlElement& element)
		{
			std::cout << "load_Data\n";
			return true;
		}
		bool load_Sub(const TiXmlElement& element)
		{
			std::cout << "load_Sub\n";
			return true;
		}
	};

	void uut_XMLFileLoader(void)
	{
		XMLFileLoader l_xml_file_loader;
		UUT_XMLFileLoader l_loader;
		std::string l_xml_file(g_resource_path + "xml_file.xml");
		std::ifstream i(l_xml_file);

		if (i.is_open())
		{
			std::string line;
			while(std::getline(i, line))
				std::cout << line << "\n";
			i.close();
		}

		l_xml_file_loader.setFile(l_xml_file);
		l_xml_file_loader.addCallback("/Root/El", &UUT_XMLFileLoader::load_El, &l_loader);
		l_xml_file_loader.addCallback("/Root/El/Sub", &UUT_XMLFileLoader::load_Sub, &l_loader);
		l_xml_file_loader.addCallback("/Root/El/Sub/Data", &UUT_XMLFileLoader::load_Data, &l_loader);

		l_xml_file_loader.start();

		while(!l_xml_file_loader.isDone())
		{
			Sleep(1000);
		}

	}

}
