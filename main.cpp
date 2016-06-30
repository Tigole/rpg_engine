#include <iostream>
#include <vector>
#include <SFML\System\String.hpp>


#include "Character/ICharacter.hpp"
#include "Character/Character/DBG_Character.hpp"
#include "Party/Party.hpp"

#include "FightEngine/FightFSM.hpp"

#include "_UnitUnderTest/uut.hpp"

using namespace std;
using namespace uut;

int main(int argc, char** argv)
{
	vector<void(*)(void)> uut_functions;

	//uut_functions.push_back(uut_Fight_std);
	//uut_functions.push_back(uut_Fight_obj);
	//uut_functions.push_back(uut_TestLoadingSkills);
	uut_functions.push_back(uut_Test_Sf_String);

	for (auto& a : uut_functions)
	{
		a();
	}

	system("PAUSE");
	return 0;
}
