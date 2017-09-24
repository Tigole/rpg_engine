#ifndef _SPRITE_SHEET_HPP
#define _SPRITE_SHEET_HPP 1

#include <SFML/Graphics.hpp>

class TextureManager;
class Animation;

class SpriteSheet
{
public:
	SpriteSheet(TextureManager* texture_manager);
	~SpriteSheet();

	void mt_Draw(sf::RenderWindow* window);

	void mt_Set_Texture_Rect(const sf::IntRect& rect);
	void mt_Get_Size(int& width, int& height);

	void mt_Set_World_Position(int x, int y);
	void mt_Get_World_Position(int& x, int& y);

	void mt_Update(float delta_time_ms);

	void mt_Set_Animation(const std::string& animation_name, bool play = false, bool loop = false);
	Animation* mt_Get_Current_Animation(void);
	void mt_Load(TextureManager& texture_manager, const std::string& conf_file_name);

private:
	TextureManager* m_texture_manager;

	sf::Sprite m_sprite;
};

#endif // !_SPRITE_SHEET_HPP
