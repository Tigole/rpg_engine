#ifndef _COMPOSITE_ATTRIBUTE_HPP
#define _COMPOSITE_ATTRIBUTE_HPP 1

#include "Attribute.hpp"

#include <map>
#include <memory>

extern "C"
{
	void deleteCompositeAttribute(IAttribute* obj);
}

class CompositeAttribute : public Attribute
{
public:
	CompositeAttribute(const std::string& base_name);
	CompositeAttribute(const CompositeAttribute& cp);

	bool addAttributes(std::unique_ptr<IAttribute>& lower_attribute);
	virtual bool getValue(const std::string& attribute_name, int& value) const;
	virtual bool setValue(const std::string& attribute_name, int value);
	std::unique_ptr<IAttribute> clone(void) const;
	bool save(TiXmlElement& parent) const;
	virtual void dump(ILogger& l);

private:
	bool splitAttributeName(const std::string& full_name, std::string& base_name, std::string& lower_name) const;
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
