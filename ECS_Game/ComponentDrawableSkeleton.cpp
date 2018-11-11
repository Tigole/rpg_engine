#include "ComponentDrawableSkeleton.hpp"


void fn_Set_Part(const sf::Vector2f& position, sf::Sprite& sprite, const std::string& part_id, float x_offset, float y_offset)
{
	sf::FloatRect l_dimension;

	l_dimension = sprite.getLocalBounds();

	sprite.setOrigin(l_dimension.width / 2, l_dimension.height / 2);

	sprite.setPosition(position.x + x_offset, position.y + y_offset);
}

ComponentDrawableSkeleton::ComponentDrawableSkeleton()
	:ComponentDrawable(ECS_ComponentId::DRAW_SKELETON),
	l_Bounds(sf::Vector2f(100, 100))
{
	l_Bounds.setFillColor(sf::Color::Transparent);
	l_Bounds.setOutlineColor(sf::Color::Red);
	l_Bounds.setOutlineThickness(10.0f);
}

void ComponentDrawableSkeleton::mt_Update_Position(const sf::Vector2f& world_position_px)
{
	l_Bounds.setPosition(world_position_px);
	m_position = world_position_px;

	for (auto& l_part : m_parts)
		fn_Set_Part(m_position, l_part.second.m_sprite, l_part.second.m_id, l_part.second.m_pos_offset.x, l_part.second.m_pos_offset.y);
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
	//window->draw(l_Bounds);
	for (auto& l_part : m_parts)
	{
		window->draw(l_part.second.m_sprite);
	}
}

void ComponentDrawableSkeleton::mt_Add_Part(const std::string& id, sf::Texture* texture, float x_offset, float y_offset)
{
	sf::Sprite* l_sprite;

	m_parts[id].m_id = id;
	m_parts[id].m_pos_offset = sf::Vector2f(x_offset, y_offset);
	m_parts[id].m_parent = nullptr;
	l_sprite = &m_parts[id].m_sprite;
	
	//l_sprite->setScale(1.5f, 1.5f);
	l_sprite->setTexture(*texture);

	fn_Set_Part(m_position, *l_sprite, id, x_offset, y_offset);
}

SkeletonData* ComponentDrawableSkeleton::mt_Get_Part(const std::string& part_id)
{
	SkeletonData* l_Ret(nullptr);
	auto l_it = m_parts.find(part_id);

	if (l_it != m_parts.end())
	{
		l_Ret = &l_it->second;
	}

	return l_Ret;
}

void ComponentDrawableSkeleton::mt_Set_Direction(Direction d)
{
	//
}

void ComponentDrawableSkeleton::mt_Set_Animation(const std::string& anim_id, bool play, bool loop)
{
	auto l_anim_it = m_animations.find(anim_id);

	if (l_anim_it != m_animations.end())
	{
		if (m_current_animation != nullptr)
		{
			for (auto& l_anim : *m_current_animation)
			{
				l_anim.second->mt_Stop();
			}
		}

		m_current_animation = &l_anim_it->second;

		if (play == true)
		{
			for (auto& l_anim : *m_current_animation)
			{
				l_anim.second->mt_Play(loop);
			}
		}
	}
}