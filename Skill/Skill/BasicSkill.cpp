#include "BasicSkill.hpp"

#include "FSM/FSM.hpp"
#include "Attribute/IAttribute.hpp"
#include "Attribute/ICharacterised.hpp"
#include "Miscellaneous.hpp"
#include "Character/ICharacter.hpp"
#include "Logger/ILogger.h"
#include "Math/ExpressionParser.hpp"
#include "FightEngine/IBattleGroundWrapper.hpp"
#include "Effect/IEffect.hpp"

#include <algorithm>

void fn_Delete_BasicSkill(ISkill* obj)
{
	delete obj;
}

BasicSkill::BasicSkill(const std::string & id)
	:m_owner(nullptr),
	m_id(id)
{
	/** Nothing **/
}

BasicSkill::BasicSkill(const BasicSkill& bs)
 :	m_owner(nullptr),
	m_id(bs.m_id)
{
	for (auto& effect : bs.m_effects)
		m_effects.push_back(effect->mt_Clone());
}

BasicSkill::~BasicSkill()
{
	/** Nothing **/
}

BasicSkill& BasicSkill::operator=(const BasicSkill& bs)
{
	m_owner = bs.m_owner;
	m_id = bs.m_id;
	return *this;
}

std::unique_ptr<ISkill> BasicSkill::mt_Clone(void) const
{
	return std::unique_ptr<ISkill>(new BasicSkill(*this));
}

void BasicSkill::mt_Use(const std::vector<IBattleGroundWrapper*>& targets)
{
	ICharacter* t(nullptr);
	if (m_owner != nullptr)
		for (auto& target : targets)
		{
			t = target->mt_Get_Character();
			if (t != nullptr)
				for (auto& effect : m_effects)
					effect->mt_Affect(*this, *m_owner, *t);
		};
}

void BasicSkill::mt_Set_Owner(ICharacter& owner)
{
	m_owner = &owner;
}

const std::string& BasicSkill::mt_Get_Name(void) const
{
	return m_id;
}

void BasicSkill::mt_Add_Effect(const std::unique_ptr<IEffect>& effect)
{
	m_effects.push_back(effect->mt_Clone());
}
