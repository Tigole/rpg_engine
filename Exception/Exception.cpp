#include "Exception.hpp"

#include <tinyxml.h>

IException::~IException()
{
	/** Nothing **/
}

Exception::Exception(const std::string& str)
	:m_what(str)
{
	/** Nothing **/
}

const char* Exception::what(void) const
{
	return m_what.c_str();
}

XMLLoadingExceptionAttributeMissing::XMLLoadingExceptionAttributeMissing(const TiXmlElement& element, const std::string& attribute_missing_name)
	:Exception("Attribute \"" + attribute_missing_name + "\" is missing in element \"" + element.ValueStr() + "\"")
{
	/** Nothing **/
}

XMLLoadingExceptionElementMissing::XMLLoadingExceptionElementMissing(const TiXmlElement& element, const std::string& element_missing_name)
	: Exception("Element \"" + element_missing_name + "\" is missing in element \"" + element.ValueStr() + "\"")
{
	/** Nothing **/
}

XMLLoadingExceptionElementHasNoChild::XMLLoadingExceptionElementHasNoChild(const TiXmlElement& element)
	: Exception("Element \"" + element.ValueStr() + "\" should have children")
{
	/** Nothing **/
}

XMLLoadingExceptionNoLoader::XMLLoadingExceptionNoLoader(const std::string& id)
	: Exception("No loader found for \"" + id + "\"")
{
	/** Nothing **/
}

AttributeNotFound::AttributeNotFound(const std::string& attribute_name, const std::string& type_name)
	:Exception("Attribute \"" + attribute_name + "\" is not found for type \"" + type_name + "\"")
{
	/** Nothing **/
}

AttributeNotFound::AttributeNotFound(const std::string& attribute_name, const std::string& type_name, const std::string& object_name)
	: Exception("Attribute \"" + attribute_name + "\" is not found for type \"" + type_name + "\" for object \"" + object_name + "\"")
{
	/** Nothing **/
}

AttributeAlreadyExists::AttributeAlreadyExists(const std::string& attribute_name, const std::string& type_name)
	: Exception("Attribute \"" + attribute_name + "\" already exists for type \"" + type_name + "\"")
{
	/** Nothing **/
}

AttributeAlreadyExists::AttributeAlreadyExists(const std::string& attribute_name, const std::string& type_name, const std::string& object_name)
	: Exception("Attribute \"" + attribute_name + "\" already exists for type \"" + type_name + "\" for object \"" + object_name + "\"")
{
	/** Nothing **/
}

ResourceDoesNotExists::ResourceDoesNotExists(const std::string& resource_name, const std::string& context)
	: Exception("Resource \"" + resource_name + "\" does not exists in \"" + context + "\"")
{
	/** Nothing **/
}

ResourceAlradeyExists::ResourceAlradeyExists(const std::string& resource_name, const std::string& context)
	: Exception("Resource \"" + resource_name + "\" already exists in \"" + context + "\"")
{
	/** Nothing **/
}

UnimplementedFunction::UnimplementedFunction(const std::string& function_name)
	: Exception("Function \"" + function_name + "\" is not implemented yet")
{
	/** Nothing **/
}

DLLFunctionNotFound::DLLFunctionNotFound(const std::string& dll_name, const std::string& function_name)
	: Exception("Function \"" + function_name + "\" in library \"" + dll_name + "\" is not found")
{
	/** Nothing **/
}

StringSplittingFail::StringSplittingFail(const std::string& str)
	: Exception("Splitting failed in \"" + str + "\"")
{
	/** Nothing **/
}
