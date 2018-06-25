#include "ComponentDrawableSkeleton.hpp"

ComponentDrawableSkeleton::ComponentDrawableSkeleton()
	:ComponentDrawable(ECS_ComponentId::DRAW_SKELETON)
{}

void ComponentDrawableSkeleton::mt_Update_Position(const sf::Vector2f& world_position_px)
{
	//
}

sf::Vector2i ComponentDrawableSkeleton::mt_Get_Size(void) const
{
	sf::Vector2i l_ret(m_size);

	/*for (auto& l_part : m_parts)
	{
		l_ret.x = std::max(l_ret.x, l_part.m_sprite.s)
	}*/

	return l_ret;
}

void ComponentDrawableSkeleton::mt_Draw(sf::RenderWindow* window)
{
	for (auto& l_part : m_parts)
	{
		window->draw(l_part.second.m_sprite);
	}
}

void ComponentDrawableSkeleton::mt_Add_Part(const std::string& id, sf::Texture* texture)
{
	m_parts[id].m_sprite.setTexture(*texture);
}