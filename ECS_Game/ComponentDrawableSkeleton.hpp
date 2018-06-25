#ifndef _COMPONENET_DRAWABLE_SKELETON_HPP
#define _COMPONENET_DRAWABLE_SKELETON_HPP 1

#include "ECS_Core/ECS_Component.hpp"
#include "ECS_Game/ComponentDrawable.hpp"

#include <SFML/Graphics.hpp>

struct SkeletonData
{
	sf::Sprite m_sprite;
};

class ComponentDrawableSkeleton : public ComponentDrawable
{
public:
	ComponentDrawableSkeleton();
	virtual void mt_Update_Position(const sf::Vector2f& world_position_px);
	virtual sf::Vector2i mt_Get_Size(void) const;
	virtual void mt_Draw(sf::RenderWindow* window);

	void mt_Add_Part(const std::string& id, sf::Texture* texture);

protected:
	std::unordered_map<std::string, SkeletonData> m_parts;
	sf::Vector2i m_size;
};

#endif // !_COMPONENET_DRAWABLE_SKELETON_HPP