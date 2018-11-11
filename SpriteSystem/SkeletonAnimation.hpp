#ifndef _SKELETON_ANIMATION_HPP
#define _SKELETON_ANIMATION_HPP 1


#include "Miscellaneous.hpp"
#include <SFML/Graphics.hpp>

struct SkeletonTransformation
{
	SkeletonTransformation();
	SkeletonTransformation(const sf::Vector2f Position, const sf::Vector2f& Scale, float Rotation, const sf::Color Color, float m_Duration);
	sf::Vector2f m_Position;
	sf::Vector2f m_Scale;
	float m_Rotation;
	sf::Color m_Color;
	float m_Duration;
};


class SkeletonAnimation
{
public:
	SkeletonAnimation();

	void mt_Reset();

	void mt_Play(bool loop);

	void mt_Stop(void);

	void mt_Update(float delta_time_s);

	sf::Vector2f mt_Interpolate_Position(void) const;
	sf::Vector2f mt_Interpolate_Scale(void) const;
	sf::Color mt_Interpolate_Color(void) const;
	void mt_Add_Step(const SkeletonTransformation& step);
	bool mt_New_Cycle(void) const;
	bool mt_Is_Playing(void) const;

private:
	sf::Sprite* m_Target;
	std::vector<SkeletonTransformation> m_Transformations;
	std::vector<SkeletonTransformation>::iterator m_Previous_Transformation;
	std::vector<SkeletonTransformation>::iterator m_Current_Transformation;
	float m_elapsed_time;
	bool m_is_playing;
	bool m_loop;
	bool m_new_cycle;
};

#endif // !_SKELETON_ANIMATION_HPP