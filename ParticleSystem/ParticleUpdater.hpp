#ifndef _PARTICLE_UPDATER_HPP
#define _PARTICLE_UPDATER_HPP 1

#include "ParticleContainer.hpp"

class ParticleUpdater
{
public:
	virtual ~ParticleUpdater(){}
	virtual void mt_Update(float delta_time_s, ParticleContainer& particles) = 0;
};

#endif // !_PARTICLE_UPDATER_HPP