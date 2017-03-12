#include "TextureManager.hpp"
#include "Exception/Exception.hpp"
#include "Miscellaneous.hpp"

#include "GUI.hpp"

/*namespace uut
{
	extern std::string g_resource_path;
}*/

TextureManager::TextureManager(const std::string& resources_path)
	: m_resources_path(resources_path)
{
	/** Nothing **/
	/** For debuggin purpose **/
	/*sf::Texture texture;
	texture.loadFromFile(uut::g_resource_path +  "Graphics/Textures/dlg.png");
	texture.setRepeated(true);

	m_textures["dlg"] = texture;*/
}
TextureManager::~TextureManager()
{
	/** Nothing **/
}

void TextureManager::load(const TiXmlElement& texture)
{
	std::vector<std::string> attributes;
	std::string attrib;
	sf::Texture t;

	attributes.push_back("id");
	attributes.push_back("path");

	for (auto child = texture.FirstChildElement(); (child != nullptr); child = child->NextSiblingElement())
	{
		if (checkAttributes(texture, attributes) == true)
		{
			texture.QueryStringAttribute("path", &attrib);
			t.loadFromFile(m_resources_path + attrib);
			texture.QueryStringAttribute("id", &attrib);

			if (m_textures.find(attrib) != m_textures.end())
				throw ExceptionResourceAlradeyExists(attrib, FUNCTION_NAME);

			m_textures[attrib] = t;
		}
	}
}

const sf::Texture& TextureManager::getTexture(const std::string& texture_id) const
{
	std::map<std::string, sf::Texture>::const_iterator it(m_textures.find(texture_id));

	if (it == m_textures.end())
	{
		throw ExceptionResourceDoesNotExists(texture_id, FUNCTION_NAME);
	}

	return it->second;
}


std::unique_ptr<IGUIBackground> TextureManager::getBackground(const std::string& background_id) const
{
	std::unique_ptr<IGUIBackground> l_ret;
	auto it(m_background.find(background_id));

	if (it == m_background.end())
	{
		throw ExceptionResourceDoesNotExists(background_id, FUNCTION_NAME);
	}

	l_ret = it->second->clone();

	return l_ret;
}
