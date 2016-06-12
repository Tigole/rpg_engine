#ifndef _STATUS_HANDLER_FSM_HPP
#define _STATUS_HANDLER_FSM_HPP 1

#include "FSM/FSM/IFSM.hpp"
#include <map>

namespace fsm
{


/**
	\class StatusHandlerFSM
	\brief Base class defining basics status for fsm
	\note All FMS should be children of this one

	\fn StatusHandlerFSM(const char* status_unknown)
	\brief Constructor of the object
	\details fill the "translation" table to understand returned status

	\fn const char* formatStatus(int status)
	\brief see IFSM::formatStatus
	\details Will return m_str_status_unknown if status is not in the "translation" table

	\enum enum BasicFSM_Status
	\brief Enumeration representing status returned by function process
	\details Children FSM should have their own protected enumerations
	with their first value equal to BASIC_FSM_MAX_STATUS
	and a last value for their own children
	\code{.cpp}
	class SomeFSM : public StatusHandlerFSM
	{
	public:
		...
	protected:
		enum SomeFSM_Status
		{
			SOME_FSM_FIRST_EXTRA_STATUS = STATUS_FSM_STATUS_MAX,
			SOME_FSM_STATUS_MAX
		};
	}
	\endcode

	\var std::map<int, const char*> m_translation_table
	\brief Table to translate returned status into human understandable status
	\details This table is pre-filled in the construction of the object by entering BasicFSM_Status ints

	\var const char* m_str_status_unknown
	\brief Variable used to format an invalid status
**/

class StatusHandlerFSM : public IFSM
{
public:
	enum StatusHandlerFSM_Status
	{
		STATUS_FSM_ERROR,
		STATUS_FSM_RUNNING,

		STATUS_FSM_STATUS_MAX
	};

	StatusHandlerFSM(const char* status_unknown = "UNKNOWN STATUS");
	virtual ~StatusHandlerFSM();

	virtual const char* formatStatus(int status) const;

protected:

	std::map<int, const char*> m_translation_table;
	const char* m_str_status_unknown;
};



}

#endif // _STATUS_HANDLER_FSM_HPP
