#ifndef _ECS_TYPES_HPP
#define _ECS_TYPES_HPP 1

#include <string>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <map>

#include "Miscellaneous.hpp"

class ECS_System;
class ECS_Component;

using ECS_EntityId = int;
using ECS_EntityMessage = int;

enum class ECS_ComponentId
{
	POSITION = 0,
	SPRITE_SHEET,
	MOVABLE,
	CONTROLLER,
	DRAW_SKELETON,

	COUNT
};
using ECS_ComponentContainer = misc::UnorderedMap<ECS_ComponentId, std::unique_ptr<ECS_Component>>;
using ECS_EntityContainer = misc::UnorderedMap<ECS_EntityId, ECS_ComponentContainer>;

enum class ECS_SystemId
{
	RENDERER = 0,
	MOVEMENT,
	CONTROL,

	COUNT
};
using ECS_SystemContainer = misc::UnorderedMap<ECS_SystemId, std::unique_ptr<ECS_System>>;

enum class ECS_EntityEvent
{
	SPAWNED = 0,
	DESPAWNED,
	COLLIDING_X,
	COLLIDING_Y,
	MOVING_LEFT,
	MOVING_RIGHT,
	MOVING_UP,
	MOVING_DOWN,
	ELEVATION_CHANGE,
	BECAME_IDLE,
	BEGAN_MOVING
};


#endif // _ECS_TYPES_HPP
