#ifndef _EFFECT_HPP
#define _EFFECT_HPP 1

#include "Effect\IEffect.hpp"
#include <string>

class Effect : public IEffect
{
public:
	Effect(const std::string& target_attribute_name);
	virtual ~Effect();

protected:
	std::string m_target_attribute_name;
};
#endif // !_EFFECT_HPP