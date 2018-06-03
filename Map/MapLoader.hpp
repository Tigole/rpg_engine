#ifndef _MAP_LOADER_HPP
#define _MAP_LOADER_HPP 1

#include "Loader/Loader.hpp"
#include <string>
#include <memory>

#include "XMLFileLoader.hpp"

class IMap;
class TiXmlElement;
class TilesetManager;
class XMLFileLoader;

template<typename MapType>
class IMapLoader
{
public:
	IMapLoader(){}
	virtual ~IMapLoader(){}
	virtual bool mt_Prepare(MapType& map, XMLFileLoader& file_loader, const std::string& file_path) = 0;

protected:
};

template<typename MapType>
class MapLoader : public IMapLoader<MapType>
{
public:
	MapLoader() : m_Target(nullptr){}
	virtual ~MapLoader(){}
	bool mt_Prepare(MapType& map, XMLFileLoader& file_loader, const std::string& file_path)
	{
		bool l_b_ret;

		m_Target = &map;

		l_b_ret = mt_Prepare_Loader(file_loader, file_path);

		return l_b_ret;
	}
protected:
	virtual bool mt_Prepare_Loader(XMLFileLoader& file_loader, const std::string& file_name) = 0;

	MapType* m_Target;
};

#endif // !_MAP_LOADER_HPP
