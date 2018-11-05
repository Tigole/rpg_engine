#ifndef _PARTICLE_GENERATOR_RANGE_SIZE_HPP
#define _PARTICLE_GENERATOR_RANGE_SIZE_HPP 1

#include "ParticleGeneratorAreaPosition.hpp"

class ParticleGeneratorRangeSize : public ParticleGenerator
{
public:
	virtual void mt_Generate(ParticleEmitter& emitter, ParticleContainer& container, std::size_t from, std::size_t to)
	{
		auto& l_Current = container.m_Current_Size;
		auto& l_Start = container.m_Start_Size;
		auto& l_End = container.m_Final_Size;

		for (std::size_t ii = from; ii <= to; ii++)
		{
			l_Start[ii] = sf::Vector2f(m_From, m_From);
			l_Current[ii] = l_Start[ii];
			l_End[ii] = sf::Vector2f(m_To, m_To);
		}
	}
	float m_From, m_To;
};

#endif // !_PARTICLE_GENERATOR_RANGE_SIZE_HPP