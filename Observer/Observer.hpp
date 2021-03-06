#ifndef _OBSERVER_HPP
#define _OBSERVER_HPP

template<typename MessageType>
class Observer
{
public:
	virtual ~Observer(){}
	virtual void mt_Notify(const MessageType& msg) = 0;
};

#endif // _OBSERVER_HPP
