#include "ParticleContainer.hpp"
#include "GUI/TextureManager.hpp"


const std::size_t ParticleContainer::Max_Particle = 10000;

ParticleContainer::ParticleContainer()
	: m_Alive_Count(0), m_Particle_Count(Max_Particle),
	m_Position(Max_Particle),
	m_Velocity(Max_Particle),
	m_Start_Size(Max_Particle),
	m_Current_Size(Max_Particle),
	m_Final_Size(Max_Particle),
	m_Start_Color(Max_Particle),
	m_Current_Color(Max_Particle),
	m_Final_Color(Max_Particle),
	m_Texture(Max_Particle),
	m_Drawable(Max_Particle),
	m_Start_Rotation(Max_Particle),
	m_Current_Rotation(Max_Particle),
	m_Final_Rotation(Max_Particle),
	m_Lifespan(Max_Particle),
	m_Max_Lifespan(Max_Particle),
	m_Alive(Max_Particle)
{
	mt_Reset();
}

ParticleContainer::~ParticleContainer()
{
	mt_Reset();
}

void ParticleContainer::mt_Resize(std::size_t size)
{
	if (size >= Max_Particle)
	{
		m_Particle_Count = Max_Particle;
		mt_Reset();
	}
	else if (size >= 0)
	{
		m_Particle_Count = size;
		mt_Reset();
	}
}

std::size_t ParticleContainer::mt_Get_Size(void) const
{
	return m_Particle_Count;
}

void ParticleContainer::mt_Reset(void)
{
	for (std::size_t ii = 0; ii < m_Particle_Count; ii++)
	{
		mt_Reset_Particle(ii);
	}
	m_Alive_Count = 0;
}

void ParticleContainer::mt_Active(std::size_t index)
{
	if (	(index < m_Particle_Count)
		&&	(m_Alive[index] == false))
	{
		m_Alive[index] = true;
		mt_Swap(index, m_Alive_Count);
		m_Alive_Count++;
	}
}

void ParticleContainer::mt_Deactive(std::size_t index)
{
	if ((index < m_Particle_Count)
		&& (m_Alive[index] == true)
		&&	(m_Alive_Count != 0))
	{
		mt_Reset_Particle(index);
		m_Alive_Count--;
		mt_Swap(index, m_Alive_Count);
	}
}

std::size_t ParticleContainer::mt_Get_Alive_Count(void) const
{
	return m_Alive_Count;
}

void ParticleContainer::mt_Swap(std::size_t ii, std::size_t jj)
{
	if ((ii < m_Particle_Count) && (jj < m_Particle_Count) && (ii != jj))
	{
		std::swap(m_Position[ii], m_Position[jj]);
		std::swap(m_Velocity[ii], m_Velocity[jj]);
		std::swap(m_Start_Size[ii], m_Start_Size[jj]);
		std::swap(m_Current_Size[ii], m_Current_Size[jj]);
		std::swap(m_Final_Size[ii], m_Final_Size[jj]);
		std::swap(m_Start_Color[ii], m_Start_Color[jj]);
		std::swap(m_Current_Color[ii], m_Current_Color[jj]);
		std::swap(m_Final_Color[ii], m_Final_Color[jj]);
		std::swap(m_Texture[ii], m_Texture[jj]);
		std::swap(m_Drawable[ii], m_Drawable[jj]);
		std::swap(m_Start_Rotation[ii], m_Start_Rotation[jj]);
		std::swap(m_Current_Rotation[ii], m_Current_Rotation[jj]);
		std::swap(m_Final_Rotation[ii], m_Final_Rotation[jj]);
		std::swap(m_Lifespan[ii], m_Lifespan[jj]);
		std::swap(m_Max_Lifespan[ii], m_Max_Lifespan[jj]);
		std::swap(m_Alive[ii], m_Alive[jj]); 
	}
}

void ParticleContainer::mt_Reset_Particle(std::size_t index)
{
	if (index < m_Particle_Count)
	{
		m_Position[index] = { 0.0f, 0.0f, 0.0f };
		m_Velocity[index] = { 0.0f, 0.0f, 0.0f };
		m_Start_Size[index] = { 0.0f, 0.0f };
		m_Current_Size[index] = { 0.0f, 0.0f };
		m_Final_Size[index] = { 0.0f, 0.0f };
		m_Start_Color[index] = sf::Color::Transparent;
		m_Current_Color[index] = sf::Color::Transparent;
		m_Final_Color[index] = sf::Color::Transparent;
		m_Drawable[index].setTexture(nullptr);
		if (m_Texture[index].empty() == false)
		{
			m_Texture_Manager->mt_Release_Resource(m_Texture[index]);
			m_Texture[index] = "";
		}
		m_Start_Rotation[index] = 0.0f;
		m_Current_Rotation[index] = 0.0f;
		m_Final_Rotation[index] = 0.0f;
		m_Lifespan[index] = 0.0f;
		m_Max_Lifespan[index] = 0.0f;
		m_Alive[index] = false; 
	}
}

void ParticleContainer::mt_Set_Texture_Manager(TextureManager* manager)
{
	m_Texture_Manager = manager;
}

TextureManager* ParticleContainer::mt_Get_Texture_Manager(void)
{
	return m_Texture_Manager;
}

bool ParticleContainer::mt_Is_Full(void) const
{
	return (m_Alive_Count >= m_Particle_Count);
}