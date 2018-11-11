#include "Miscellaneous.hpp"
#include "Logger/ILogger.h"

namespace misc
{

void fn_Center_Origin(sf::Transformable& object, const sf::FloatRect& localbound)
{
	object.setOrigin(localbound.left + localbound.width / 2, localbound.top + localbound.height / 2);
}

}
