#include "Window/Window.hpp"

Window::Window(const std::string& title)
{
	//
}

Window::~Window()
{
	//
}

void Window::mt_Begin_Draw(void)
{
	//
}

void Window::mt_End_Draw(void)
{
	//
}

void Window::mt_Update(void)
{
	//
}

sf::RenderWindow* Window::mt_Get_Renderer_Window(void)
{
	return &m_renderer_window;
}

sf::FloatRect Window::mt_Get_View_Space(void) const
{
	return m_renderer_window.getView().getViewport();
}