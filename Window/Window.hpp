#ifndef _WINDOW_HPP
#define _WINDOW_HPP 1

#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window(const std::string& title);
	virtual ~Window();

	void mt_Begin_Draw(void);
	void mt_End_Draw(void);

	void mt_Update(void);

	sf::RenderWindow* mt_Get_Renderer_Window(void);
	sf::FloatRect mt_Get_View_Space(void) const;

private:
	sf::RenderWindow m_renderer_window;
};

#endif // _WINDOW_HPP
