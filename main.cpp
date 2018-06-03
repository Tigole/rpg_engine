#include <iostream>
#include <vector>
#include <SFML/System/String.hpp>

#include "Character/ICharacter.hpp"
#include "Character/Character/DBG_Character.hpp"
#include "Party/Party.hpp"

#include "FightEngine/FightFSM.hpp"

#include "_UnitUnderTest/uut.hpp"
#include "Logger/ILogger.h"

#include "Exception/Exception.hpp"

#include <cwchar>
#include <locale>
#include <locale.h>

#include "Game.hpp"

#include <SFML/Config.hpp>

using namespace std;
using namespace uut;

void delete_int(int* obj)
{
	delete obj;
}

void fn_Play(const std::string& resource_path)
{
	Game l_game(resource_path);

	while (l_game.mt_Is_Running())
	{
		l_game.mt_Update();
		l_game.mt_Render();
		l_game.mt_LateUpdate();
	}
}

int main(int argc, char** argv)
{
	vector<pair<string,void(*)(void)>> uut_functions;
#if (PLATFORM == PLATFORM_WINDOWS)
	std::string l_resource_path("C:/Users/Janniere Sylvain/Dropbox/01-Resources_rpg_engine/Resources/");
#elif (PLATFORM == PLATFORM_LINUX)
	std::string l_resource_path("/home/jaja/Documents/Git/rpg_engine/Resources/");
#endif // PLATFORM
	log().mt_Entrance_Function(FUNCTION_NAME);

	std::cout << "SFML : " << SFML_VERSION_MAJOR << '.' << SFML_VERSION_MINOR << '.' << SFML_VERSION_PATCH << '\n';
	
	if (argc > 1)
	{
		l_resource_path = argv[1];
	}
	else
	{
		//
	}

	std::cout << "Resource path : " << l_resource_path << '\n';
	std::cout << "\"Esc\" pour sortir du jeu\n\"Espace\" pour passer à la carte de jeu\n";
	std::cout << "\"a\" pour revenir dans le menu\n";

	fn_Play(l_resource_path);


#if 0
	//uut_functions.push_back(make_pair("uut_Map", uut_Map));
	uut_functions.push_back(make_pair("uut_Game", uut_Game));
	uut_functions.push_back(make_pair("uut_Tileset", uut_Tileset));
	uut_functions.push_back(make_pair("uut_TestLoadingSkills", uut_TestLoadingSkills));
	uut_functions.push_back(make_pair("uut_Test_Sf_String", uut_Test_Sf_String));
	uut_functions.push_back(make_pair("uut_Loading_Characters", uut_Loading_Characters));
	uut_functions.push_back(make_pair("uut_ExpressionParser", uut_ExpressionParser));
	uut_functions.push_back(make_pair("uut_AttributeLoading", uut_AttributeLoading));
	uut_functions.push_back(make_pair("uut_SkillLoading", uut_SkillLoading));
	uut_functions.push_back(make_pair("uut_CharacterLoading", uut_CharacterLoading));
	uut_functions.push_back(make_pair("uut_GUIBackground", uut_GUIBackground));
	uut_functions.push_back(make_pair("uut_DialogBox", uut_DialogBox));
	uut_functions.push_back(make_pair("uut_TextDialogBox", uut_TextDialogBox));
	uut_functions.push_back(make_pair("uut_MapManager", uut_MapManager));
	uut_functions.push_back(make_pair("uut_Environment", uut_Environment));
	//uut_functions.push_back(make_pair("uut_ECS_Entity", uut_ECS_Entity));
	uut_functions.push_back(make_pair("uut_XMLFileLoader", uut_XMLFileLoader));
#endif
	for (auto& a : uut_functions)
	{
		try
		{
			a.second();
		}
		catch (std::exception& e)
		{
			cerr << "[" << a.first << "] : " << e.what() << "\n";
			log().mt_Exit_Function();
		}
		catch (const IException& e)
		{
			cerr << "[" << a.first << "] : " << e.mt_What() << "\n";
			log().mt_Exit_Function();
		}
	}

	/*cout << "ééé@à" << "\n";
	log() << "ééé@à" << "\n";*/

#ifdef _WIN32
	//system("PAUSE");
#endif // __WIN32

	//setlocale(LC_ALL, old_local.c_str());

	log().mt_Exit_Function();

	return 0;
}
