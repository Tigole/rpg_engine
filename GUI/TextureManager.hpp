#ifndef _TEXTURE_MANAGER_HPP
#define _TEXTURE_MANAGER_HPP 1

#include "Loader/Loader.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

class IGUIBackground;

class TextureManager : public ILoader
{
public:
	TextureManager(const std::string& resources_path);
	~TextureManager();

	void mt_Load(const std::string& file_path);
	const sf::Texture& mt_Get_Texture(const std::string& texture_id) const;
	std::unique_ptr<IGUIBackground> mt_Get_Background(const std::string& background_id) const;

protected:
	void mt_Load(const TiXmlElement& texture);
	std::string m_resources_path;
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, std::unique_ptr<IGUIBackground>> m_background;
};

#endif // !_TEXTURE_MANAGER_HPP
