#ifndef _COMPONENT_DRAWABLE_HPP
#define _COMPONENT_DRAWABLE_HPP 1

#include "ComponentPosition.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "ECS_Game/Direction.hpp"

#include "SpriteSystem/SpriteSheet.hpp"

class sf::RenderWindow;

class ComponentDrawable : public ECS_Component
{
public:
	ComponentDrawable(const ECS_ComponentId& id);
	virtual ~ComponentDrawable();

	virtual void mt_Update_Position(const sf::Vector2f& world_position_px) = 0;
	virtual sf::Vector2i mt_Get_Size(void) const = 0;
	virtual void mt_Draw(sf::RenderWindow* window) = 0;
	virtual void mt_Set_Direction(Direction d) = 0;
};

class ComponentSpriteSheet : public ComponentDrawable
{
public:
	ComponentSpriteSheet();
	~ComponentSpriteSheet();

	virtual void mt_Update_Position(const sf::Vector2f& world_position_px);
	virtual sf::Vector2i mt_Get_Size(void) const;
	virtual void mt_Draw(sf::RenderWindow* window);
	void mt_Load(TextureManager& texture_manager, const std::string& sprite_name);
	static const ECS_ComponentId& mt_Get_Id(void);
protected:
	std::unique_ptr<SpriteSheet> m_sprite;
};

#endif // _COMPONENT_DRAWABLE_HPP
