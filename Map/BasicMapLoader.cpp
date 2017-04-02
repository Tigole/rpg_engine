#include "BasicMapLoader.hpp"
#include "BasicMap.hpp"

BasicMapLoader::BasicMapLoader()
	:MapLoader("BasicMap")
{}

std::unique_ptr<IMap> BasicMapLoader::load(const TiXmlElement& element, const TilesetManager& tm)
{
	BasicMap bm;
	bm.load(element, tm);
	return std::unique_ptr<IMap>(new BasicMap(bm));
}