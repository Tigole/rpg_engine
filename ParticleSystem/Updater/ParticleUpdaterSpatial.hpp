#ifndef _PARTICLE_UPDATER_SPATIAL_HPP
#define _PARTICLE_UPDATER_SPATIAL_HPP 1

#include "ParticleSystem/ParticleUpdater.hpp"

class ParticleUpdaterSpatial : public ParticleUpdater
{
public:
	virtual void mt_Update(float delta_time_s, ParticleContainer& particles)
	{
		auto& l_Vel = particles.m_Velocity;
		auto& l_Pos = particles.m_Position;

		for (std::size_t ii = 0; ii < particles.mt_Get_Alive_Count(); ii++)
		{
			l_Pos[ii] += l_Vel[ii] * delta_time_s;
		}
	}
};

#endif // !_PARTICLE_UPDATER_SPATIAL_HPP