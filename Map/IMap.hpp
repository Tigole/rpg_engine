#ifndef _IMAP_HPP
#define _IMAP_HPP 1

#include <string>
#include "Miscellaneous.hpp"

class TiXmlElement;

class IMap //: public misc::Clonable<IMap>
{
public:
	virtual ~IMap() {}

	virtual void mt_Save(TiXmlElement& element) = 0;
	virtual const std::string& mt_Get_Id() const = 0;
};

#endif // _IMAP_HPP
