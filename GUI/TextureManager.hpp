#ifndef _TEXTURE_MANAGER_HPP
#define _TEXTURE_MANAGER_HPP 1

#include <SFML\Graphics.hpp>
#include <map>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	sf::Texture& getTexture(const std::string& texture_id);

protected:
	std::map<std::string, sf::Texture> m_textures;
};

#endif // !_TEXTURE_MANAGER_HPP