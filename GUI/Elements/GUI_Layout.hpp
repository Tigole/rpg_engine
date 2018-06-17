#ifndef _GUI_LAYOUT_HPP
#define _GUI_LAYOUT_HPP 1

#include "GUI/GUI_Element.hpp"

#include <unordered_set>
#include <memory>
#include <vector>

class GUI_Interface;

class GUI_Layout : public GUI_Element
{
public:
	GUI_Layout(const std::string& id, GUI_Interface* owner);
	virtual void mt_Update(float delta_time_ms);
	virtual void mt_Draw(Window& target);
	void mt_Add_Element(const std::string& element, const sf::FloatRect& rect);
	virtual void mt_Redraw(void);
	virtual void mt_On_Active();
	void mt_Set_Margin(const sf::Vector2f& margin);

protected:
	sf::Vector2f m_margin;
	std::unordered_map<std::string, sf::FloatRect> m_children;
	GUI_Interface* m_interface;
};

#endif // !_GUI_LAYOUT_HPP