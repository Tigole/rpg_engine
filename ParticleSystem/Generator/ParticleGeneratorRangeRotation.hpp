#ifndef _PARTICLE_GENERATOR_RANGE_ROTATION_HPP
#define _PARTICLE_GENERATOR_RANGE_ROTATION_HPP 1

#include "ParticleGeneratorAreaPosition.hpp"

class ParticleGeneratorRangeRotation : public ParticleGenerator
{
public:
	virtual void mt_Generate(ParticleEmitter& emitter, ParticleContainer& container, std::size_t from, std::size_t to)
	{
		auto& l_Start = container.m_Start_Rotation;
		auto& l_End = container.m_Current_Rotation;

		for (std::size_t ii = from; ii <= to; ii++)
		{
			l_Start[ii] = m_From;
			l_End[ii] = m_To;
		}
	}
	float m_From, m_To;
};

#endif // !_PARTICLE_GENERATOR_RANGE_ROTATION_HPP