#include "MenuNavigation.hpp"
#if 0
MenuNavigation::MenuNavigation(/*unsigned int row_number, unsigned int column_number*/)
	: m_navigation_objects(),
	m_target_object(m_navigation_objects.end()),
	m_row_number(0),
	m_column_number(0),
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

	mt_Add_Stop_State(&m_state_done);
	m_state_idle.m_arr_transitions.push_back(std::make_pair(&m_trans_on_validate, false));
	m_state_idle.m_arr_transitions.push_back(std::make_pair(&m_trans_on_cancel, false));

	m_state_child.m_arr_transitions.push_back(std::make_pair(&m_trans_child_on_validate, false));
	m_state_child.m_arr_transitions.push_back(std::make_pair(&m_trans_child_on_cancel, false));

	m_trans_child_on_cancel.m_target_state = &m_state_idle;
	m_trans_child_on_validate.m_target_state = &m_state_done;
	m_trans_on_validate.m_target_state = &m_state_child;
	m_trans_on_cancel.m_target_state = &m_state_done;
}

void MenuNavigation::mt_On_Validate(void)
{
	if (m_target_object != m_navigation_objects.end())
	{
		m_trans_child_on_validate.mt_Set_Flag();
	}
	else
	{
		/** Nothing **/
	}
}

void MenuNavigation::mt_On_Cancel(void)
{
	m_trans_on_cancel.mt_Set_Flag();
}

void MenuNavigation::mt_On_Left(void)
{
	mt_On_Bottom();
}

void MenuNavigation::mt_On_Right(void)
{
	mt_On_Up();
}

void MenuNavigation::mt_On_Up(void)
{
	if (m_target_object != m_navigation_objects.begin())
		m_target_object--;
	mt_Manage_Drawing();
}

void MenuNavigation::mt_On_Bottom(void)
{
	if ((m_target_object + 1) != m_navigation_objects.end())
		m_target_object++;
	mt_Manage_Drawing();
}

void MenuNavigation::mt_Set_Navigation_Objects(std::vector<INavigationObject*>& navigation_objects, unsigned int row_number, unsigned int column_number)
{
	sf::IntRect inside_dimensions(mt_Get_Inside_Dimensions());
	m_navigation_objects = navigation_objects;
	m_target_object = m_navigation_objects.begin();

	m_row_number = row_number;
	m_column_number = column_number;
	m_cell_dimensions.x = inside_dimensions.width / m_column_number;
	m_cell_dimensions.y = inside_dimensions.height / m_row_number;

}

void MenuNavigation::mt_Manage_Drawing(void)
{
	unsigned int nb_navigation_objects_to_show(m_row_number * m_column_number);
	std::vector<INavigationObject*>::iterator it, end_it;

	it = m_target_object;
	end_it = m_target_object + nb_navigation_objects_to_show;


	/*m_target_object->

	for ()*/

	for (; it != end_it; it++)
	{
		//
	}
}
#endif