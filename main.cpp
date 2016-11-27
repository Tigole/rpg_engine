#include <iostream>
#include <vector>
#include <SFML/System/String.hpp>

#include "Character/ICharacter.hpp"
#include "Character/Character/DBG_Character.hpp"
#include "Party/Party.hpp"

#include "FightEngine/FightFSM.hpp"

#include "_UnitUnderTest/uut.hpp"
#include "Logger/ILogger.h"

#include "Exception\Exception.hpp"

#include <cwchar>
#include <locale>
#include <locale.h>

using namespace std;
using namespace uut;

void delete_int(int* obj)
{
	delete obj;
}

int main(int argc, char** argv)
{
	vector<pair<string,void(*)(void)>> uut_functions;
	//std::string old_local;

	log().entranceFunction(FUNCTION_NAME);

	//std::locale::global(std::locale("fr-FR"));

	//old_local = setlocale(LC_ALL, nullptr);

	//cout << "local : " << old_local << "\n";
	//log() << "local : " << old_local << "\n";

	//setlocale(LC_ALL, "windows-1252");

	//log() << "local : " << setlocale(LC_ALL, nullptr) << "\n";

	//uut_functions.push_back(uut_Fight_std);
	//uut_functions.push_back(uut_Fight_obj);
	
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

		for (auto& a : uut_functions)
		{
			try
			{
				a.second();
			}
			catch (std::exception& e)
			{
				cerr << "[" << a.first << "] : " << e.what() << "\n";
			}
			catch (const IException& e)
			{
				cerr << "[" << a.first << "] : " << e.what() << "\n";
			}
		}

	cout << "ééé@à" << "\n";
	log() << "ééé@à" << "\n";

#ifdef _WIN32
	system("PAUSE");
#endif // __WIN32

	//setlocale(LC_ALL, old_local.c_str());

	log().exitFunction();

	return 0;
}
