#ifndef _OBSERVER_HPP
#define _OBSERVER_HPP

template<typename MessageType>
class Observer
{
public:
	virtual ~Observer(){}
	virtual void notify(const MessageType& msg) = 0;
};

#endif // _OBSERVER_HPP
