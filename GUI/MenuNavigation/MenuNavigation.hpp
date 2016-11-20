#ifndef _MENU_NAVIGATION_HPP
#define _MENU_NAVIGATION_HPP 1

#include <vector>

#include "GUI\Actionable\BasicActionable.hpp"
#include "FSM\FSM.hpp"
#include "FSM\FSMTransition.hpp"
#include "MenuNavigationStates.hpp"

class INavigationObject;

class MenuNavigation : public BasicActionable, public fsm::SequentialFSM
{
public:
	MenuNavigation(unsigned int row_number, unsigned int column_number);

	void onValidate(void);
	void onCancel(void);
	void onLeft(void);
	void onRight(void);
	void onUp(void);
	void onBottom(void);

	void setNavigatioObjects(std::vector<INavigationObject*>& navigation_objects);

protected:
	std::vector<INavigationObject*> m_navigation_objects;
	std::vector<INavigationObject*>::iterator m_target_object;
	unsigned int m_row_number, m_column_number;

	fsm::IdleState m_state_idle;
	fsm::EmptyState m_state_done;
	MenuNavigationState_Child m_state_child;
	fsm::TogglableTransition m_trans_on_validate, m_trans_on_cancel, m_trans_child_on_cancel, m_trans_child_on_validate;

};

#endif // !_IMENU_NAVIGATION_HPP