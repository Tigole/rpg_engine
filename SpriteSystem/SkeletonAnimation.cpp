#include "SkeletonAnimation.hpp"


SkeletonTransformation::SkeletonTransformation()
{}

SkeletonTransformation::SkeletonTransformation(const sf::Vector2f Position, const sf::Vector2f& Scale, float Rotation, const sf::Color Color, float m_Duration)
	:m_Position(Position),
	m_Scale(Scale),
	m_Rotation(Rotation),
	m_Color(Color),
	m_Duration(m_Duration)
{}

SkeletonAnimation::SkeletonAnimation()
{
	mt_Add_Step(SkeletonTransformation({ 0.0f, 0.0f }, { 1.0f, 1.0f }, 0.0f, sf::Color::White, 0.0f));
}

void SkeletonAnimation::mt_Reset()
{
	if (m_Transformations.size() > 1)
	{
		m_Current_Transformation = m_Transformations.begin() + 1;
	}
	else
	{
		m_Current_Transformation = m_Transformations.begin();
	}
	m_Previous_Transformation = m_Transformations.begin();

	m_is_playing = false;
	m_new_cycle = false;
}

void SkeletonAnimation::mt_Play(bool loop)
{
	mt_Reset();
	m_is_playing = true;
	m_loop = loop;
}

void SkeletonAnimation::mt_Stop(void)
{
	m_is_playing = false;
}

void SkeletonAnimation::mt_Update(float delta_time_s)
{
	if (m_is_playing)
	{
		m_elapsed_time += delta_time_s;
		m_new_cycle = false;

		if (m_elapsed_time >= m_Current_Transformation->m_Duration)
		{
			m_Previous_Transformation = m_Current_Transformation;
			m_Current_Transformation++;
			if (m_Current_Transformation == m_Transformations.end())
			{
				if (m_loop)
				{
					m_Current_Transformation = m_Transformations.begin();
					m_new_cycle = true;
				}
				else
				{
					m_is_playing = false;
				}
			}
		}
		m_Target->setPosition(mt_Interpolate_Position());
		m_Target->setScale(mt_Interpolate_Scale());
		m_Target->setRotation(misc::fn_Time_Interpolate(0.0f, m_Current_Transformation->m_Duration, m_Previous_Transformation->m_Rotation, m_Current_Transformation->m_Rotation, m_elapsed_time));
		m_Target->setColor(mt_Interpolate_Color());
	}
}

sf::Vector2f SkeletonAnimation::mt_Interpolate_Position(void) const
{
	sf::Vector2f l_Ret;

	l_Ret.x = misc::fn_Time_Interpolate(0.0f, m_Current_Transformation->m_Duration, m_Previous_Transformation->m_Position.x, m_Current_Transformation->m_Position.x, m_elapsed_time);
	l_Ret.y = misc::fn_Time_Interpolate(0.0f, m_Current_Transformation->m_Duration, m_Previous_Transformation->m_Position.y, m_Current_Transformation->m_Position.y, m_elapsed_time);

	return l_Ret;
}

sf::Vector2f SkeletonAnimation::mt_Interpolate_Scale(void) const
{
	sf::Vector2f l_Ret;

	l_Ret.x = misc::fn_Time_Interpolate(0.0f, m_Current_Transformation->m_Duration, m_Previous_Transformation->m_Scale.x, m_Current_Transformation->m_Scale.x, m_elapsed_time);
	l_Ret.y = misc::fn_Time_Interpolate(0.0f, m_Current_Transformation->m_Duration, m_Previous_Transformation->m_Scale.y, m_Current_Transformation->m_Scale.y, m_elapsed_time);

	return l_Ret;
}

sf::Color SkeletonAnimation::mt_Interpolate_Color(void) const
{
	sf::Color l_Ret;

	l_Ret.r = misc::fn_Time_Interpolate(0.0f, m_Current_Transformation->m_Duration, m_Previous_Transformation->m_Color.r, m_Current_Transformation->m_Color.r, m_elapsed_time);
	l_Ret.g = misc::fn_Time_Interpolate(0.0f, m_Current_Transformation->m_Duration, m_Previous_Transformation->m_Color.g, m_Current_Transformation->m_Color.g, m_elapsed_time);
	l_Ret.b = misc::fn_Time_Interpolate(0.0f, m_Current_Transformation->m_Duration, m_Previous_Transformation->m_Color.b, m_Current_Transformation->m_Color.b, m_elapsed_time);
	l_Ret.a = misc::fn_Time_Interpolate(0.0f, m_Current_Transformation->m_Duration, m_Previous_Transformation->m_Color.a, m_Current_Transformation->m_Color.a, m_elapsed_time);

	return l_Ret;
}

void SkeletonAnimation::mt_Add_Step(const SkeletonTransformation& step)
{
	m_Transformations.push_back(step);
	mt_Reset();
}

bool SkeletonAnimation::mt_New_Cycle(void) const
{
	return m_new_cycle;
}

bool SkeletonAnimation::mt_Is_Playing(void) const
{
	return m_is_playing;
}
