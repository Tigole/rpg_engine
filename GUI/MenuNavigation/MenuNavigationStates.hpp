#ifndef _MENU_NAVIGATION_STATES_HPP
#define _MENU_NAVIGATION_STATES_HPP 1

#include "FSM\FSMState.hpp"
#include "FSM\FSMTransition.hpp"

class INavigationObject;
class MenuNavigation;

class MenuNavigationState_Child : public fsm::State
{
public:
	MenuNavigationState_Child(	MenuNavigation& parent, 
								std::vector<INavigationObject*>& navigation_objects, 
								std::vector<INavigationObject*>::iterator& target_object, 
								fsm::TogglableTransition& trans_child_validate, 
								fsm::TogglableTransition& trans_child_cancel);
protected:
	MenuNavigation& m_parent;
	std::vector<INavigationObject*>& m_navigation_objects;
	std::vector<INavigationObject*>::iterator& m_target_object;
	fsm::TogglableTransition& m_trans_child_validate;
	fsm::TogglableTransition& m_trans_child_cancel;
	bool process(void);
};

#endif // !_MENU_NAVIGATION_STATES_HPP