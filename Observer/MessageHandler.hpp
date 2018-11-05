#ifndef _MESSAGE_HANDLER_HPP
#define _MESSAGE_HANDLER_HPP 1

#include <unordered_map>

#include "Communicator.hpp"

template<typename MessageTypeId, typename MessageType>
class MessageHandler
{
public:
	MessageHandler(){}

	void mt_Add_Observer(const MessageTypeId& msg_id, Observer<MessageType>* observer)
	{
		m_subscriptions[msg_id].mt_Add_Observer(observer);
	}

	void mt_Unsubscribe(const MessageTypeId& msg_id, Observer<MessageType>* observer)
	{
		m_subscriptions[msg_id].mt_Remove_Observer(observer);
	}

	void mt_Dispatch(const MessageType& msg)
	{
		auto l_it = m_subscriptions.find(mt_Get_Type(msg));

		if (l_it != m_subscriptions.end())
		{
			l_it->second.mt_Broadcast(msg);
		}
	}

protected:

	virtual MessageTypeId mt_Get_Type(const MessageType& msg) = 0;

	std::unordered_map<MessageTypeId, Communicator<MessageType>> m_subscriptions;
};

#endif // !_MESSAGE_HANDLER_HPP