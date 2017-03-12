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

class ExceptionXMLLoadingAttributeMissing : public Exception
{
public:
	ExceptionXMLLoadingAttributeMissing(const TiXmlElement& element, const std::string& attribute_missing_name);
};

class ExceptionXMLLoadingElementMissing : public Exception
{
public:
	ExceptionXMLLoadingElementMissing(const TiXmlElement& element, const std::string& element_missing_name);
};

class ExceptionXMLLoadingElementHasNoChild : public Exception
{
public:
	ExceptionXMLLoadingElementHasNoChild(const TiXmlElement& element);
};

class ExceptionXMLLoadingNoLoader : public Exception
{
public:
	ExceptionXMLLoadingNoLoader(const std::string& id);
};

class ExceptionAttributeNotFound : public Exception
{
public:
	ExceptionAttributeNotFound(const std::string& attribute_name, const std::string& type_name);
	ExceptionAttributeNotFound(const std::string& attribute_name, const std::string& type_name, const std::string& object_name);
};

class ExceptionAttributeAlreadyExists : public Exception
{
public:
	ExceptionAttributeAlreadyExists(const std::string& attribute_name, const std::string& type_name);
	ExceptionAttributeAlreadyExists(const std::string& attribute_name, const std::string& type_name, const std::string& object_name);
};

class ExceptionResourceDoesNotExists : public Exception
{
public:
	ExceptionResourceDoesNotExists(const std::string& resource_name, const std::string& context);
};

class ExceptionResourceAlradeyExists : public Exception
{
public:
	ExceptionResourceAlradeyExists(const std::string& resource_name, const std::string& context);
};

class ExceptionUnimplementedFunction : public Exception
{
public:
	ExceptionUnimplementedFunction(const std::string& function_name);
};

class ExceptionDLLFunctionNotFound : public Exception
{
public:
	ExceptionDLLFunctionNotFound(const std::string& dll_name, const std::string& function_name);
};

class ExceptionStringSplittingFail : public Exception
{
public:
	ExceptionStringSplittingFail(const std::string& str);
};

class ExceptionArraySize : public Exception
{
public:
	ExceptionArraySize(unsigned int index, unsigned int array_size, const std::string& array_name, const std::string& context);
};

#endif // !_EXCEPTION_HPP