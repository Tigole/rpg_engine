#ifndef _BASIC_ACTIONABLE_HPP
#define _BASIC_ACTIONABLE_HPP 1

#include "IActionable.hpp"

class BasicActionable : public IActionable
{
public:
	BasicActionable();
	virtual ~BasicActionable();

	virtual void mt_Manage_Event(const IEvent& event);
	virtual void mt_On_Validate(void) = 0;
	virtual void mt_On_Cancel(void) = 0;
	virtual void mt_On_Left(void) = 0;
	virtual void mt_On_Right(void) = 0;
	virtual void mt_On_Up(void) = 0;
	virtual void mt_On_Bottom(void) = 0;

protected:
	//
};

#endif // !_BASIC_ACTIONABLE_HPP
