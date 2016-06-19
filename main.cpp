#include <iostream>
#include <vector>

#include "Character/ICharacter.hpp"
#include "Character/DBG_Character.hpp"
#include "FightEngine\Party.hpp"

#include "FightEngine\FightFSM.hpp"

#include "FightEngine\uut.hpp"

using namespace std;
using namespace uut;

int main(int argc, char** argv)
{
	std::vector<void(*)(void)> uut_functions;

	uut_functions.push_back(uut_Fight_std);
	uut_functions.push_back(uut_Fight_obj);

	for (auto& a : uut_functions)
	{
		a();
	}

	system("PAUSE");
	return 0;
}
