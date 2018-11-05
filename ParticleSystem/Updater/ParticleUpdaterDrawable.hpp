#ifndef _PARTICLE_UPDATER_DRAWABLE_HPP
#define _PARTICLE_UPDATER_DRAWABLE_HPP 1

#include "ParticleSystem/ParticleUpdater.hpp"

class ParticleUpdaterDrawable : public ParticleUpdater
{
public:
	//
	virtual void mt_Update(float delta_time_s, ParticleContainer& particles);
};

#endif // !_PARTICLE_UPDATER_DRAWABLE_HPP