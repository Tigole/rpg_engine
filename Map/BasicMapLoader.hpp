#ifndef _BASIC_MAP_LOADER_HPP
#define _BASIC_MAP_LOADER_HPP 1

#include "MapLoader.hpp"

class BasicMapLoader : public MapLoader
{
public:
	BasicMapLoader();

	virtual std::unique_ptr<IMap> load(const TiXmlElement& element, const TilesetManager& tm);
};

#endif // !_BASIC_MAP_LOADER_HPP