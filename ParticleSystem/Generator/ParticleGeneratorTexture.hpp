#ifndef _PARTICLE_GENERATOR_TEXTURE_HPP
#define _PARTICLE_GENERATOR_TEXTURE_HPP 1

#include "ParticleSystem/ParticleGenerator.hpp"
#include "GUI/TextureManager.hpp"

class ParticleGeneratorTexture : public ParticleGenerator
{
public:
	virtual void mt_Generate(ParticleEmitter& emitter, ParticleContainer& container, std::size_t from, std::size_t to)
	{
		if (m_Texture_Id.empty() == false)
		{
			auto& l_Texture = container.m_Texture;
			auto& l_Drawable = container.m_Drawable;
			auto& l_Size = container.m_Current_Size;
			auto l_Manager = container.mt_Get_Texture_Manager();

			for (std::size_t ii = from; ii <= to; ii++)
			{
				auto l_Resource = l_Manager->mt_Get_Resource(m_Texture_Id);
				l_Texture[ii] = m_Texture_Id;
				l_Drawable[ii].setTexture(l_Resource);
			}
		}
	}

	std::string m_Texture_Id;
};

#endif // !_PARTICLE_GENERATOR_TEXTURE_HPP