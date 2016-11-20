#include "TextureManager.hpp"
#include "Exception\Exception.hpp"
#include "Miscellaneous.hpp"

TextureManager::TextureManager()
{
	/** Nothing **/
	/** For debuggin purpose **/
	sf::Texture texture;
	texture.loadFromFile("C:/Users/Janniere Sylvain/Documents/GitHub/rpg_engine/Resources/Texture/dlg.png"/*, sf::IntRect(0, 0, 33/3, 33/3)*/);
	texture.setRepeated(true);

	m_textures["dlg"] = texture;
}
TextureManager::~TextureManager()
{
	/** Nothing **/
}

sf::Texture& TextureManager::getTexture(const std::string& texture_id)
{
	std::map<std::string, sf::Texture>::iterator it(m_textures.find(texture_id));

	if (it == m_textures.end())
	{
		throw ResourceDoesNotExists(texture_id, FUNCTION_NAME);
	}

	return it->second;
}