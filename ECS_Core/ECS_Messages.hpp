#ifndef _ECS_MESSAGES_HPP
#define _ECS_MESSAGES_HPP 1

#include "ECS_Types.hpp"
#include "ECS_Game/Direction.hpp"

enum class ECS_EntityMessageId
{
	MoveRqst,
	StopMove,
	StartMoving,
	StopMoving,
	DirectionChanged,
	/*
	MOVE,
	STOP_MOVE,
	IS_MOVING,
	FRAME_CHANGE,
	STATE_CHANGED,
	SWITCH_STATE,
	DIRECTION_CHANGED,*/
};

union ECS_EntityMessageData
{
	ECS_EntityState m_state;
	Direction m_direction;
};

struct ECS_EntityMessage
{
	ECS_EntityMessageId m_id;
	ECS_EntityId m_sender;

	ECS_EntityMessageData m_data;
};

std::string fn_ECS_EntityMessageId_Enum_To_String(const ECS_EntityMessageId& id);

#endif // !_ECS_MESSAGES_HPP