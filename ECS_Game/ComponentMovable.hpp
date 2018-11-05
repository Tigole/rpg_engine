#ifndef _COMPONENT_MOVABLE_HPP
#define _COMPONENT_MOVABLE_HPP 1

#include "ECS_Core/ECS_Component.hpp"
#include "ECS_Game/Direction.hpp"
#include <SFML/System.hpp>

class ComponentMovable : public ECS_Component
{
public:
	ComponentMovable();

	const sf::Vector2f& mt_Get_Velocity(void) const;
	const sf::Vector2f& mt_Get_Accelerationpx(void) const;
	const sf::Vector2f& mt_Get_Speed(void) const;
	float mt_Get_Max_Velocity(void) const;

	void mt_Set_Velocity(const sf::Vector2f& velocity);
	void mt_Set_Acceleration(const sf::Vector2f& acceleration);
	void mt_Set_Acceleration(float x, float y);
	void mt_Set_Speed(const sf::Vector2f& speed);
	void mt_Set_Max_Velocity(float max_velocity);

	void mt_Add_Velocity(const sf::Vector2f& velocity);
	void mt_Apply_Friction(const sf::Vector2f& friction);
	void mt_Accelerate(const sf::Vector2f& acceleration);

	void mt_Move(const Direction& dir);
	void mt_Stop(Axis a);
	void mt_Set_Direction(const Direction& dir);
	Direction mt_Get_Direction(void) const;

private:
	void mt_Manage_Friction(float& velocity, float friction);
	sf::Vector2f m_velocity;
	sf::Vector2f m_speed;
	sf::Vector2f m_acceleration;
	int m_max_velocity;
	Direction m_direction;
};

#endif // !_COMPONENT_MOVABLE_HPP
