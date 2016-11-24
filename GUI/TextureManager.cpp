#include "TextureManager.hpp"
#include "Exception\Exception.hpp"
#include "Miscellaneous.hpp"

#include "GUI.hpp"

TextureManager::TextureManager()
{
	/** Nothing **/
	/** For debuggin purpose **/
	sf::Texture texture;
	texture.loadFromFile("C:/Users/Janniere Sylvain/Documents/GitHub/rpg_engine/Resources/Texture/dlg.png");
	texture.setRepeated(true);

	m_textures["dlg"] = texture;
}
TextureManager::~TextureManager()
{
	/** Nothing **/
}

const sf::Texture& TextureManager::getTexture(const std::string& texture_id) const
{
	std::map<std::string, sf::Texture>::const_iterator it(m_textures.find(texture_id));

	if (it == m_textures.end())
	{
		throw ResourceDoesNotExists(texture_id, FUNCTION_NAME);
	}

	return it->second;
}


std::unique_ptr<IGUIBackground> TextureManager::getBackground(const std::string& background_id) const
{
	std::unique_ptr<IGUIBackground> l_ret;
	auto it(m_background.find(background_id));

	if (it == m_background.end())
	{
		throw ResourceDoesNotExists(background_id, FUNCTION_NAME);
	}

	l_ret = it->second->clone();

	return l_ret;
}