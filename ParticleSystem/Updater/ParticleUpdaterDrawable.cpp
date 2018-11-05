#include "ParticleUpdaterDrawable.hpp"
#include "ParticleSystem/ParticleContainer.hpp"

void ParticleUpdaterDrawable::mt_Update(float delta_time_s, ParticleContainer& particles)
{
	auto& l_Drawable = particles.m_Drawable;
	auto& l_Position = particles.m_Position;
	auto& l_Size = particles.m_Current_Size;
	auto& l_Color = particles.m_Current_Color;
	auto& l_Rotation = particles.m_Current_Rotation;

	for (std::size_t ii = 0; ii < particles.mt_Get_Alive_Count(); ii++)
	{
		l_Drawable[ii].setOrigin(l_Drawable[ii].getLocalBounds().width / 2, l_Drawable[ii].getLocalBounds().height / 2);
	}

	for (std::size_t ii = 0; ii < particles.mt_Get_Alive_Count(); ii++)
	{
		l_Drawable[ii].setPosition(l_Position[ii].x, l_Position[ii].y);
	}

	for (std::size_t ii = 0; ii < particles.mt_Get_Alive_Count(); ii++)
	{
		l_Drawable[ii].setSize(l_Size[ii]);
	}

	for (std::size_t ii = 0; ii < particles.mt_Get_Alive_Count(); ii++)
	{
		l_Drawable[ii].setFillColor(l_Color[ii]);
	}

	for (std::size_t ii = 0; ii < particles.mt_Get_Alive_Count(); ii++)
	{
		l_Drawable[ii].setRotation(l_Rotation[ii]);
	}
}