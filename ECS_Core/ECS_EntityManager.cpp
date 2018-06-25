#include "ECS_EntityManager.hpp"
#include "XMLFileLoader.hpp"
#include "ECS_Entity_Loader.hpp"


ECS_EntityManager::ECS_EntityManager(const std::string& resource_path, ECS_SystemManager& system_manager, TextureManager* texture_manager)
 :	m_entities(),
 	m_system_manager(&system_manager),
	m_resource_path(resource_path),
	m_current_id(0),
	m_texture_manager(texture_manager)
{}

ECS_EntityId ECS_EntityManager::mt_Get_Entity(const std::string& id)
{
	ECS_EntityId l_ret;
	auto l_it = m_string_converter.find(id);

	if (l_it == m_string_converter.end())
	{
		auto l_str = m_paths.find(id);

		if (l_str != m_paths.end())
		{
			ECS_Entity_Loader l_loader;
			XMLFileLoader l_xml_loader;

			l_loader.mt_Prepare(m_resource_path + "Data/" + l_str->second, l_xml_loader, this, m_texture_manager);

			l_xml_loader.mt_Start();
			l_xml_loader.mt_Wait_For_Ending();

			l_it = m_string_converter.find(id);
		}
	}

	if (l_it != m_string_converter.end())
	{
		l_ret = l_it->second;
	}
	else
	{
		l_ret = -1;
	}	

	return l_ret;
}

ECS_EntityId ECS_EntityManager::mt_Add_Entity(const std::string& id)
{
	ECS_EntityId l_ret(m_current_id);

	m_string_converter.emplace(id, l_ret);
	m_entities.emplace(l_ret, ECS_ComponentContainer());

	m_current_id++;
	return l_ret;
}

void ECS_EntityManager::mt_Load_Paths(const std::string& conf_file)
{
	XMLFileLoader l_loader;

	l_loader.mt_Set_File(conf_file);
	l_loader.mt_Add_On_Entry_Callback(conf_file, "/Entities/Entity", &ECS_EntityManager::mt_Load_Entity, this);

	l_loader.mt_Start();
	l_loader.mt_Wait_For_Ending();
}

bool ECS_EntityManager::mt_Load_Entity(const XML_Element& entity)
{
	bool l_b_ret;
	std::string l_id, l_path;


	l_b_ret = entity.mt_Get_Attribute("id", l_id);
	if (l_b_ret == true)
	{
		l_b_ret = entity.mt_Get_Attribute("path", l_path);
	}

	if (l_b_ret == true)
	{
		m_paths.emplace(l_id, l_path);
	}

	return l_b_ret;
}