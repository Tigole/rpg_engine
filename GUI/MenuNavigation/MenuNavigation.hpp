#ifndef _MENU_NAVIGATION_HPP
#define _MENU_NAVIGATION_HPP 1

#include <vector>

#include "GUI\Actionable\BasicActionable.hpp"
#include "FSM\FSM.hpp"
#include "FSM\FSMTransition.hpp"
#include "MenuNavigationStates.hpp"
#include "GUI\DialogBox.hpp"

class INavigationObject;

class MenuNavigation : public BasicActionable, public fsm::SequentialFSM, public BasicDialogBox
{
public:
	MenuNavigation();

	void onValidate(void);
	void onCancel(void);
	void onLeft(void);
	void onRight(void);
	void onUp(void);
	void onBottom(void);

	void setNavigatioObjects(std::vector<INavigationObject*>& navigation_objects, unsigned int row_number, unsigned int column_number);

protected:
	void manageDrawing(void);

	std::vector<INavigationObject*> m_navigation_objects;
	std::vector<INavigationObject*>::iterator m_target_object;
	unsigned int m_row_number, m_column_number;
	sf::Vector2u m_cell_dimensions;

	fsm::IdleState m_state_idle;
	fsm::EmptyState m_state_done;
	MenuNavigationState_Child m_state_child;
	fsm::TogglableTransition m_trans_on_validate, m_trans_on_cancel, m_trans_child_on_cancel, m_trans_child_on_validate;

};

#endif // !_IMENU_NAVIGATION_HPP