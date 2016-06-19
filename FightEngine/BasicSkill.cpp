#include "BasicSkill.hpp"

#include "FSM\FSM.hpp"


BasicSkill::BasicSkill(const std::string& name)
	:m_name(name)
{
	//
}

BasicSkill::~BasicSkill()
{
	//
}

int BasicSkill::use(const std::vector<ICharacter*>& targets)
{
	return fsm::StatusHandlerFSM::STATUS_FSM_ERROR;
}