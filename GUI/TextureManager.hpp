#ifndef _TEXTURE_MANAGER_HPP
#define _TEXTURE_MANAGER_HPP 1

#include "Loader/Loader.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

#include "ResourceManager.hpp"

class IGUIBackground;

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
	TextureManager(const std::string& resources_path)
		:ResourceManager<TextureManager, sf::Texture>(resources_path, "/Textures/Texture")
	{}
	~TextureManager()
	{}

	bool mt_Load(sf::Texture* resource, const std::string& file_path)
	{
		return resource->loadFromFile(file_path);
	}
#if 0
	void mt_Load(const std::string& file_path);
	const sf::Texture& mt_Get_Texture(const std::string& texture_id) const;
	std::unique_ptr<IGUIBackground> mt_Get_Background(const std::string& background_id) const;

protected:
	void mt_Load(const TiXmlElement& texture);
	std::string m_resources_path;
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, std::unique_ptr<IGUIBackground>> m_background;
#endif
};

#endif // !_TEXTURE_MANAGER_HPP
