#ifndef _MAP_LOADER_HPP
#define _MAP_LOADER_HPP 1

#include "Loader/Loader.hpp"
#include <string>
#include <memory>

class IMap;
class TiXmlElement;
class TilesetManager;
class XMLFileLoader;

class IMapLoader
{
public:
	IMapLoader(){}
	virtual ~IMapLoader(){}
	virtual void mt_Prepare(XMLFileLoader& file_loader, const std::string& file_path) = 0;
	virtual std::unique_ptr<IMap> mt_Get_Map() = 0;

protected:
	virtual void mt_Finalize(void) = 0;
};

template<typename MapType>
class MapLoader : public IMapLoader
{
public:
	virtual ~MapLoader(){}
	std::unique_ptr<IMap> mt_Get_Map()
	{
		std::unique_ptr<IMap> l_ret(nullptr);

		mt_Finalize();

		l_ret = m_map.mt_Clone();

		mt_Unload_Map();

		return l_ret;
	}
protected:
	virtual void mt_Unload_Map(void) = 0;
	MapType m_map;
};

#endif // !_MAP_LOADER_HPP
