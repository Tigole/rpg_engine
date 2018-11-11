#ifndef _PARTICLE_GENERATOR_POINT_POSITION_HPP
#define _PARTICLE_GENERATOR_POINT_POSITION_HPP 1

#include "ParticleSystem/ParticleGenerator.hpp"

class ParticleGeneratorPointPosition : public ParticleGenerator
{
public:
	virtual void mt_Generate(ParticleEmitter& emitter, ParticleContainer& container, std::size_t from, std::size_t to)
	{
		auto& l_Position = container.m_Position;
		for (std::size_t ii = from; ii <= to; ii++)
		{
			l_Position[ii] = emitter.mt_Get_Position();
		}
	}
};

#endif // !_PARTICLE_GENERATOR_POINT_POSITION_HPP