#ifndef _UUT_FIGHT_ENGINE_HPP
#define _UUT_FIGHT_ENGINE_HPP 1

#include <vector>

class ICharacter;
class IParty;

namespace uut
{
	enum Fight_States
	{
		FS_Choose_Skill,
		FS_Use_Skill,
		FS_Game_Over,
		FS_Fight_Won,
		FS_Done
	};

	void uut_Fight_std(void);
	void uut_Fight_obj(void);
	void uut_TestLoadingSkills(void);
}


#endif // !_UUT_FIGHT_ENGINE_HPP