#ifndef _SYSTEM_RENDERER_HPP
#define _SYSTEM_RENDERER_HPP 1

#include "ECS_Core/ECS_System.hpp"
#include "Direction.hpp"

#include <vector>

class ECS_SystemManager;
class ComponentDrawable;
class Window;

class SystemRenderer : public ECS_System
{
public:
	SystemRenderer(ECS_SystemManager* system_manager);

	void mt_Notify(const ECS_EntityMessage& msg);
	virtual void mt_Update(float delta_time_ms);
	void mt_Render(Window& window, unsigned int layer);

	static ECS_SystemId mt_Get_System_Id();
	virtual void mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event);

private:
	ComponentDrawable* mt_Get_Drawable(const ECS_EntityId& entity);
	void mt_Sort_By_Layer(void);
	void mt_Set_Direction(ECS_EntityId entity, Direction d);

	std::vector<ECS_ComponentId> m_drawable_components;

};

#endif // _SYSTEM_RENDERER_HPP
