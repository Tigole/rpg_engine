#ifndef _PARTICLE_GENERATOR_RANDOM_VELOCITY_HPP
#define _PARTICLE_GENERATOR_RANDOM_VELOCITY_HPP 1

#include "ParticleGeneratorAreaPosition.hpp"

class ParticleGeneratorRandomVelocity : public ParticleGenerator
{
public:
	virtual void mt_Generate(ParticleEmitter& emitter, ParticleContainer& container, std::size_t from, std::size_t to)
	{
		RandomGenerator l_rand;
		auto& l_Vel = container.m_Velocity;

		for (std::size_t ii = from; ii <= to; ii++)
		{
			l_Vel[ii] = sf::Vector3f(l_rand(m_From.x, m_To.x), l_rand(m_From.y, m_To.y), l_rand(m_From.z, m_To.z));
		}
	}
	sf::Vector3f m_From, m_To;
};

#endif // !_PARTICLE_GENERATOR_RANDOM_VELOCITY_HPP