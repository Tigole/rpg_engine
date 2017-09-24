#ifndef _COMPOSITE_ATTRIBUTE_HPP
#define _COMPOSITE_ATTRIBUTE_HPP 1

#include "Attribute.hpp"

#include <map>
#include <memory>

extern "C"
{
	void fn_delete_CompositeAttribute(IAttribute* obj);
}

class CompositeAttribute : public Attribute
{
public:
	CompositeAttribute(const std::string& base_name);
	CompositeAttribute(const CompositeAttribute& cp);

	void mt_Add_Attributes(std::unique_ptr<IAttribute>& lower_attribute);
	virtual void mt_Get_Value(const std::string& attribute_name, int& value) const;
	virtual void mt_Set_Value(const std::string& attribute_name, int value);
	std::unique_ptr<IAttribute> mt_Clone(void) const;
	void mt_Save(TiXmlElement& parent) const;
	virtual void mt_Dump(ILogger& l);

private:
	void mt_Split_Attribute_Name(const std::string& full_name, std::string& base_name, std::string& lower_name) const;
	std::map<std::string, std::unique_ptr<IAttribute>> m_attributes;

	/** \fn bool splitAttributeName(const std::string& full_name, std::string& base_name, std::string& lower_name) const
		\brief Split "full_name" into "base_name" and "lower_name"
		\return true on success
		Example:
			full_name = "hp.max"
			base_name = "hp"
			lower_name = "max"
	**/
};

#endif // !_COMPOSITE_ATTRIBUTE_HPP
