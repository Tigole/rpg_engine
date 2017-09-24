#include "BasicActionable.hpp"
#include "GUI/Event/IEvent.hpp"

#include <map>

BasicActionable::BasicActionable()
{
	/** Nothing **/
}
BasicActionable::~BasicActionable()
{
	/** Nothing **/
}

void BasicActionable::mt_Manage_Event(const IEvent& event)
{
	typedef std::map<sf::Keyboard::Key, void(BasicActionable::*)(void)> KeyPressedMap;
	typedef std::map<sf::Keyboard::Key, void(BasicActionable::*)(void)>::iterator KeyPressedMapIterator;
	KeyPressedMap key_pressed_map;
	KeyPressedMapIterator key_pressed_map_it;
	const sf::Event& l_event(event.mt_Get_SFML_Event());

	key_pressed_map[sf::Keyboard::Left] = &BasicActionable::mt_On_Left;
	key_pressed_map[sf::Keyboard::Right] = &BasicActionable::mt_On_Right;
	key_pressed_map[sf::Keyboard::Up] = &BasicActionable::mt_On_Up;
	key_pressed_map[sf::Keyboard::Down] = &BasicActionable::mt_On_Bottom;
	key_pressed_map[sf::Keyboard::Escape] = &BasicActionable::mt_On_Cancel;
	key_pressed_map[sf::Keyboard::Return] = &BasicActionable::mt_On_Validate;

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
