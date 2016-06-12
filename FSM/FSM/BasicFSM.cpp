#include "BasicFSM.hpp"
#include "FSM/State/IState.hpp"

namespace fsm
{

BasicFSM::BasicFSM()
 :	StatusHandlerFSM(),
	m_current_state(nullptr)
{
	/** Nothing **/
}

BasicFSM::~BasicFSM()
{
	/** Nothing **/
}

}
