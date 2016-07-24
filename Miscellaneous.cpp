#include "Miscellaneous.hpp"
#include "Logger/ILogger.h"

namespace misc
{
	ILoader::ILoader()
	{
		/** Noting **/
	}

	ILoader::~ILoader()
	{
		/** Nothing **/
	}

	bool ILoader::checkAttributes(const TiXmlElement& element, const std::vector<std::string>& attributes)
	{
		bool l_ret(attributes.size() != 0);
		std::vector<std::string>::size_type i;
		const char* attrib;

		for (i = 0; i < attributes.size(); i++)
		{
			attrib = element.Attribute(attributes[i].c_str());
			if (attrib == nullptr)
			{
				log().entranceFunction(FUNCTION_NAME);
				log() << "No attribute : \"" << attributes[i] << "\"\n\tIn element : \"" << element.Value() << "\"\n";
				log().exitFunction();
			}
		}
		return l_ret;
	}

	Loader::Loader(const std::string& element_name)
	 :	m_element_name(element_name)
	{
		/** Nothing **/
	}

	Loader::~Loader()
	{
		/** Nothing **/
	}

	const std::string& Loader::getElementName(void) const
	{
		return m_element_name;
	}



	/*std::string numberToString(unsigned char c)
	{
		return numberToString((unsigned int)c);
	}

	std::string numberToString(char c)
	{
		return numberToString((int)c);
	}*/
}
