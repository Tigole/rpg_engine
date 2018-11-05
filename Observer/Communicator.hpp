#ifndef _COMMUNICATOR_HPP
#define _COMMUNICATOR_HPP 1

#include "Observer/Observer.hpp"

#include <set>

template<typename MessageType>
class Communicator
{
public:
	void mt_Add_Observer(Observer<MessageType>* observer)
	{
		if (m_observers.find(observer) == m_observers.end())
			m_observers.emplace(observer);
	}
	void mt_Remove_Observer(Observer<MessageType>* observer)
	{
		m_observers.erase(observer);
	}
	void mt_Broadcast(const MessageType& msg)
	{
		for (auto o : m_observers)
			o->mt_Notify(msg);
	}
private:
	std::set<Observer<MessageType>*> m_observers;
};

#endif // _COMMUNICATOR_HPP
