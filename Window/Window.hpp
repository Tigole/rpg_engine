#ifndef _WINDOW_HPP
#define _WINDOW_HPP 1

#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class GUI_Manager;
class EventManager;
class EventDetails;

class Window
{
public:
	Window(EventManager* event_manager, GUI_Manager* gui_manager);
	virtual ~Window();

	void mt_Create(const std::string& title, const sf::Vector2u& size);
	void mt_Begin_Draw(void);
	void mt_End_Draw(void);

	bool mt_Is_Done(void) const;

	void mt_On_Close(EventDetails* event_details);

	void mt_Update(void);

	sf::RenderWindow* mt_Get_Renderer_Window(void);
	sf::FloatRect mt_Get_View_Space(void) const;

private:
	sf::RenderWindow m_renderer_window;

	EventManager* m_event_manager;
	GUI_Manager* m_gui_manager;
	bool m_is_done;
};

#endif // _WINDOW_HPP
