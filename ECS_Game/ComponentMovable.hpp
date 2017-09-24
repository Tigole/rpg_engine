#ifndef _COMPONENT_MOVABLE_HPP
#define _COMPONENT_MOVABLE_HPP 1

#include "ECS_Core/ECS_Component.hpp"
#include "ECS_Game/Direction.hpp"
#include <SFML/System.hpp>

class ComponentMovable : public ECS_Component
{
public:
	ComponentMovable();

	const sf::Vector2f& mt_Get_Velocity_px_per_ms(void) const;
	const sf::Vector2f& mt_Get_Accelerationpx_per_ms2(void) const;
	const sf::Vector2f& mt_Get_Speed_px_per_ms(void) const;
	float mt_Get_Max_Velocity_px_per_ms(void) const;

	void mt_Set_Velocity_px_per_ms(const sf::Vector2f& velocity);
	void mt_Set_Acceleration_px_per_ms2(const sf::Vector2f& acceleration);
	void mt_Set_Speed_px_per_ms(const sf::Vector2f& speed);
	void mt_Set_Max_Velocity(float max_velocity);

	void mt_Add_Velocity_px_per_ms(const sf::Vector2f& velocity);
	void mt_Apply_Friction_px_per_ms(const sf::Vector2f& friction);
	void mt_Accelerate_px_per_ms2(const sf::Vector2f& acceleration);

	void mt_Move(const Direction& dir);

private:
	void mt_Manage_Friction(float& vel_px_per_ms, float friction);
	sf::Vector2f m_velocity_px_per_s;
	sf::Vector2f m_speed_px_per_s;
	sf::Vector2f m_acceleration_px_per_s2;
	int m_max_velocity_px_per_s;
	//Direction m_direction;
};

#endif // !_COMPONENT_MOVABLE_HPP
