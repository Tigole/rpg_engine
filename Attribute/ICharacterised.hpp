#ifndef _ICHARACTERISED_HPP
#define _ICHARACTERISED_HPP 1

template<class AttributeType>
class ICharacterised
{
public:
	virtual ~ICharacterised()
	{
		/** Nothing **/
	}

	virtual AttributeType* getAttribute(const std::string& attribute_name) = 0;
};

#endif // _ICHARACTERISED_HPP
