#ifndef _EVENT_QUEUE_HPP
#define _EVENT_QUEUE_HPP 1

#include <queue>

template<typename EventType>
class EventQueue
{
public:
	void mt_Add_Event(const EventType& event)
	{
		m_Queue.push(event);
	}

	bool mt_Process(EventType& event)
	{
		bool l_b_ret(false);

		if (m_Queue.empty() == false)
		{
			event = m_Queue.front();
			m_Queue.pop();
			l_b_ret = true;
		}

		return l_b_ret;
	}

	void mt_Clear(void)
	{
		while (m_Queue.empty() == false)
		{
			m_Queue.pop();
		}
	}

private:
	std::queue<EventType> m_Queue;
};

#endif // !_EVENT_QUEUE_HPP