#ifndef _STATES_H
#define _STATES_H 1

#include "FSM/State/IState.hpp"
#include "FSM/Transition/ITransition.hpp"

#include <vector>

namespace fsm
{
	/**
		\class State
		\brief Class managing transitions

		\fn virtual IState* callProcess(void)
		\brief Manage the action of the state and transitions to change current state of a FSM
		\details Transitions must be sorted by priority (highest priority in the lowest index)

		\fn bool process(void)
		\brief Method used to really process actions of the state
		\return false on error, true otherwise

		\var std::vector<std::pair<ITransition*, bool>> m_arr_transitions
		\brief Array of transitions
		\details
				- Freeing memory is provided when destructor is called for elements which has their flag set to true
				- Transitions must be sorted by priority (highest priority in the lowest index)
	**/

	class State : public IState
	{
	public:
		State();
		virtual ~State();
		IState* callProcess(void);
		std::vector<std::pair<ITransition*, bool>> m_arr_transitions;
	protected:
		virtual bool process(void) = 0;

	};

	/** 
		\class EntryExitState
		\brief Class managing OnEntry and OnExit call when entering and leaving the state

		\fn virtual IState* callProcess(void)
		\brief Manage OnEntry and OnExit method call when entering and leaving the state
		\details Transitions must be sorted by priority (highest priority in the lowest index)

		\fn bool reset(void)
		\brief Method used to reset the state machine in its initial state. Must be called by children objects if redefined
		\return true if reset succeeded, false otherwise

		\fn bool onEntry(void)
		\brief Update internal flag to stop calling onEntry. Must be called by children objects if redefined
		\return true

		\fn bool process(void)
		\brief Method used to really process actions of the state
		\return false on error, true otherwise

		\fn bool onExit(void)
		\brief Update internal flag to call onEntry. Must be called by children objects if redefined
		\return true

		\var bool m_b_on_entry_must_be_done
		\brief Flag to know wheather onEntry method should be called
	**/

	class EntryExitState : public State
	{
	public:
		EntryExitState();
		virtual ~EntryExitState();
		IState* callProcess(void);
		bool reset(void);

	protected:
		virtual bool onEntry(void);
		virtual bool onExit(void);
		bool m_b_on_entry_must_be_done;
	};

}

#endif // _STATES_H
