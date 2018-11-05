#ifndef _PARTICLE_GENERATOR_RANGE_COLOR_HPP
#define _PARTICLE_GENERATOR_RANGE_COLOR_HPP 1

#include "ParticleSystem/ParticleGenerator.hpp"
#include <SFML/Graphics.hpp>

#include "ParticleGeneratorAreaPosition.hpp"

class ParticleGeneratorRangeColor : public ParticleGenerator
{
public:
	ParticleGeneratorRangeColor() = default;
	virtual void mt_Generate(ParticleEmitter& emitter, ParticleContainer& container, std::size_t from, std::size_t to)
	{
		RandomGenerator l_rand;
		auto& l_Start_Color = container.m_Start_Color;
		auto& l_Current_Color = container.m_Current_Color;
		auto& l_Final_Color = container.m_Final_Color;

		for (std::size_t ii = from; ii <= to; ii++)
		{
			l_Start_Color[ii] = m_Start_Color;
			l_Current_Color[ii] = m_Start_Color;
			l_Final_Color[ii] = m_Final_Color;
		}
	}

	sf::Color m_Start_Color;
	sf::Color m_Final_Color;
};

#endif // !_PARTICLE_GENERATOR_RANGE_COLOR_HPP