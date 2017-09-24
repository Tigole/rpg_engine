#include "Exception.hpp"
#include "Miscellaneous.hpp"

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

const char* Exception::mt_What(void) const
{
	return m_what.c_str();
}

ExceptionXMLLoadingAttributeMissing::ExceptionXMLLoadingAttributeMissing(const TiXmlElement& element, const std::string& attribute_missing_name)
	:Exception("Attribute \"" + attribute_missing_name + "\" is missing in element \"" + element.ValueStr() + "\"")
{
	/** Nothing **/
}

ExceptionXMLLoadingElementMissing::ExceptionXMLLoadingElementMissing(const TiXmlElement& element, const std::string& element_missing_name)
	: Exception("Element \"" + element_missing_name + "\" is missing in element \"" + element.ValueStr() + "\"")
{
	/** Nothing **/
}

ExceptionXMLLoadingElementHasNoChild::ExceptionXMLLoadingElementHasNoChild(const TiXmlElement& element)
	: Exception("Element \"" + element.ValueStr() + "\" should have children")
{
	/** Nothing **/
}

ExceptionXMLLoadingNoLoader::ExceptionXMLLoadingNoLoader(const std::string& id)
	: Exception("No loader found for \"" + id + "\"")
{
	/** Nothing **/
}

ExceptionAttributeNotFound::ExceptionAttributeNotFound(const std::string& attribute_name, const std::string& type_name)
	:Exception("Attribute \"" + attribute_name + "\" is not found for type \"" + type_name + "\"")
{
	/** Nothing **/
}

ExceptionAttributeNotFound::ExceptionAttributeNotFound(const std::string& attribute_name, const std::string& type_name, const std::string& object_name)
	: Exception("Attribute \"" + attribute_name + "\" is not found for type \"" + type_name + "\" for object \"" + object_name + "\"")
{
	/** Nothing **/
}

ExceptionAttributeAlreadyExists::ExceptionAttributeAlreadyExists(const std::string& attribute_name, const std::string& type_name)
	: Exception("Attribute \"" + attribute_name + "\" already exists for type \"" + type_name + "\"")
{
	/** Nothing **/
}

ExceptionAttributeAlreadyExists::ExceptionAttributeAlreadyExists(const std::string& attribute_name, const std::string& type_name, const std::string& object_name)
	: Exception("Attribute \"" + attribute_name + "\" already exists for type \"" + type_name + "\" for object \"" + object_name + "\"")
{
	/** Nothing **/
}

ExceptionResourceDoesNotExists::ExceptionResourceDoesNotExists(const std::string& resource_name, const std::string& context)
	: Exception("Resource \"" + resource_name + "\" does not exists in \"" + context + "\"")
{
	/** Nothing **/
}

ExceptionResourceAlradeyExists::ExceptionResourceAlradeyExists(const std::string& resource_name, const std::string& context)
	: Exception("Resource \"" + resource_name + "\" already exists in \"" + context + "\"")
{
	/** Nothing **/
}

ExceptionUnimplementedFunction::ExceptionUnimplementedFunction(const std::string& function_name)
	: Exception("Function \"" + function_name + "\" is not implemented yet")
{
	/** Nothing **/
}

ExceptionDLLFunctionNotFound::ExceptionDLLFunctionNotFound(const std::string& dll_name, const std::string& function_name)
	: Exception("Function \"" + function_name + "\" in library \"" + dll_name + "\" is not found")
{
	/** Nothing **/
}

ExceptionStringSplittingFail::ExceptionStringSplittingFail(const std::string& str)
	: Exception("Splitting failed in \"" + str + "\"")
{
	/** Nothing **/
}

ExceptionArraySize::ExceptionArraySize(unsigned int index, unsigned int array_size, const std::string& array_name, const std::string& context)
	: Exception("Index \"" + misc::fn_Number_To_String(index) + "\" is too large for \"" + array_name + "[0;" + misc::fn_Number_To_String(array_size) + "[\" in " + context)
{
	/** Nothing **/
}
