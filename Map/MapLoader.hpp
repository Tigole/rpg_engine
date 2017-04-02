#ifndef _MAP_LOADER_HPP
#define _MAP_LOADER_HPP 1

#include "Loader/Loader.hpp"
#include <string>
#include <memory>

class IMap;
class TiXmlElement;
class TilesetManager;

class MapLoader : public Loader
{
public:
	MapLoader(const std::string& element_name) : Loader(element_name) {}
	virtual ~MapLoader(){}
	virtual std::unique_ptr<IMap> load(const TiXmlElement& element, const TilesetManager& tm) = 0;
};

#endif // !_MAP_LOADER_HPP