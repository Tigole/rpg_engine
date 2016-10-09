#ifndef _EXCEPTION_HPP
#define _EXCEPTION_HPP 1

#include <string>

class TiXmlElement;

class IException
{
public:
	virtual ~IException();

	virtual const char* what(void) const = 0;
};

class Exception : public IException
{
public:
	Exception(const std::string& str);

	const char* what(void) const;

protected:
	std::string m_what;
};

class XMLLoadingExceptionAttributeMissing : public Exception
{
public:
	XMLLoadingExceptionAttributeMissing(const TiXmlElement& element, const std::string& attribute_missing_name);
};

class XMLLoadingExceptionElementMissing : public Exception
{
public:
	XMLLoadingExceptionElementMissing(const TiXmlElement& element, const std::string& element_missing_name);
};

class XMLLoadingExceptionElementHasNoChild : public Exception
{
public:
	XMLLoadingExceptionElementHasNoChild(const TiXmlElement& element);
};

class XMLLoadingExceptionNoLoader : public Exception
{
public:
	XMLLoadingExceptionNoLoader(const std::string& id);
};

class AttributeNotFound : public Exception
{
public:
	AttributeNotFound(const std::string& attribute_name, const std::string& type_name);
	AttributeNotFound(const std::string& attribute_name, const std::string& type_name, const std::string& object_name);
};

class AttributeAlreadyExists : public Exception
{
public:
	AttributeAlreadyExists(const std::string& attribute_name, const std::string& type_name);
	AttributeAlreadyExists(const std::string& attribute_name, const std::string& type_name, const std::string& object_name);
};

class ResourceDoesNotExists : public Exception
{
public:
	ResourceDoesNotExists(const std::string& resource_name, const std::string& context);
};

class ResourceAlradeyExists : public Exception
{
public:
	ResourceAlradeyExists(const std::string& resource_name, const std::string& context);
};

class UnimplementedFunction : public Exception
{
public:
	UnimplementedFunction(const std::string& function_name);
};

class DLLFunctionNotFound : public Exception
{
public:
	DLLFunctionNotFound(const std::string& dll_name, const std::string& function_name);
};

class StringSplittingFail : public Exception
{
public:
	StringSplittingFail(const std::string& str);
};

#endif // !_EXCEPTION_HPP