#include "ComponentMovable.hpp"

ComponentMovable::ComponentMovable()
	:ECS_Component(ECS_ComponentId::MOVABLE),
	m_velocity_px_per_s(0.0f, 0.0f),
	m_speed_px_per_s(0.0f, 0.0f),
	m_acceleration_px_per_s2(0.0f, 0.0f),
	m_max_velocity_px_per_s(10.0f)
{}

const sf::Vector2f& ComponentMovable::mt_Get_Velocity_px_per_ms(void) const
{
	return m_velocity_px_per_s;
}

const sf::Vector2f& ComponentMovable::mt_Get_Accelerationpx_per_ms2(void) const
{
	return m_acceleration_px_per_s2;
}

const sf::Vector2f& ComponentMovable::mt_Get_Speed_px_per_ms(void) const
{
	return m_speed_px_per_s;
}

float ComponentMovable::mt_Get_Max_Velocity_px_per_ms(void) const
{
	return m_max_velocity_px_per_s;
}

void ComponentMovable::mt_Set_Velocity_px_per_ms(const sf::Vector2f& velocity)
{
	m_velocity_px_per_s = velocity;
}

void ComponentMovable::mt_Set_Acceleration_px_per_ms2(const sf::Vector2f& acceleration)
{
	m_acceleration_px_per_s2 = acceleration;
}

void ComponentMovable::mt_Set_Speed_px_per_ms(const sf::Vector2f& speed)
{
	m_speed_px_per_s = speed;
}

void ComponentMovable::mt_Set_Max_Velocity(float max_velocity)
{
	m_max_velocity_px_per_s = max_velocity;
}

void ComponentMovable::mt_Add_Velocity_px_per_ms(const sf::Vector2f& velocity)
{
	m_velocity_px_per_s += velocity;
	
	if (std::abs(m_velocity_px_per_s.x) > m_max_velocity_px_per_s)
	{
		if (static_cast<int>(m_velocity_px_per_s.x) < 0)
			m_velocity_px_per_s.x = -m_max_velocity_px_per_s;
		else
			m_velocity_px_per_s.x = m_max_velocity_px_per_s;
	}

	if (std::abs(m_velocity_px_per_s.y) > m_max_velocity_px_per_s)
	{
		if (static_cast<int>(m_velocity_px_per_s.y) < 0)
			m_velocity_px_per_s.y = -m_max_velocity_px_per_s;
		else
			m_velocity_px_per_s.y = m_max_velocity_px_per_s;
	}
}

void ComponentMovable::mt_Apply_Friction_px_per_ms(const sf::Vector2f& friction)
{
	mt_Manage_Friction(m_velocity_px_per_s.x, friction.x);
	mt_Manage_Friction(m_velocity_px_per_s.y, friction.y);
}

void ComponentMovable::mt_Accelerate_px_per_ms2(const sf::Vector2f& acceleration)
{
	m_acceleration_px_per_s2 += acceleration;
}

void ComponentMovable::mt_Move(const Direction& dir)
{
	switch (dir)
	{
	case Direction::DOWN:
		m_acceleration_px_per_s2.y -= m_speed_px_per_s.y;
		break;
	case Direction::UP:
		m_acceleration_px_per_s2.y += m_speed_px_per_s.y;
		break;
	case Direction::LEFT:
		m_acceleration_px_per_s2.x -= m_speed_px_per_s.x;
		break;
	case Direction::RIGHT:
		m_acceleration_px_per_s2.x += m_speed_px_per_s.x;
		break;
	default:
		break;
	}
}


void ComponentMovable::mt_Manage_Friction(float& vel_px_per_ms, float friction)
{
	if (static_cast<int>(vel_px_per_ms) != 0)
	{
		if (static_cast<int>(std::abs(vel_px_per_ms) - std::abs(friction)) < 0)
		{
			vel_px_per_ms = 0;
		}
		else
		{
			if (static_cast<int>(vel_px_per_ms) < 0)
				vel_px_per_ms -= friction;
			else
				vel_px_per_ms += friction;
		}
	}
}
