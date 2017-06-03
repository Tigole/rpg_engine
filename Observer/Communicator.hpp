#ifndef _COMMUNICATOR_HPP
#define _COMMUNICATOR_HPP 1

#include "Observer/Observer.hpp"

#include <set>

template<typename MessageType>
class Communicator
{
public:
	void addObserver(Observer<MessageType>& observer)
	{
		if (m_observers.find(&observer) == m_observers.end())
			m_observers.emplace(&observer);
	}
	void removeObserver(Observer<MessageType>& observer)
	{
		m_observers.erase(&observer);
	}
	void broadcast(const MessageType& msg)
	{
		for (auto o : m_observers)
			o->notify(msg);
	}
private:
	std::set<Observer<MessageType>*> m_observers;
};

#endif // _COMMUNICATOR_HPP
