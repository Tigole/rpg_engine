#ifndef _SYSTEM_SKELETON_HPP
#define _SYSTEM_SKELETON_HPP 1

#include "ECS_Core/ECS_System.hpp"

struct SkeletonData;

class SystemSkeleton : public ECS_System
{
public:
	SystemSkeleton(ECS_SystemManager* manager);

	virtual void mt_Notify(const ECS_EntityMessage& msg);
	virtual void mt_Update(float delta_time_ms);
	virtual void mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event);

protected:
	sf::Transform mt_Get_Part_Transform(SkeletonData& part);
};

#endif // !_SYSTEM_SKELETON_HPP