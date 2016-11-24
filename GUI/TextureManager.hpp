#ifndef _TEXTURE_MANAGER_HPP
#define _TEXTURE_MANAGER_HPP 1

#include <SFML\Graphics.hpp>
#include <map>
#include <memory>

class IGUIBackground;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	const sf::Texture& getTexture(const std::string& texture_id) const;
	std::unique_ptr<IGUIBackground> getBackground(const std::string& background_id) const;

protected:
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, std::unique_ptr<IGUIBackground>> m_background;
};

#endif // !_TEXTURE_MANAGER_HPP