#include "GUI_Layout.hpp"
#include "GUI/GUI_Interface.hpp"

GUI_Layout::GUI_Layout(const std::string& id, GUI_Interface* owner)
	:GUI_Element(id, owner),
	m_interface(owner)
{}

void GUI_Layout::mt_Update(float delta_time_ms)
{
	//
}

void GUI_Layout::mt_Draw(Window& target)
{
	//
}

void GUI_Layout::mt_On_Active()
{
	mt_Set_State(GUI_Element_State::Neutral);
}

void GUI_Layout::mt_Add_Element(const std::string& element, const sf::FloatRect& rect)
{
	m_children.emplace(element, rect);
}

void GUI_Layout::mt_Redraw(void)
{
	sf::Vector2f l_required_space(0.0f, 0.0f), l_tmp;
	sf::FloatRect l_allocation;
	std::unordered_map<GUI_Element*, sf::FloatRect> l_children;

	for (auto& el : m_children)
	{
		l_children.emplace(m_interface->mt_Get_Element(el.first), el.second);
	}

	for (auto& el : l_children)
	{
		l_tmp = el.first->mt_Get_Required_Space();

		l_required_space.x = std::max(l_tmp.x, l_required_space.x);
		l_required_space.y = std::max(l_tmp.y, l_required_space.y);
	}

	for (auto& el : l_children)
	{

		l_allocation.width = l_required_space.x * el.second.width;
		if (el.second.width > 1)
			l_allocation.width += m_margin.x;
		l_allocation.height = l_required_space.y * el.second.height;
		if (el.second.height > 1)
			l_allocation.height += m_margin.y;

		l_allocation.left = m_allocation.left + (l_required_space.x + m_margin.x) * el.second.left;
		l_allocation.top = m_allocation.top + (l_required_space.y + m_margin.y) * el.second.top;
		/*if (el.second.top != 0)
			l_allocation.top += m_margin.y;*/


		el.first->mt_Set_Allocation(l_allocation);
	}

	for (auto& el : l_children)
	{
		el.first->mt_Redraw();
	}
}

void GUI_Layout::mt_Set_Margin(const sf::Vector2f& margin)
{
	m_margin = margin;
}