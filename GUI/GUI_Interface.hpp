#ifndef _GUI_INTERFACE_HPP
#define _GUI_INTERFACE_HPP 1

#include <unordered_map>
#include <string>
#include <memory>

#include "GUI_Element.hpp"

class Window;
struct EventDetails;
class GUI_Manager;

using GUI_Element_Container = std::unordered_map<std::string, std::unique_ptr<GUI_Element>>;

class GUI_Interface : public GUI_Element
{
public:
	GUI_Interface(const std::string& id, GUI_Manager* manager);

	void mt_Add_Element(GUI_Element* element);

	bool mt_Is_Active(void) const;
	bool mt_Has_Focus(void) const;

	virtual void mt_On_Click(const sf::Vector2f& mousePos);
	virtual void mt_On_Release(const sf::Vector2f& mousePos);
	virtual void mt_On_Hover(const sf::Vector2f& mousePos);
	virtual void mt_On_Leave();
	virtual void mt_On_Focus();
	virtual void mt_On_Defocus();

	void mt_Update(float detla_time_ms);
	void mt_Draw(Window& target);
	virtual void mt_Set_Environment(Environment* env);

	/*void mt_On_MouseMove(EventDetails* details);
	void mt_On_Click(EventDetails* details);
	void mt_On_Release(EventDetails* details);*/

protected:
	GUI_Manager* m_manager;
	GUI_Element_Container m_elements;
	bool m_is_active;
	bool m_has_focus;
};

#endif // !_GUI_INTERFACE_HPP