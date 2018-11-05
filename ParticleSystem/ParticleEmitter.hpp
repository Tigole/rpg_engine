#ifndef _PARTICLE_EMITTER_HPP
#define _PARTICLE_EMITTER_HPP 1

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>

class ParticleContainer;
class ParticleSystem;

class ParticleEmitter
{
public:
	ParticleEmitter();
	ParticleEmitter(const sf::Vector3f& position, std::size_t particle_count);

	void mt_Set_System(ParticleSystem* system);
	void mt_Update(float delta_time_s, ParticleContainer& particles);
	void mt_Set_Position(const sf::Vector3f& position);
	void mt_Set_Emitting_Rate(float emitting_rate_particle_per_s);
	void mt_Set_Particle_Count(std::size_t particle_count);
	void mt_Set_Generator_List(const std::string& list_id);
	std::string mt_Get_Generator_List(void) const;
	sf::Vector3f mt_Get_Position(void) const;

private:
	ParticleSystem* m_System;
	sf::Vector3f m_Position;
	std::size_t m_Particle_Count;
	float m_Emit_Rate;
	float m_Accumulated_Time;
	std::string m_Generator_List;
};

#endif // _PARTICLE_EMITTER_HPP