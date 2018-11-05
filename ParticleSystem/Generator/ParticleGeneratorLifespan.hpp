#ifndef _PARTICLE_GENERATOR_LIFESPAN_HPP
#define _PARTICLE_GENERATOR_LIFESPAN_HPP 1

#include "ParticleGeneratorAreaPosition.hpp"

class ParticleGeneratorLifespan : public ParticleGenerator
{
public:
	virtual void mt_Generate(ParticleEmitter& emitter, ParticleContainer& container, std::size_t from, std::size_t to)
	{
		RandomGenerator l_rand;
		auto& l_Lifespan = container.m_Max_Lifespan;

		for (std::size_t ii = from; ii <= to; ii++)
		{
			l_Lifespan[ii] = l_rand(m_From, m_To);
		}
	}
	float m_From, m_To;
};

#endif // !_PARTICLE_GENERATOR_LIFESPAN_HPP