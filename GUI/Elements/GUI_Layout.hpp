#ifndef _GUI_LAYOUT_HPP
#define _GUI_LAYOUT_HPP 1

#include "GUI/GUI_Element.hpp"

class GUI_Layout : public GUI_Element
{
public:
	void mt_Update(float detla_time_ms);
	void mt_Draw(Window& target);
};

#endif // !_GUI_LAYOUT_HPP