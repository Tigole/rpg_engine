#ifndef _PARTICLE_UPDATER_LIFESPAN_HPP
#define _PARTICLE_UPDATER_LIFESPAN_HPP 1

#include "ParticleSystem/ParticleUpdater.hpp"

class ParticleUpdaterLifespan : public ParticleUpdater
{
public:
	virtual void mt_Update(float delta_time_s, ParticleContainer& particles)
	{
		auto& l_Life = particles.m_Lifespan;
		auto& l_MLife = particles.m_Max_Lifespan;

		for (std::size_t ii = 0; ii < particles.mt_Get_Alive_Count();)
		{
			l_Life[ii] += delta_time_s;
			if (l_Life[ii] >= l_MLife[ii])
			{
				particles.mt_Deactive(ii);
			}
			else
			{
				ii++;
			}
		}
	}
};

#endif // !_PARTICLE_UPDATER_LIFESPAN_HPP