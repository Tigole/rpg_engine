#ifndef _PARTICLE_GENERATOR_AREA_POSITION_HPP
#define _PARTICLE_GENERATOR_AREA_POSITION_HPP 1

#include "ParticleSystem/ParticleGenerator.hpp"
#include <SFML/Graphics.hpp>
#include "ParticleSystem/ParticleEmitter.hpp"

#include <cstdlib>
class RandomGenerator
{
public:
	int mt_Generate(void)
	{
		return std::rand();
	}
	int mt_Generate(int max)
	{
		if (max == 0)
			max = 1;
		return std::rand() % max;
	}
	int mt_Generate(int min, int max)
	{
		return min + mt_Generate(max - min);
	}
	int operator()()
	{
		return mt_Generate();
	}
	int operator()(int max)
	{
		return mt_Generate(max);
	}
	int operator()(int min, int max)
	{
		return mt_Generate(min, max);
	}
};

class ParticleGeneratorAreaPosition : public ParticleGenerator
{
public:
	ParticleGeneratorAreaPosition() : m_Deviation(0.0f, 0.0f, 0.0f){}
	virtual void mt_Generate(ParticleEmitter& emitter, ParticleContainer& container, std::size_t from, std::size_t to)
	{
		RandomGenerator l_rand;
		auto& l_Position = container.m_Position;
		auto l_center = emitter.mt_Get_Position();
		auto l_From = l_center - m_Deviation;
		auto l_To = l_center + m_Deviation;

		for (std::size_t ii = from; ii <= to; ii++)
		{
			l_Position[ii] = sf::Vector3f(l_rand(l_From.x, l_To.x), l_rand(l_From.y, l_To.y), l_rand(l_From.z, l_To.z));
		}
	}

	sf::Vector3f m_Deviation;
};

#endif // !_PARTICLE_GENERATOR_AREA_POSITION_HPP