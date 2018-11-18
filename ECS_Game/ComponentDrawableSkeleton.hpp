#ifndef _COMPONENET_DRAWABLE_SKELETON_HPP
#define _COMPONENET_DRAWABLE_SKELETON_HPP 1

#include "ECS_Core/ECS_Component.hpp"
#include "ECS_Game/ComponentDrawable.hpp"
#include "ECS_Game/Direction.hpp"
#include "SpriteSystem/SkeletonAnimation.hpp"

#include <SFML/Graphics.hpp>

struct SkeletonData
{
	std::string m_id;
	sf::Sprite m_sprite;
	sf::Vector2f m_pos_offset;
	sf::Transform m_Initial_Transform;
	SkeletonData* m_parent;
};

using PartId = std::string;
using AnimId = std::string;

using AnimationSet = std::unordered_map<PartId, std::unique_ptr<SkeletonAnimation>>;
using AnimationContainer = std::unordered_map<AnimId, AnimationSet>;
using SkeletonParts = std::unordered_map<PartId, SkeletonData>;

class ComponentDrawableSkeleton : public ComponentDrawable
{
public:
	ComponentDrawableSkeleton();
	virtual void mt_Update_Position(const sf::Vector2f& world_position_px);
	virtual sf::Vector2i mt_Get_Size(void) const;
	virtual void mt_Draw(sf::RenderWindow* window);
	virtual void mt_Set_Direction(Direction d);

	void mt_Add_Part(const std::string& id, sf::Texture* texture, float x_offset, float y_offset);
	void mt_Add_Animation(const std::string& part_id, std::unique_ptr<SkeletonAnimation>& animation);
	SkeletonData* mt_Get_Part(const std::string& part_id);
	AnimationSet* mt_Get_Animation(void);

	void mt_Set_Animation(const AnimId& anim_id, bool play, bool loop);

protected:
	sf::RectangleShape l_Bounds;
	SkeletonParts m_parts;
	sf::Vector2i m_size;
	sf::Vector2f m_position;
	AnimationContainer m_animations;
	AnimationSet* m_current_animation;
};

#endif // !_COMPONENET_DRAWABLE_SKELETON_HPP