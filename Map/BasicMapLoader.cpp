#include "BasicMapLoader.hpp"
#include "BasicMap.hpp"

BasicMapLoader::BasicMapLoader()
	:MapLoader("BasicMap")
{}

std::unique_ptr<IMap> BasicMapLoader::load(const TiXmlElement& element, const TilesetManager& tm)
{
	BasicMap bm;
	bm.load(element, tm);
	return bm.clone();
}