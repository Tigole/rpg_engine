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

#include "ECS_Core/ECS_Entity.hpp"
#include "ECS_Core/ECS_EntityManager.hpp"
#include "ECS_Core/ECS_SystemManager.hpp"
#include "XMLFileLoader.hpp"

#include <SFML/Graphics.hpp>

#include <cstdio>
#include <iostream>

//#include <Windows.h>

namespace uut
{

	/** Please change this path for your own working
		(We're working to make it easier to configure from the project configuration)
	**/
#if (PLATFORM == PLATFORM_WINDOWS)
	static std::string g_resource_path("C:/Users/Janniere Sylvain/Dropbox/01-Resources_rpg_engine/Resources/");
#elif (PLATFORM == PLATFORM_LINUX)
	static std::string g_resource_path("/home/jaja/Documents/Git/rpg_engine/Resources/");
#endif // PLATFORM
	void uut_Fight_std(void)
	{
		std::vector<ICharacter*> ennemies;
		DBG_Character hero("Hero", 50), ennemy("Ennemy", 10);
		Fight_States fsm_state(FS_Choose_Skill);
		ICharacter* source_character(nullptr), *target_character(nullptr);

		ennemies.resize(1, &ennemy);
		hero.mt_Set_Ennemies(ennemies);
		ennemies[0] = &hero;
		ennemy.mt_Set_Ennemies(ennemies);

		do
		{
			switch (fsm_state)
			{
			case FS_Choose_Skill:
				/** Act **/
				hero.mt_Select_Skill();
				ennemy.mt_Select_Skill();
				source_character = &hero;
				target_character = &ennemy;
				/** Transition **/
				fsm_state = FS_Use_Skill;
				break;
			case FS_Use_Skill:
				/** Act **/
				source_character->mt_Use_Skill();
				if (!target_character->mt_Is_Dead())
				{
					std::swap(source_character, target_character);
				}

				/** Transition **/
				if (source_character == &hero)	/** All characters have played **/
				{
					if (hero.mt_Is_Dead())
					{
						fsm_state = FS_Game_Over;
					}
					else if (ennemy.mt_Is_Dead())
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

		log().mt_Entrance_Function(FUNCTION_NAME);

		fighters.push_back(&hero);
		fighters.push_back(&ennemy);

		hero_party.mt_Add_Member(&hero);
		ennemy_party.mt_Add_Member(&ennemy);
		ennemies_party.push_back(&ennemy_party);

		fsm.mt_Initialize(hero_party, ennemies_party);

		do
		{
			status = fsm.mt_Process();
		} while (status == fsm::StatusHandlerFSM::STATUS_FSM_RUNNING);

		log() << "fsm ended with status : " << fsm.mt_Format_Status(status) << "\n";
		log().mt_Exit_Function();
	}

	void uut_TestLoadingSkills(void)
	{
		SkillManager sm;
		std::map<std::string, std::unique_ptr<SkillLoader>> loaders;
		std::string file_path(g_resource_path + "Data/Skills.xml");
		std::vector<std::string> skills_names;
		DBG_Character c("JaJa", 50);

		log().mt_Entrance_Function(FUNCTION_NAME);

		skills_names.push_back("Attack +1");
		skills_names.push_back("Attack -1");
		skills_names.push_back("Attack *2");
		skills_names.push_back("Attack /2");
		skills_names.push_back("Attack %75");
		skills_names.push_back("Attack 5");

		loaders["DBG_DamageSkill"] = std::unique_ptr<SkillLoader>(new DBG_DamageSkillLoader("DBG_DamageSkill"));

		sm.mt_Load(file_path, loaders);

		log().mt_Start_Block("testing getting skills");

		for (auto& skill_name : skills_names)
		{
			std::unique_ptr<ISkill> skill(nullptr);
			log() << "getting " << skill_name << " : \t";
			skill = std::move(sm.mt_Get_Skill(skill_name, c));
			log() << skill.get() << "\n";
		}

		log().mt_End_Block();

		log().mt_Exit_Function();
	}

	void uut_Test_Sf_String(void)
	{
		std::string title("ééé");
		sf::Font font;
		sf::Text text;
		sf::RenderWindow window(sf::VideoMode(640, 480), sf::String(L"ààà"));
		bool font_loaded;

		log().mt_Entrance_Function(FUNCTION_NAME);

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
		log().mt_Exit_Function();
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

		log().mt_Entrance_Function(FUNCTION_NAME);

		skill_loaders["DBG_DamageSkill"] = std::unique_ptr<SkillLoader>(new DBG_DamageSkillLoader("DBG_DamageSkill"));
		char_loaders["DBG_Character"] = std::unique_ptr<CharacterLoader>(new DBG_CharacterLoader("DBG_Character"));

		sm.mt_Load(g_resource_path + skills_file, skill_loaders);
		cm.mt_Load(g_resource_path + characters_file, char_loaders, sm);
		character = cm.mt_Get_Character(character_to_get);
		character->mt_Dump(log());

		log().mt_Exit_Function();
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

		var_list.mt_Set_Variable("a", "1");
		var_list.mt_Set_Variable("b", "2");
		var_list.mt_Set_Variable("c", "3");
		var_list.mt_Set_Variable("d", "4");
		var_list.mt_Set_Variable("owner.attack", "10");
		var_list.mt_Set_Variable("target.defense", "5");

		log().mt_Entrance_Function(FUNCTION_NAME);

		for (auto& a : str_test)
		{
			log().mt_Start_Block(a.c_str());
			log() << "Evaluating \"" << a << "\"\n";

			parsed_succefull = parser.mt_Parse(a, var_list);
			log() << "Parsing..." << parsed_succefull << "\n";
			if (parsed_succefull == true)
			{
				if (parser.mt_Get_Result(res) == true)
					log() << "\"" << a << "\" = \"" << misc::fn_Number_To_String(res) << "\"\n";
				else
					log() << "Error : " << parser.mt_Get_Error() << "\n";
			}
			else
			{
				log() << "Error : " << parser.mt_Get_Error() << "\n";
			}

			log().mt_End_Block();
		}

		log().mt_Exit_Function();
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

		log().mt_Entrance_Function(FUNCTION_NAME);
		log().mt_Start_Block("BasicAttribute");
		/** BasicAttribute **/
		try
		{
			element.reset(new TiXmlElement(basic_attribute_loader.mt_Get_Element_Name()));
			element->SetAttribute("name", "hp");
			element->SetAttribute("value", 10);
			attribute = std::move(basic_attribute_loader.mt_Load(*element));

			//element->Print(stdout, -1);

			assert(attribute != nullptr);
			assert(attribute->mt_Get_Name() == "hp");
			attribute->mt_Get_Value(attribute->mt_Get_Name(), attribute_value);
			assert(attribute_value == 10);
		}
		catch (IException& e)
		{
			log() << e.mt_What() << "\n";
		}
		log().mt_End_Block();

		log().mt_Start_Block("CompositAttribute");
		/** CompositAttribute **/
		try
		{
			element.reset(new TiXmlElement(composite_attribute_loader.mt_Get_Element_Name()));
			element->SetAttribute("name", "hp");
			element->LinkEndChild(new TiXmlElement(basic_attribute_loader.mt_Get_Element_Name()));
			element->FirstChildElement()->SetAttribute("id", "current");
			element->FirstChildElement()->SetAttribute("value", 10);
			element->LinkEndChild(new TiXmlElement(basic_attribute_loader.mt_Get_Element_Name()));
			element->LastChild()->ToElement()->SetAttribute("id", "max");
			element->LastChild()->ToElement()->SetAttribute("value", 50);

			//element->Print(stdout, -1);

			attribute = std::move(composite_attribute_loader.mt_Load(*element));
			assert(attribute != nullptr);
			assert(attribute->mt_Get_Name() == "hp");
			attribute->mt_Get_Value("hp.current", attribute_value);
			assert(attribute_value == 10);
			attribute->mt_Get_Value("hp.max", attribute_value);
			assert(attribute_value == 50);
			attribute->mt_Get_Value("hp", attribute_value);
			assert(attribute_value == 50);
		}
		catch (IException& e)
		{
			log() << e.mt_What() << "\n";
		}
		log().mt_End_Block();

		log().mt_Start_Block("AttributeList");
		/** AttributeList **/
		try
		{
			element.reset(new TiXmlElement(attribute_list_loader.mt_Get_Element_Name()));
			element->LinkEndChild(new TiXmlElement(composite_attribute_loader.mt_Get_Element_Name()));
			element->FirstChildElement()->SetAttribute("name", "hp");
			element->FirstChildElement()->LinkEndChild(new TiXmlElement(basic_attribute_loader.mt_Get_Element_Name()));
			element->FirstChildElement()->FirstChildElement()->SetAttribute("name", "hp.current");
			element->FirstChildElement()->FirstChildElement()->SetAttribute("value", 10);
			element->LinkEndChild(new TiXmlElement(basic_attribute_loader.mt_Get_Element_Name()));
			element->LastChild()->ToElement()->SetAttribute("name", "damages");
			element->LastChild()->ToElement()->SetAttribute("value", 5);

			//element->Print(stdout, -1);

			attribute_list_loader.mt_Load(*element, attributes);
			assert(attributes.size() == 2);
		}
		catch (IException& e)
		{
			log() << e.mt_What() << "\n";
		}
		log().mt_End_Block();

		log().mt_Exit_Function();
	}

	void uut_SkillLoading(void)
	{
		std::unique_ptr<ISkill> basic_skill(nullptr);
		std::unique_ptr<TiXmlElement> element;
		AttributeLoaderFactory attribute_loader_factory;
		BasicSkillLoader basic_skill_loader;

		basic_skill_loader.mt_Set_AttributeLoaderFactory(&attribute_loader_factory);

		log().mt_Entrance_Function(FUNCTION_NAME);

		element.reset(new TiXmlElement("BasicSkill"));
		element->SetAttribute("id", "fire_ball");
		element->SetAttribute("target_attribute", "hp.current");
		element->SetAttribute("formula", "(owner.attack - target.defense)*skill.damages");
		element->LinkEndChild(new TiXmlElement("AttributeList"));
		element->FirstChildElement()->LinkEndChild(new TiXmlElement("BasicAttribute"));
		element->FirstChildElement()->FirstChildElement()->SetAttribute("id", "damages");
		element->FirstChildElement()->FirstChildElement()->SetAttribute("value", 5);

		basic_skill = std::move(basic_skill_loader.mt_Load(*element));
		assert(basic_skill != nullptr);
		assert(basic_skill->mt_Get_Attribute("damages") != nullptr);

		log().mt_Exit_Function();
	}

	void uut_CharacterLoading(void)
	{
		log().mt_Entrance_Function(FUNCTION_NAME);
		log().mt_Exit_Function();
	}

	void uut_GUIBackground(void)
	{
		TextureManager texture_manager(g_resource_path);
		texture_manager.mt_Load(g_resource_path + "Data/Textures.xml");
		sf::RenderWindow window(sf::VideoMode(640, 480), FUNCTION_NAME);
		GUIBackground gui_bg(texture_manager, "dlg", GUIBackground::TextureData(5));

		gui_bg.mt_Set_Dimensions(350, 250);

		log().mt_Entrance_Function(FUNCTION_NAME);

		gui_bg.mt_Set_Screen_Position(33, 33);

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
		log().mt_Exit_Function();

	}

	void uut_DialogBox(void)
	{
		TextureManager texture_manager(g_resource_path);
		texture_manager.mt_Load(g_resource_path + "Data/Textures.xml");
		sf::RenderWindow window(sf::VideoMode(640, 480), FUNCTION_NAME);
		GUIBackground gui_bg(texture_manager, "dlg", GUIBackground::TextureData(5));
		std::unique_ptr<IGUIBackground> bg_ptr(gui_bg.mt_Clone());
		BasicDialogBox dlg_box_0(bg_ptr, 32, 32+64, 64, 64);
		bg_ptr = gui_bg.mt_Clone();
		BasicDialogBox dlg_box_1(bg_ptr, 16, 32, 64*3, 64*2);
		bg_ptr = gui_bg.mt_Clone();
		BasicDialogBox dlg_box_2(bg_ptr, 300, 32, 150, 150);
		bool b_hide(false);

		log().mt_Entrance_Function(FUNCTION_NAME);

		window.setFramerateLimit(90);

		dlg_box_1.mt_Set_Screen_Position(32, 64+32);
		dlg_box_0.mt_Set_Screen_Position(32, 16);

		dlg_box_1.mt_Set_Dimensions(350, 250);

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
			dlg_box_0.mt_Hide(b_hide);

			window.clear(sf::Color::Magenta);
			// puis, dans la boucle de dessin, entre window.clear() et window.display()
			window.draw(dlg_box_0);
			window.draw(dlg_box_1);
			window.draw(dlg_box_2);
			window.display();
		}
		log().mt_Exit_Function();
	}

	void uut_TextDialogBox(void)
	{
		TextureManager texture_manager(g_resource_path);
		texture_manager.mt_Load(g_resource_path + "Data/Textures.xml");
		sf::Font font;
		sf::RenderWindow window(sf::VideoMode(640, 480), FUNCTION_NAME);
		GUIBackground gui_bg(texture_manager, "dlg", GUIBackground::TextureData(5));
		font.loadFromFile(g_resource_path + "Graphics/Fonts/shaded_larch/ShadedLarch_PERSONAL_USE.ttf");//"Font/firestarter/FIRESTARTER.ttf");
		std::unique_ptr<IGUIBackground> bg_ptr(gui_bg.mt_Clone());
		TextDialogBox text_dialog(bg_ptr, TextDialogBox::TextData(font), 32, 32 + 64);

		log().mt_Entrance_Function(FUNCTION_NAME);

		window.setFramerateLimit(90);

		text_dialog.mt_Set_Text("Coucou\ntoi !");

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
		log().mt_Exit_Function();
	}

	void uut_Tileset(void)
	{
		TilesetManager tileset_manager(g_resource_path);
		sf::RenderWindow window(sf::VideoMode(640, 480), FUNCTION_NAME);
		Tile top_left, top_right, buttonm_right, buttom_left;

		log().mt_Entrance_Function(FUNCTION_NAME);

		tileset_manager.mt_Load(g_resource_path + "Data/Tilesets.xml");

		top_left = tileset_manager.mt_Get_Tile("Tileset_0", 0, 0);
		top_right = tileset_manager.mt_Get_Tile("Tileset_0", 1, 0);
		buttonm_right = tileset_manager.mt_Get_Tile("Tileset_0", 1, 1);
		buttom_left = tileset_manager.mt_Get_Tile("Tileset_0", 0, 1);

		window.setFramerateLimit(90);

		top_right.m_sprite.setPosition(50, 0);
		buttonm_right.m_sprite.setPosition(50, 50);
		buttom_left.m_sprite.setPosition(0, 50);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color::Yellow);

			window.draw(top_left.m_sprite);
			window.draw(top_right.m_sprite);
			window.draw(buttonm_right.m_sprite);
			window.draw(buttom_left.m_sprite);
			// puis, dans la boucle de dessin, entre window.clear() et window.display()
			window.display();
		}
		log().mt_Exit_Function();
	}

	void uut_Map(void)
	{
		Environment env(g_resource_path);
		std::unique_ptr<IMap> basic_map;
		BasicMapLoader loader(env.m_tileset_manager);
		XMLFileLoader l_xml_loader;

		log().mt_Entrance_Function(FUNCTION_NAME);

		env.m_tileset_manager.mt_Load(g_resource_path + "Data/Tilesets.xml");
		env.m_music_manager.mt_Load(g_resource_path + "Data/Musics.xml");

		loader.mt_Prepare(l_xml_loader, g_resource_path + "Data/Map_0002.xml");

		l_xml_loader.mt_Start();
		while (l_xml_loader.mt_Is_Done() == false)
			sf::sleep(sf::milliseconds(100));

		basic_map = loader.mt_Get_Map();
		basic_map->mt_Run(env);

		log().mt_Exit_Function();
	}

	void uut_MapManager(void)
	{
		/*Environment l_environment(g_resource_path);
		std::map<std::string, std::unique_ptr<IMapLoader>> l_loaders;
		IMap* l_map;
		BasicMap l_basic_map;

		l_loaders["BasicMap"].reset(new BasicMapLoader(l_basic_map, l_environment.m_tileset_manager));
		l_environment.m_tileset_manager.load(g_resource_path + "Data/Tilesets.xml");
		l_environment.m_music_manager.load(g_resource_path + "Data/Musics.xml");

		l_environment.m_map_manager.load(g_resource_path + "Data/Maps.xml", l_loaders, l_environment.m_tileset_manager);

		l_map = l_environment.m_map_manager.getMap("PkmnMap");

		l_map->run(l_environment);*/
	}
	void uut_Environment(void)
	{
		Environment l_environment(g_resource_path);

		l_environment.mt_Load();
	}
#if 0
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
#endif // 0
	class UUT_XMLFileLoader
	{
	public:
		bool load_El(const XML_Element& element)
		{
			std::cout << "load_El\n";
			return true;
		}
		bool load_Data(const XML_Element& element)
		{
			std::cout << "load_Data\n";
			return true;
		}
		bool load_Sub(const XML_Element& element)
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

		l_xml_file_loader.mt_Set_File(l_xml_file);
		l_xml_file_loader.mt_Add_On_Entry_Callback("/Root/El", &UUT_XMLFileLoader::load_El, &l_loader);
		l_xml_file_loader.mt_Add_On_Entry_Callback("/Root/El/Sub", &UUT_XMLFileLoader::load_Sub, &l_loader);
		l_xml_file_loader.mt_Add_On_Entry_Callback("/Root/El/Sub/Data", &UUT_XMLFileLoader::load_Data, &l_loader);

		l_xml_file_loader.mt_Start();

		while(!l_xml_file_loader.mt_Is_Done())
		{
			sf::sleep(sf::milliseconds(100));
		}

	}

}
