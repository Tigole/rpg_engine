#ifndef _FONT_MANAGER_HPP
#define _FONT_MANAGER_HPP 1

#include <SFML/Graphics/Font.hpp>

#include "ResourceManager.hpp"

class FontManager : public ResourceManager<FontManager, sf::Font>
{
public:
	FontManager(const std::string& resources_path)
		:ResourceManager<FontManager, sf::Font>(resources_path, "/Fonts/Font")
	{}

	bool mt_Load(sf::Font* resource, const std::string& file_path)
	{
		return resource->loadFromFile(file_path);
	}
};

#endif // !_FONT_MANAGER_HPP