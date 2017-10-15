#include "SystemRenderer.hpp"
#include "ComponentDrawable.hpp"
#include "ComponentPosition.hpp"
#include "ECS_Core/ECS_EntityManager.hpp"
#include "Environment.hpp"
#include "Window/Window.hpp"

ECS_SystemId SystemRenderer::mt_Get_System_Id()
{
	return ECS_SystemId::RENDERER;
}

SystemRenderer::SystemRenderer(ECS_SystemManager* system_manager)
 :	ECS_System(mt_Get_System_Id()),
	m_drawable_components()
{
	m_required_components.push_back(ECS_ComponentId::POSITION);
	m_required_components.push_back(ECS_ComponentId::SPRITE_SHEET);

	m_drawable_components.push_back(ECS_ComponentId::SPRITE_SHEET);
}

void SystemRenderer::mt_Notify(const ECS_EntityMessage& msg)
{
	//
}

void SystemRenderer::mt_Update(float delta_time_ms)
{
	ECS_EntityManager& l_entity_manager(m_environment->m_entity_manager);
	ComponentPosition* l_entity_position;
	ComponentDrawable* l_entity_drawable;

	for (auto& l_current_entity : m_entities)
	{
		l_entity_position = l_entity_manager.mt_Get_Component<ComponentPosition>(l_current_entity, ECS_ComponentId::POSITION);
		l_entity_drawable = mt_Get_Drawable(l_current_entity);
		l_entity_drawable->mt_Update_Position(l_entity_position->mt_Get_Current_Position());
	}
}

ComponentDrawable* SystemRenderer::mt_Get_Drawable(const ECS_EntityId& entity)
{
	ECS_EntityManager& l_entity_manager(m_environment->m_entity_manager);
	ComponentDrawable* l_ret(nullptr);

	for (size_t i = 0; (i < m_drawable_components.size()) && (l_ret == nullptr); i++)
	{
		l_ret = l_entity_manager.mt_Get_Component<ComponentDrawable>(entity, m_drawable_components[i]);
	}

	return l_ret;
}

void SystemRenderer::mt_Render(Window& window, unsigned int layer)
{
	ECS_EntityManager& l_entity_mngr(m_environment->m_entity_manager);

	for (auto& l_entity : m_entities)
	{
		ComponentPosition* l_p_position = l_entity_mngr.mt_Get_Component<ComponentPosition>(l_entity, ECS_ComponentId::POSITION);
		ComponentDrawable* l_p_drawable;
		int l_width, l_height;
		sf::FloatRect l_drawable_bounds;

		if (l_p_position->mt_Get_Current_Layer() == layer)
		{
			l_p_drawable = mt_Get_Drawable(l_entity);
			l_width = l_p_drawable->mt_Get_Size().x;
			l_height = l_p_drawable->mt_Get_Size().y;

			l_drawable_bounds.left = l_p_position->mt_Get_Current_Position().x;
			l_drawable_bounds.top = l_p_position->mt_Get_Current_Position().y;

			l_drawable_bounds.width = l_p_drawable->mt_Get_Size().x;
			l_drawable_bounds.height = l_p_drawable->mt_Get_Size().y;

			if (window.mt_Get_View_Space().intersects(l_drawable_bounds))
			{
				l_p_drawable->mt_Draw(window.mt_Get_Renderer_Window());
			}
		}
	}
}

void SystemRenderer::mt_Sort_By_Layer(void)
{
	std::sort(m_entities.begin(), m_entities.end(), [this](ECS_EntityId l_e1, ECS_EntityId l_e2)
	{
		bool l_b_ret;
		ECS_EntityManager& l_entity_manager(this->m_environment->m_entity_manager);
		ComponentPosition* l_e1_pos, *l_e2_pos;
		
		l_e1_pos = l_entity_manager.mt_Get_Component<ComponentPosition>(l_e1, ECS_ComponentId::POSITION);
		l_e2_pos = l_entity_manager.mt_Get_Component<ComponentPosition>(l_e2, ECS_ComponentId::POSITION);

		if (l_e1_pos->mt_Get_Current_Layer() == l_e2_pos->mt_Get_Current_Layer())
			l_b_ret = l_e1_pos->mt_Get_Current_Position().y < l_e2_pos->mt_Get_Current_Position().y;
		else
			l_b_ret = l_e1_pos->mt_Get_Current_Layer() < l_e2_pos->mt_Get_Current_Layer();
		return l_b_ret;
	});
}

void SystemRenderer::mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event)
{
	//
}