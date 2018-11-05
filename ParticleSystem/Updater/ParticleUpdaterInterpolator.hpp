#ifndef _PARTICLE_UPDATER_INTERPOLATOR_HPP
#define _PARTICLE_UPDATER_INTERPOLATOR_HPP 1

#include "ParticleSystem/ParticleUpdater.hpp"
#include "Miscellaneous.hpp"

class ParticleUpdaterInterpolator : public ParticleUpdater
{
public:
	virtual void mt_Update(float delta_time_s, ParticleContainer& particles)
	{
		auto& l_Life = particles.m_Lifespan;
		auto& l_MLife = particles.m_Max_Lifespan;
		auto& l_Col = particles.m_Current_Color;
		auto& l_SCol = particles.m_Start_Color;
		auto& l_FCol = particles.m_Final_Color;
		auto& l_Rot = particles.m_Current_Rotation;
		auto& l_SRot = particles.m_Start_Rotation;
		auto& l_FRot = particles.m_Final_Rotation;
		auto& l_Size = particles.m_Current_Size;
		auto& l_SSize = particles.m_Start_Size;
		auto& l_FSize = particles.m_Final_Size;

		for (std::size_t ii = 0; ii < particles.mt_Get_Alive_Count(); ii++)
		{
			if (l_SCol[ii].r != l_FCol[ii].r)
			{
				l_Col[ii].r = misc::fn_Time_Interpolate<sf::Uint8>(0.0f, l_MLife[ii], l_SCol[ii].r, l_FCol[ii].r, l_Life[ii]);
			}
			if (l_SCol[ii].g != l_FCol[ii].g)
			{
				l_Col[ii].g = misc::fn_Time_Interpolate<sf::Uint8>(0.0f, l_MLife[ii], l_SCol[ii].g, l_FCol[ii].g, l_Life[ii]);
			}
			if (l_SCol[ii].b != l_FCol[ii].b)
			{
				l_Col[ii].b = misc::fn_Time_Interpolate<sf::Uint8>(0.0f, l_MLife[ii], l_SCol[ii].b, l_FCol[ii].b, l_Life[ii]);
			}
			if (l_SCol[ii].a != l_FCol[ii].a)
			{
				l_Col[ii].a = misc::fn_Time_Interpolate<sf::Uint8>(0.0f, l_MLife[ii], l_SCol[ii].a, l_FCol[ii].a, l_Life[ii]);
			}
		}

		for (std::size_t ii = 0; ii < particles.mt_Get_Alive_Count(); ii++)
		{
			if (l_SRot[ii] != l_FRot[ii])
			{
				l_Rot[ii] = misc::fn_Time_Interpolate<float>(0.0f, l_MLife[ii], l_SRot[ii], l_FRot[ii], l_Life[ii]);
			}
		}

		for (std::size_t ii = 0; ii < particles.mt_Get_Alive_Count(); ii++)
		{
			if (l_SSize[ii] != l_FSize[ii])
			{
				l_Size[ii].x = misc::fn_Time_Interpolate<float>(0.0f, l_MLife[ii], l_SSize[ii].x, l_FSize[ii].x, l_Life[ii]);
				l_Size[ii].y = misc::fn_Time_Interpolate<float>(0.0f, l_MLife[ii], l_SSize[ii].y, l_FSize[ii].y, l_Life[ii]);
			}
		}
	}
};

#endif // !_PARTICLE_UPDATER_INTERPOLATOR_HPP