#ifndef _ECS_TYPES_HPP
#define _ECS_TYPES_HPP 1

#include <string>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <map>

class ECS_System;
class ECS_Component;

using ECS_EntityId = int;
using ECS_Entity = ECS_EntityId;
using ECS_EntityMessage = int;
using ECS_EntityEvent = int;

enum class ECS_ComponentId
{
	POSITION = 0,
	SPRITE_SHEET,
	MOVABLE,

	COUNT
};
using ECS_ComponentContainer = std::unordered_map<ECS_ComponentId, std::unique_ptr<ECS_Component>>;
using ECS_EntityContainer = std::unordered_map<ECS_EntityId, ECS_ComponentContainer>;

enum class ECS_SystemId
{
	RENDERER = 0,
	MOVEMENT,

	COUNT
};
using ECS_SystemContainer = std::unordered_map<ECS_SystemId, std::unique_ptr<ECS_System>>;


#endif // _ECS_TYPES_HPP
