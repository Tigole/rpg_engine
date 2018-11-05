#ifndef _PARTICLE_GENERATOR_RANDOM_SIZE_HPP
#define _PARTICLE_GENERATOR_RANDOM_SIZE_HPP 1

#include "ParticleGeneratorAreaPosition.hpp"

class ParticleGeneratorRandomSize : public ParticleGenerator
{
public:
	virtual void mt_Generate(ParticleEmitter& emitter, ParticleContainer& container, std::size_t from, std::size_t to)
	{
		RandomGenerator l_rand;
		auto& l_Size = container.m_Current_Size;
		auto& l_SSize = container.m_Start_Size;
		auto& l_FSize = container.m_Final_Size;

		for (std::size_t ii = from; ii <= to; ii++)
		{
			float l_rand_size = l_rand(m_From, m_To);
			l_Size[ii] = sf::Vector2f(l_rand_size, l_rand_size);
			l_SSize[ii] = sf::Vector2f(l_rand_size, l_rand_size);
			l_FSize[ii] = sf::Vector2f(l_rand_size, l_rand_size);
		}
	}
	int m_From, m_To;
};


#endif // !_PARTICLE_GENERATOR_RANDOM_SIZE_HPP