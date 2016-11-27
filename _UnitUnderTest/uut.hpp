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
	void uut_Test_Sf_String(void);
	void uut_Loading_Characters(void);
	void uut_ExpressionParser(void);
	void uut_AttributeLoading(void);
	void uut_SkillLoading(void);
	void uut_CharacterLoading(void);
	void uut_GUIBackground(void);
	void uut_DialogBox(void);
	void uut_TextDialogBox(void);
}


#endif // !_UUT_FIGHT_ENGINE_HPP
