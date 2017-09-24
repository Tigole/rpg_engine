#ifndef _IMAP_HPP
#define _IMAP_HPP 1

#include <string>
#include "Miscellaneous.hpp"

class TiXmlElement;
class MapManager;
class TilesetManager;
class Environment;
class XMLFileLoader;

class IMap : public misc::Clonable<IMap>
{
public:
	virtual ~IMap() {}

	virtual IMap* mt_Run(Environment& environment) = 0;
	virtual void mt_Initialize(MapManager& map_manager) = 0;
	virtual void mt_Save(TiXmlElement& element) = 0;
	virtual const std::string& mt_Get_Id() const = 0;
};

#endif // _IMAP_HPP
