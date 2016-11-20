#ifndef _IEVENT_HPP
#define _IEVENT_HPP 1

#include <SFML/Window/Event.hpp>

class IEvent
{
public:
	IEvent(const sf::Event& event) : m_sfml_event(event){}
	virtual ~IEvent(){}
	const sf::Event& getSFMLEvent(void) const { return m_sfml_event; }
private:
	sf::Event m_sfml_event;
};

//typedef sf::Event IEvent;

/*class IEvent
{
public:
	virutal ~IEvent(){}
};*/

#endif // !_IEVENT_HPP