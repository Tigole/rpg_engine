#include "BasicActionable.hpp"
#include "GUI\Event\IEvent.hpp"

#include <map>

BasicActionable::BasicActionable()
{
	/** Nothing **/
}
BasicActionable::~BasicActionable()
{
	/** Nothing **/
}

void BasicActionable::manageEvent(const IEvent& event)
{
	typedef std::map<sf::Keyboard::Key, void(BasicActionable::*)(void)> KeyPressedMap;
	typedef std::map<sf::Keyboard::Key, void(BasicActionable::*)(void)>::iterator KeyPressedMapIterator;
	KeyPressedMap key_pressed_map;
	KeyPressedMapIterator key_pressed_map_it;
	const sf::Event& l_event(event.getSFMLEvent());

	key_pressed_map[sf::Keyboard::Left] = &BasicActionable::onLeft;
	key_pressed_map[sf::Keyboard::Right] = &BasicActionable::onRight;
	key_pressed_map[sf::Keyboard::Up] = &BasicActionable::onUp;
	key_pressed_map[sf::Keyboard::Down] = &BasicActionable::onBottom;
	key_pressed_map[sf::Keyboard::Escape] = &BasicActionable::onCancel;
	key_pressed_map[sf::Keyboard::Return] = &BasicActionable::onValidate;

	switch (l_event.type)
	{
	case sf::Event::KeyPressed:
		key_pressed_map_it = key_pressed_map.find(l_event.key.code);
		if (key_pressed_map_it != key_pressed_map.end())
		{
			(this->*(key_pressed_map_it->second))();
		}
		break;
	default:
		break;
	}
}