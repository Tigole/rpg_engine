#include "MenuNavigation.hpp"

MenuNavigation::MenuNavigation(unsigned int row_number, unsigned int column_number)
	: m_navigation_objects(),
	m_target_object(m_navigation_objects.end()),
	m_row_number(row_number),
	m_column_number(column_number),
	m_state_idle(),
	m_state_done(),
	m_state_child(*this, m_navigation_objects, m_target_object, m_trans_child_on_validate, m_trans_child_on_cancel),
	m_trans_on_validate(),
	m_trans_on_cancel(), 
	m_trans_child_on_cancel(), 
	m_trans_child_on_validate()
{
	if ((m_row_number == 0) || (m_column_number == 0))
	{
		//
	}

	addStopState(&m_state_done);
	m_state_idle.m_arr_transitions.push_back(std::make_pair(&m_trans_on_validate, false));
	m_state_idle.m_arr_transitions.push_back(std::make_pair(&m_trans_on_cancel, false));

	m_state_child.m_arr_transitions.push_back(std::make_pair(&m_trans_child_on_validate, false));
	m_state_child.m_arr_transitions.push_back(std::make_pair(&m_trans_child_on_cancel, false));

	m_trans_child_on_cancel.m_target_state = &m_state_idle;
	m_trans_child_on_validate.m_target_state = &m_state_done;
	m_trans_on_validate.m_target_state = &m_state_child;
	m_trans_on_cancel.m_target_state = &m_state_done;
}

void MenuNavigation::onValidate(void)
{
	if (m_target_object != m_navigation_objects.end())
	{
		m_trans_child_on_validate.setFlag();
	}
	else
	{
		/** Nothing **/
	}
}

void MenuNavigation::onCancel(void)
{
	m_trans_on_cancel.setFlag();
}

void MenuNavigation::onLeft(void)
{
	onBottom();
}

void MenuNavigation::onRight(void)
{
	onUp();
}

void MenuNavigation::onUp(void)
{
	if (m_target_object != m_navigation_objects.begin())
		m_target_object--;
}

void MenuNavigation::onBottom(void)
{
	if ((m_target_object + 1) != m_navigation_objects.end())
		m_target_object++;
}

void MenuNavigation::setNavigatioObjects(std::vector<INavigationObject*>& navigation_objects)
{
	m_navigation_objects = navigation_objects;
	m_target_object = m_navigation_objects.end();
}
