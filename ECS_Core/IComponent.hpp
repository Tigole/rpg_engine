#ifndef _ICOMPONENT_HPP
#define _ICOMPONENT_HPP 1

#include <string>

class TiXmlElement;

using ComponentType = std::string;

class IComponent
{
public:
	IComponent(const ComponentType& type);
	virtual ~IComponent();

	ComponentType getType(void) const;

	virtual void load(const TiXmlElement& element) = 0;

protected:
	ComponentType m_type;
};

#endif // !_ICOMPONENT_HPP