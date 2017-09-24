#ifndef _IBATTLEGROUND_WRAPPER_H
#define _IBATTLEGROUND_WRAPPER_H 1

class ICharacter;

class IBattleGroundWrapper
{
public:
	virtual ~IBattleGroundWrapper(){}

	virtual ICharacter* mt_Get_Character(void) = 0;
};

#endif // !_IBATTLEGROUND_WRAPPER_H
