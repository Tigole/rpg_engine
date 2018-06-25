#include "ECS_Entity_Loader.hpp"
#include "ECS_EntityManager.hpp"
#include "XMLFileLoader.hpp"
#include "ECS_Game/ComponentPosition.hpp"
#include "ECS_Game/ComponentDrawableSkeleton.hpp"
#include "GUI/TextureManager.hpp"

void ECS_Entity_Loader::mt_Prepare(const std::string& file_path, XMLFileLoader& xml_loader, ECS_EntityManager* target, TextureManager* texture_manager)
{
	xml_loader.mt_Set_File(file_path);
	xml_loader.mt_Add_On_Entry_Callback(file_path, "/Entity", &ECS_Entity_Loader::mt_Load_Entity, this);
	xml_loader.mt_Add_On_Entry_Callback(file_path, "/Entity/Position", &ECS_Entity_Loader::mt_Load_Position, this);
	xml_loader.mt_Add_On_Entry_Callback(file_path, "/Entity/Skeleton", &ECS_Entity_Loader::mt_Load_Skeleton, this);
	xml_loader.mt_Add_On_Entry_Callback(file_path, "/Entity/Skeleton/Part", &ECS_Entity_Loader::mt_Load_Skeleton_Part, this);

	m_texture_manager = texture_manager;
	m_target = target;
}

bool ECS_Entity_Loader::mt_Load_Entity(const XML_Element& entity)
{
	bool l_b_ret;
	std::string l_id;

	l_b_ret = entity.mt_Get_Attribute("id", l_id);

	if (l_b_ret == true)
	{
		m_entity_id = m_target->mt_Add_Entity(l_id);
	}

	return l_b_ret;
}

bool ECS_Entity_Loader::mt_Load_Position(const XML_Element& position)
{
	bool l_b_ret(true);
	sf::Vector2f l_pos(-500.0f, -500.0f);
	int l_z(-1);

	ComponentPosition* l_position = m_target->mt_Add_Component<ComponentPosition>(m_entity_id, ECS_ComponentId::POSITION);

	l_position->mt_Set_Current_Position(l_pos, l_z);

	return l_b_ret;
}

bool ECS_Entity_Loader::mt_Load_Skeleton(const XML_Element& skeleton)
{
	bool l_b_ret(true);

	m_target->mt_Add_Component<ComponentDrawableSkeleton>(m_entity_id, ECS_ComponentId::DRAW_SKELETON);

	return l_b_ret;
}


bool ECS_Entity_Loader::mt_Load_Skeleton_Part(const XML_Element& part)
{
	bool l_b_ret(false);
	std::string l_part_id, l_texture_id;
	sf::Texture* l_texture(nullptr);

	l_b_ret = part.mt_Get_Attribute("id", l_part_id);
	if (l_b_ret == true)
	{
		l_b_ret = part.mt_Get_Attribute("texture_id", l_texture_id);
	}
	if (l_b_ret == true)
	{
		l_texture = m_texture_manager->mt_Get_Resource(l_texture_id);

		l_b_ret = (l_texture != nullptr);
	}
	if (l_b_ret == true)
	{
		ComponentDrawableSkeleton* l_skeleton = m_target->mt_Get_Component<ComponentDrawableSkeleton>(m_entity_id, ECS_ComponentId::DRAW_SKELETON);

		l_skeleton->mt_Add_Part(l_part_id, l_texture);
	}


	return l_b_ret;
}