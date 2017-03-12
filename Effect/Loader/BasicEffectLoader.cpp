#include "BasicEffectLoader.hpp"

#include "Effect/Effect/BasicEffectBuffer.hpp"
#include "Effect/Effect/BasicEffectModifer.hpp"
#include "Effect/Effect/BasicEffectSetter.hpp"
#include "Exception/Exception.hpp"

#include <tinyxml.h>

BasicEffectSetterLoader::BasicEffectSetterLoader()
	:EffectLoader("BasicEffectSetter")
{
	/** Nothing **/
}

std::unique_ptr<IEffect> BasicEffectSetterLoader::load(const TiXmlElement& element)
{
	std::unique_ptr<IEffect> l_ret(nullptr);
	std::string target_attribute, formula;

	if (element.QueryStringAttribute("target_attribute", &target_attribute) != TIXML_SUCCESS)
		throw ExceptionXMLLoadingAttributeMissing(element, "target_attribute");

	if (element.QueryStringAttribute("formula", &formula) != TIXML_SUCCESS)
		throw ExceptionXMLLoadingAttributeMissing(element, "formula");

	l_ret.reset(new BasicEffectSetter(target_attribute, formula));

	return l_ret;
};

BasicEffectModifierLoader::BasicEffectModifierLoader()
	:EffectLoader("BasicEffectModifier")
{
	/** Nothing **/
}

std::unique_ptr<IEffect> BasicEffectModifierLoader::load(const TiXmlElement& element)
{
	std::unique_ptr<IEffect> l_ret(nullptr);
	std::string target_attribute, formula;

	if (element.QueryStringAttribute("target_attribute", &target_attribute) != TIXML_SUCCESS)
		throw ExceptionXMLLoadingAttributeMissing(element, "target_attribute");

	if (element.QueryStringAttribute("formula", &formula) != TIXML_SUCCESS)
		throw ExceptionXMLLoadingAttributeMissing(element, "formula");

	l_ret.reset(new BasicEffectModifier(target_attribute, formula));

	return l_ret;
}

BasicEffectBufferLoader::BasicEffectBufferLoader()
	:EffectLoader("BasicEffectBuffer")
{
	/** Nothing **/
}

std::unique_ptr<IEffect> BasicEffectBufferLoader::load(const TiXmlElement& element)
{
	std::unique_ptr<IEffect> l_ret(nullptr);
	std::string target_attribute;
	int value, nb_turn;

	if (element.QueryStringAttribute("target_attribute", &target_attribute) != TIXML_SUCCESS)
		throw ExceptionXMLLoadingAttributeMissing(element, "target_attribute");

	if (element.QueryIntAttribute("value", &value) != TIXML_SUCCESS)
		throw ExceptionXMLLoadingAttributeMissing(element, "value");

	if (element.QueryIntAttribute("nb_turn", &nb_turn) != TIXML_SUCCESS)
		throw ExceptionXMLLoadingAttributeMissing(element, "nb_turn");

	l_ret.reset(new BasicEffectBuffer(target_attribute, value, nb_turn));

	return l_ret;
}
