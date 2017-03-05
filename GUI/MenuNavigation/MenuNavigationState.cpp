#include "MenuNavigationStates.hpp"
#include "INavigationObject.hpp"
#include "FSM/FSM.hpp"

MenuNavigationState_Child::MenuNavigationState_Child(MenuNavigation& parent, std::vector<INavigationObject*>& navigation_objects, std::vector<INavigationObject*>::iterator& target_object, fsm::TogglableTransition& trans_child_validate, fsm::TogglableTransition& trans_child_cancel)
	:m_parent(parent),
	m_navigation_objects(navigation_objects),
	m_target_object(target_object),
	m_trans_child_validate(trans_child_validate),
	m_trans_child_cancel(trans_child_cancel)
{
	/** Nothing **/
}

bool MenuNavigationState_Child::process(void)
{
	bool l_b_ret(false);
	int child_return;

	if (m_target_object != m_navigation_objects.end())
	{
		l_b_ret = true;
		child_return = (*m_target_object)->callback(&m_parent);
		if (child_return == fsm::SequentialFSM::SEQUENTIAL_STOP_STATE_REACHED)
			m_trans_child_cancel.setFlag();
		else if (child_return == fsm::StatusHandlerFSM::STATUS_FSM_ERROR)
			m_trans_child_cancel.setFlag();
	}

	return l_b_ret;
}
