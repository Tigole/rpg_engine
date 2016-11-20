#ifndef _BASIC_ACTIONABLE_HPP
#define _BASIC_ACTIONABLE_HPP 1

#include "IActionable.hpp"

class BasicActionable : public IActionable
{
public:
	BasicActionable();
	virtual ~BasicActionable();

	virtual void manageEvent(const IEvent& event);
	virtual void onValidate(void) = 0;
	virtual void onCancel(void) = 0;
	virtual void onLeft(void) = 0;
	virtual void onRight(void) = 0;
	virtual void onUp(void) = 0;
	virtual void onBottom(void) = 0;

protected:
	//
};

#endif // !_BASIC_ACTIONABLE_HPP