#ifndef _ECS_TYPES_HPP
#define _ECS_TYPES_HPP 1

#include <string>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <map>

class ECS_System;
class ECS_Component;
class ECS_Entity;

using ECS_EntityMessage = int;
using ECS_EntityEvent = int;

using ECS_ComponentId = std::string;
using ECS_ComponentContainer = std::map<ECS_ComponentId, std::unique_ptr<ECS_Component>>;
using ECS_EntityContainer = std::map<ECS_Entity, ECS_ComponentContainer>;

using ECS_SystemId = std::string;
using ECS_SystemContainer = std::unordered_map<ECS_SystemId, std::unique_ptr<ECS_System>>;

#endif // _ECS_TYPES_HPP
