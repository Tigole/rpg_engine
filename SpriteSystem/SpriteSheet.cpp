#include "SpriteSheet.hpp"
#include "XMLFileLoader.hpp"
#include "GUI/TextureManager.hpp"

SpriteSheet::SpriteSheet(TextureManager* texture_manager)
	:m_texture_manager(texture_manager)
{}

SpriteSheet::~SpriteSheet()
{}

void SpriteSheet::mt_Draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

void SpriteSheet::mt_Set_Texture_Rect(const sf::IntRect& rect)
{
	m_sprite.setTextureRect(rect);
}

void SpriteSheet::mt_Set_World_Position(int x, int y)
{
	m_sprite.setPosition(x, y);
}

void SpriteSheet::mt_Get_World_Position(int& x, int& y)
{
	sf::Vector2f l_Position;

	l_Position = m_sprite.getPosition();
	x = l_Position.x;
	y = l_Position.y;
}

void SpriteSheet::mt_Get_Size(int& width, int& height)
{
	sf::IntRect l_Texture_Rect;

	l_Texture_Rect = m_sprite.getTextureRect();
	width = l_Texture_Rect.width;
	height = l_Texture_Rect.height;
}

void SpriteSheet::mt_Set_Animation(const std::string& animation_name, bool play, bool loop)
{
	//
}

Animation* SpriteSheet::mt_Get_Current_Animation(void)
{
	return nullptr;
}

void SpriteSheet::mt_Update(float delta_time_ms)
{
	//
}

void SpriteSheet::mt_Load(TextureManager& texture_manager, const std::string& conf_file_name)
{
	XMLFileLoader l_loader;

	l_loader.mt_Set_File(conf_file_name);
	/** TODO read the file and so on **/
	m_sprite.setTexture(texture_manager.mt_Get_Texture(conf_file_name) , true);
	m_sprite.setPosition(0.0f, 0.0f);
	//l_loader.addCallback()
	//l_loader.addCallback
}
