#include "ComponentDrawable.hpp"
#include <memory>

ComponentDrawable::ComponentDrawable(const ECS_ComponentId& id) : ECS_Component(id)
{}

ComponentDrawable::~ComponentDrawable()
{}

ComponentSpriteSheet::ComponentSpriteSheet()
	:ComponentDrawable(mt_Get_Id())
{}

ComponentSpriteSheet::~ComponentSpriteSheet()
{}

const ECS_ComponentId& ComponentSpriteSheet::mt_Get_Id(void)
{
	return ECS_ComponentId::POSITION;
}

void ComponentSpriteSheet::mt_Update_Position(const sf::Vector2f& world_position_px)
{
	m_sprite->mt_Set_World_Position(world_position_px.x, world_position_px.y);
}

sf::Vector2i ComponentSpriteSheet::mt_Get_Size(void) const
{
	sf::Vector2i l_ret;
	m_sprite->mt_Get_Size(l_ret.x, l_ret.y);
	return l_ret;
}

void ComponentSpriteSheet::mt_Draw(sf::RenderWindow* window)
{
	m_sprite->mt_Draw(window);
}

void ComponentSpriteSheet::mt_Load(TextureManager& texture_manager, const std::string& sprite_name)
{
	//m_sprite = std::make_unique<SpriteSheet>(texture_manager);
}
