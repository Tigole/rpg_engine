#include "Window/Window.hpp"

#include "Events/EventManager.hpp"
#include "GUI/GUI_Manager.hpp"

Window::Window(EventManager* event_manager, GUI_Manager* gui_manager)
	: m_renderer_window(),
	m_event_manager(event_manager),
	m_gui_manager(gui_manager),
	m_is_done(false)
{
	m_renderer_window.setVisible(false);
}

Window::~Window()
{
	m_renderer_window.close();
}

void Window::mt_Create(const std::string& title, const sf::Vector2u& size)
{
	m_is_done = false;

	m_renderer_window.create(sf::VideoMode(size.x, size.y), title);

	m_event_manager->mt_Add_Callback(GameStateType::Intro, "WINDOW_KEYBOARD_Close", &Window::mt_On_Close, this);

	m_renderer_window.setVisible(true);
}

void Window::mt_On_Close(EventDetails* event_details)
{
	m_is_done = true;
	m_renderer_window.close();
}

void Window::mt_Begin_Draw(void)
{
	m_renderer_window.clear();
}

void Window::mt_End_Draw(void)
{
	m_renderer_window.display();
}

bool Window::mt_Is_Done(void) const
{
	return m_is_done;
}
void Window::mt_Update(void)
{
	EventDataGUI l_gui_event;
	sf::Event l_event;
	while (m_renderer_window.pollEvent(l_event))
	{
		m_event_manager->mt_Handle_Event(l_event);
	}
	
	m_event_manager->mt_Update();

	while (m_gui_manager->mt_Poll_Event(l_gui_event))
	{
		m_event_manager->mt_Handle_Event(l_gui_event);
	}
}

sf::RenderWindow* Window::mt_Get_Renderer_Window(void)
{
	return &m_renderer_window;
}

sf::FloatRect Window::mt_Get_View_Space(void) const
{
	return m_renderer_window.getView().getViewport();
}