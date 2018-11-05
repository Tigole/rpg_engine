#include "ParticleEmitter.hpp"
#include "ParticleSystem.hpp"

ParticleEmitter::ParticleEmitter()
{}

ParticleEmitter::ParticleEmitter(const sf::Vector3f& position, std::size_t max_particle_count)
	:m_Position(position), m_Particle_Count(max_particle_count)
{}

void ParticleEmitter::mt_Set_System(ParticleSystem* system)
{
	m_System = system;
}

void ParticleEmitter::mt_Update(float delta_time_s, ParticleContainer& particles)
{
	GeneratorList* l_generator_list(nullptr);

	l_generator_list = m_System->mt_Get_Generator_List(m_Generator_List);
	m_Accumulated_Time += delta_time_s * m_Emit_Rate;

	if (	(m_Accumulated_Time >= 1.0f)
		&&	(l_generator_list != nullptr))
	{
		std::size_t l_particle_count = static_cast<std::size_t>(m_Accumulated_Time);
		std::size_t l_from, l_to;

		m_Accumulated_Time -= l_particle_count;

		if (m_Particle_Count >= 0)
		{
			if (m_Particle_Count < l_particle_count)
			{
				l_particle_count = m_Particle_Count;
				m_Particle_Count = 0;
			}
			else
			{
				m_Particle_Count -= l_particle_count;
			}
		}

		if (particles.mt_Is_Full() == false)
		{
			l_from = particles.mt_Get_Alive_Count();
			l_to = std::min(l_from + l_particle_count, particles.mt_Get_Size()) - 1;

			for (auto& l_generator : *l_generator_list)
			{
				l_generator->mt_Generate(*this, particles, l_from, l_to);
			}
			for (auto ii = l_from; ii <= l_to; ii++)
			{
				particles.mt_Active(ii);
			}
		}

		if (m_Particle_Count == 0)
		{
			m_System->mt_Remove_Emitter(this);
		}
	}
}

void ParticleEmitter::mt_Set_Position(const sf::Vector3f& position)
{
	m_Position = position;
}

void ParticleEmitter::mt_Set_Emitting_Rate(float emitting_rate_particle_per_s)
{
	m_Emit_Rate = emitting_rate_particle_per_s;
	m_Accumulated_Time = 0.0f;
}

void ParticleEmitter::mt_Set_Particle_Count(std::size_t particle_count)
{
	m_Particle_Count = particle_count;
}

void ParticleEmitter::mt_Set_Generator_List(const std::string& list_id)
{
	m_Generator_List = list_id;
}

std::string ParticleEmitter::mt_Get_Generator_List(void) const
{
	return m_Generator_List;
}

sf::Vector3f ParticleEmitter::mt_Get_Position(void) const
{
	return m_Position;
}