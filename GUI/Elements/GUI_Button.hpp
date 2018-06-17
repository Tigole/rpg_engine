#ifndef _GUI_BUTTON_HPP
#define _GUI_BUTTON_HPP 1

#include "GUI/GUI_Element.hpp"

class GUI_Button : public GUI_Element
{
public:
	GUI_Button(const std::string& id, GUI_Element* owner);

	virtual void mt_Update(float detla_time_ms);
	virtual void mt_Draw(Window& target);
};

#endif // !_GUI_BUTTON_HPP