#ifndef _ECS_MESSAGE_HANDLE_HPP
#define _ECS_MESSAGE_HANDLE_HPP 1

#include "Observer/MessageHandler.hpp"
#include "ECS_Messages.hpp"

#include <iostream>

class ECS_MessageHandler : public MessageHandler<ECS_EntityMessageId, ECS_EntityMessage>
{
public:
	ECS_MessageHandler(){}
protected:
	ECS_EntityMessageId mt_Get_Type(const ECS_EntityMessage& msg)
	{
		std::cout << "Msg: " << fn_ECS_EntityMessageId_Enum_To_String(msg.m_id) << '\n';
		return msg.m_id;
	}
};

#endif // !_ECS_MESSAGE_HANDLE_HPP