#ifndef _IMAP_HPP
#define _IMAP_HPP 1

class TiXmlElement;
class MapManager;
class TilesetManager;
struct Environment;

class IMap
{
public:
	virtual ~IMap() {}

	virtual IMap* run(Environment& environment) = 0;
	virtual void load(const TiXmlElement& element, const TilesetManager& tm) = 0;
	virtual void initialize(MapManager& map_manager) = 0;
	virtual void save(TiXmlElement& element) = 0;
};

#endif // _IMAP_HPP