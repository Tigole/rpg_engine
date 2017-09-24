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

	virtual void mt_Get_Value(const std::string& attribute_name, int& value) const;
	virtual void mt_Set_Value(const std::string& attribute_name, int value);
	std::unique_ptr<IAttribute> mt_Clone(void) const;
	void mt_Save(TiXmlElement& parent) const;
	virtual void mt_Dump(ILogger& l);

protected:
	int m_value;
};

#endif // _BASIC_ATTRIBUTE_HPP
