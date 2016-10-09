#ifndef _BASIC_ATTRIBUTE_HPP
#define _BASIC_ATTRIBUTE_HPP 1

#include "Attribute/Attribute/Attribute.hpp"

extern "C"
{
	void deleteBasicAttribute(IAttribute* obj);
}

class BasicAttribute : public Attribute
{
public:
	BasicAttribute(const std::string& name, int value);
	BasicAttribute(const std::string& name);

	virtual void getValue(const std::string& attribute_name, int& value) const;
	virtual void setValue(const std::string& attribute_name, int value);
	std::unique_ptr<IAttribute> clone(void) const;
	void save(TiXmlElement& parent) const;
	virtual void dump(ILogger& l);

protected:
	int m_value;
};

#endif // _BASIC_ATTRIBUTE_HPP
