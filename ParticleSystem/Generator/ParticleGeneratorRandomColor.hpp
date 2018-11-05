#ifndef _PARTICLE_GENERATOR_RANDOM_COLOR_HPP
#define _PARTICLE_GENERATOR_RANDOM_COLOR_HPP 1

#include "ParticleGeneratorAreaPosition.hpp"

class ParticleGeneratorRandomColor : public ParticleGenerator
{
public:	
	virtual void mt_Generate(ParticleEmitter& emitter, ParticleContainer& container, std::size_t from, std::size_t to)
	{
		RandomGenerator l_rand;
		auto& l_Current_Color = container.m_Current_Color;
		auto& l_Start_Color = container.m_Start_Color;
		auto& l_Final_Color = container.m_Final_Color;

		for (std::size_t ii = from; ii <= to; ii++)
		{
			l_Current_Color[ii] = sf::Color(static_cast<sf::Uint8>(l_rand(m_From.x, m_To.x)),
											static_cast<sf::Uint8>(l_rand(m_From.y, m_To.y)),
											static_cast<sf::Uint8>(l_rand(m_From.z, m_To.z)));
			l_Start_Color[ii] = l_Current_Color[ii];
			l_Final_Color[ii] = l_Current_Color[ii];
		}
	}

	sf::Vector3i m_From;
	sf::Vector3i m_To;
};

#endif // !_PARTICLE_GENERATOR_RANDOM_COLOR_HPP