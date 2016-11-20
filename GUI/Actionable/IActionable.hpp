#ifndef _IACTIONABLE_HPP
#define _IACTIONABLE_HPP 1

class IEvent;

class IActionable
{
public:
	virtual ~IActionable(){}

	virtual void manageEvent(const IEvent& event) = 0;

};

#endif // !_IACTIONABLE_HPP