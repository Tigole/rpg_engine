#ifndef _IMAP_HPP
#define _IMAP_HPP 1

class TiXmlElement;
class MapManager;

class IMap
{
public:
	virtual ~IMap() {}

	virtual IMap* run() = 0;
	virtual void load(const TiXmlElement& element, MapManager& map_manager) = 0;
	virtual void save(TiXmlElement& element) = 0;
};

#endif // _IMAP_HPP