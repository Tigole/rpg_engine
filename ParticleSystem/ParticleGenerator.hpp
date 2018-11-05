#ifndef _PARTICLE_GENERATOR_HPP
#define _PARTICLE_GENERATOR_HPP 1

#include <cstdlib>

#include "ParticleEmitter.hpp"
#include "ParticleContainer.hpp"

class ParticleGenerator
{
public:
	virtual ~ParticleGenerator(){}
	virtual void mt_Generate(ParticleEmitter& emitter, ParticleContainer& container, std::size_t from, std::size_t to) = 0;

};

#endif // !_PARTICLE_GENERATOR_HPP