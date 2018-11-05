#ifndef _PARTICLE_CONTAINER_HPP
#define _PARTICLE_CONTAINER_HPP 1

#include <array>

#include <SFML/Graphics.hpp>

class TextureManager;

class ParticleContainer
{
public:
	ParticleContainer();
	~ParticleContainer();

	void mt_Resize(std::size_t size);
	void mt_Reset(void);
	void mt_Active(std::size_t index);
	void mt_Deactive(std::size_t index);
	std::size_t mt_Get_Alive_Count(void) const;
	void mt_Set_Texture_Manager(TextureManager* manager);
	TextureManager* mt_Get_Texture_Manager(void);
	bool mt_Is_Full(void) const;
	std::size_t mt_Get_Size(void) const;

	const static std::size_t Max_Particle;

	std::vector<sf::Vector3f> m_Position;
	std::vector<sf::Vector3f> m_Velocity;
	std::vector<sf::Vector2f> m_Start_Size;
	std::vector<sf::Vector2f> m_Current_Size;
	std::vector<sf::Vector2f> m_Final_Size;
	std::vector<sf::Color> m_Start_Color;
	std::vector<sf::Color> m_Current_Color;
	std::vector<sf::Color> m_Final_Color;
	std::vector<std::string> m_Texture;
	std::vector<sf::RectangleShape> m_Drawable;

	std::vector<float> m_Start_Rotation;
	std::vector<float> m_Current_Rotation;
	std::vector<float> m_Final_Rotation;
	std::vector<float> m_Lifespan;
	std::vector<float> m_Max_Lifespan;
	std::vector<bool> m_Alive;

private:
	void mt_Swap(std::size_t ii, std::size_t jj);
	void mt_Reset_Particle(std::size_t index);

	std::size_t m_Alive_Count;
	std::size_t m_Particle_Count;
	TextureManager* m_Texture_Manager;
};

#endif // _PARTICLE_CONTAINER_HPP