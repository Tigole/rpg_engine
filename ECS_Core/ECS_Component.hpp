#ifndef _ICOMPONENT_HPP
#define _ICOMPONENT_HPP 1

#include <string>
#include "ECS_Types.hpp"

class TiXmlElement;

class ECS_Component
{
public:
	ECS_Component(const ECS_ComponentId& id) : m_id(id) {}
	virtual ~ECS_Component(){}

	ECS_ComponentId mt_Get_Id(void) const {return m_id;}

	virtual void mt_Load(const TiXmlElement& element) = 0;

protected:
	ECS_ComponentId m_id;
};

#endif // !_ICOMPONENT_HPP
