#include "StatusHandlerFSM.hpp"

namespace fsm
{

StatusHandlerFSM::StatusHandlerFSM(const char* status_unknown)
 :	m_translation_table(),
	m_str_status_unknown(status_unknown)
{
	m_translation_table[STATUS_FSM_RUNNING] = "STATUS_FSM_RUNNING";
	m_translation_table[STATUS_FSM_ERROR] = "STATUS_FSM_ERROR";
}

StatusHandlerFSM::~StatusHandlerFSM()
{
	/** Nothing **/
}

const char* StatusHandlerFSM::mt_Format_Status(int status) const
{
	const char* l_pcstr_ret = m_str_status_unknown;
	std::map<int, const char*>::const_iterator it;

	it = m_translation_table.find(status);
	if (it != m_translation_table.end())
		l_pcstr_ret = it->second;

	return l_pcstr_ret;
}

}
