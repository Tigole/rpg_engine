#include "ComponentMovable.hpp"

ComponentMovable::ComponentMovable()
	:ECS_Component(ECS_ComponentId::MOVABLE),
	m_velocity(0.0f, 0.0f),
	m_speed(0.0f, 0.0f),
	m_acceleration(0.0f, 0.0f),
	m_max_velocity(10.0f)
{}

const sf::Vector2f& ComponentMovable::mt_Get_Velocity(void) const
{
	return m_velocity;
}

const sf::Vector2f& ComponentMovable::mt_Get_Accelerationpx(void) const
{
	return m_acceleration;
}

const sf::Vector2f& ComponentMovable::mt_Get_Speed(void) const
{
	return m_speed;
}

float ComponentMovable::mt_Get_Max_Velocity(void) const
{
	return m_max_velocity;
}

void ComponentMovable::mt_Set_Velocity(const sf::Vector2f& velocity)
{
	m_velocity = velocity;
}

void ComponentMovable::mt_Set_Acceleration(const sf::Vector2f& acceleration)
{
	m_acceleration = acceleration;
}


void ComponentMovable::mt_Set_Acceleration(float x, float y)
{
	m_acceleration.x = x;
	m_acceleration.y = y;
}

void ComponentMovable::mt_Set_Speed(const sf::Vector2f& speed)
{
	m_speed = speed;
}

void ComponentMovable::mt_Set_Max_Velocity(float max_velocity)
{
	m_max_velocity = max_velocity;
}

void ComponentMovable::mt_Add_Velocity(const sf::Vector2f& velocity)
{
	m_velocity += velocity;
	
	if (std::abs(m_velocity.x) > m_max_velocity)
	{
		if (static_cast<int>(m_velocity.x) < 0)
			m_velocity.x = -m_max_velocity;
		else
			m_velocity.x = m_max_velocity;
	}

	if (std::abs(m_velocity.y) > m_max_velocity)
	{
		if (static_cast<int>(m_velocity.y) < 0)
			m_velocity.y = -m_max_velocity;
		else
			m_velocity.y = m_max_velocity;
	}
}

void ComponentMovable::mt_Apply_Friction(const sf::Vector2f& friction)
{
	mt_Manage_Friction(m_velocity.x, friction.x);
	mt_Manage_Friction(m_velocity.y, friction.y);
}

void ComponentMovable::mt_Accelerate(const sf::Vector2f& acceleration)
{
	m_acceleration += acceleration;
}

void ComponentMovable::mt_Move(const Direction& dir)
{
	switch (dir)
	{
	case Direction::Down:
		m_acceleration.y += m_speed.y;
		break;
	case Direction::Up:
		m_acceleration.y -= m_speed.y;
		break;
	case Direction::Left:
		m_acceleration.x -= m_speed.x;
		break;
	case Direction::Right:
		m_acceleration.x += m_speed.x;
		break;
	default:
		break;
	}
}

void ComponentMovable::mt_Stop(Axis a)
{
	if (a == Axis::x)
		m_velocity.x = 0.0f;
	else
		m_velocity.y = 0.0f;
}

void ComponentMovable::mt_Set_Direction(const Direction& dir)
{
	m_direction = dir;
}

Direction ComponentMovable::mt_Get_Direction(void) const
{
	return m_direction;
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
