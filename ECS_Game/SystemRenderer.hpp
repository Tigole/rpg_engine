#ifndef _SYSTEM_RENDERER_HPP
#define _SYSTEM_RENDERER_HPP 1

#include "ECS_Core/ECS_System.hpp"

#include <vector>

class ECS_SystemManager;
class ComponentDrawable;
class Window;

class SystemRenderer : public ECS_System
{
public:
	SystemRenderer(ECS_SystemManager* system_manager);

	void mt_Notify(const ECS_EntityMessage& msg);
	void mt_Update(float delta_time_ms);
	void mt_Render(Window& window, unsigned int layer);

	static ECS_SystemId mt_Get_System_Id();

private:
	ComponentDrawable* mt_Get_Drawable(const ECS_Entity& entity);
	void mt_Sort_By_Layer(void);
	std::vector<ECS_ComponentId> m_drawable_components;

};

#endif // _SYSTEM_RENDERER_HPP
