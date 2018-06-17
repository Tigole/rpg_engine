#ifndef _TILESET_MANAGER_HPP
#define _TILESET_MANAGER_HPP 1

#include <string>
#include <map>
#include "Tileset.hpp"
#include "ResourceManager.hpp"

class TilesetManager : public ResourceManager<TilesetManager, Tileset>
{
public:
	TilesetManager(const std::string& resource_path, TextureManager* texture_manager)
		:ResourceManager<TilesetManager, Tileset>(resource_path, "/Tilesets/Tileset"),
		m_texture_manager(texture_manager)
	{}
	virtual ~TilesetManager() {}
	bool mt_Load(Tileset* resource, const std::string& file_path)
	{
		bool l_b_ret;
		TilesetLoader l_tilset_loader_type(*m_texture_manager);
		XMLFileLoader l_xml_loader;

		l_b_ret = l_tilset_loader_type.mt_Prepare(*resource, l_xml_loader, file_path);

		l_xml_loader.mt_Start();
		l_xml_loader.mt_Wait_For_Ending();

		return l_b_ret;
	}

private:
	TextureManager* m_texture_manager;
};

#endif // _TILESET_MANAGER_HPP
