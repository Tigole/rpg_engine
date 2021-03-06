#ifndef _GUI_ELEMENT_HPP
#define _GUI_ELEMENT_HPP 1

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <string>

#include "GUI_Styles.hpp"

class Window;
class Environment;

class GUI_Interface;

struct GUI_Data
{
	sf::Vector2u m_size;

};

enum class GUI_Element_State
{
	Neutral,
	Focused,
	Clicked,
};

std::string fn_GUIElementState_ToString(const GUI_Element_State& state);
GUI_Element_State fn_GUIElementState_ToEnum(const std::string& state);


using StateStyles = std::unordered_map<GUI_Element_State, GUI_Style>;

class GUI_Element
{
public:
	GUI_Element(const std::string& id, GUI_Element* owner);
	virtual ~GUI_Element(){}

	virtual void mt_Update(float detla_time_ms) = 0;
	virtual void mt_Draw(Window& target) = 0;

	void mt_Set_Style(const GUI_Element_State& state, const GUI_Style& style);
	void mt_Set_State(const GUI_Element_State& state);
	GUI_Element_State mt_Get_State(void) const;

	virtual void mt_On_Click(const sf::Vector2f& mousePos);
	virtual void mt_On_Release(const sf::Vector2f& mousePos);
	virtual void mt_On_Hover(const sf::Vector2f& mousePos);
	virtual void mt_On_Leave() {}
	virtual void mt_On_Focus() {}
	virtual void mt_On_Defocus() {}
	virtual void mt_On_Active() { mt_Set_State(GUI_Element_State::Neutral); }
	virtual void mt_On_Deactive() { mt_Set_State(GUI_Element_State::Neutral); }

	bool mt_Is_Inside(const sf::Vector2f& position);

	void mt_Set_Id(const std::string& id);
	const std::string& mt_Get_Id(void) const;

	void mt_Set_Allocation(const sf::FloatRect& rect);
	sf::Vector2f mt_Get_Screen_Position(void) const;
	sf::FloatRect mt_Get_Screen_Space(void) const;

	void mt_Set_Text(const std::string& text);
	virtual void mt_Set_Environment(Environment* env);

	sf::Vector2f mt_Get_Required_Space(void) const;

	virtual void mt_Redraw(void);

protected:

	virtual void mt_Apply_Style(const GUI_Style& style);
	virtual void mt_Apply_Style_Text(const GUI_Style& style);
	virtual void mt_Apply_Style_Background(const GUI_Style& style);

	sf::FloatRect m_allocation;
	std::string m_id;

	StateStyles m_styles;
	GUI_Element_State m_current_state;
	GUI_Element* m_owner;

	GUI_Visual m_visual;
	Environment* m_environment;
};

#endif // !_GUI_ELEMENT_HPP