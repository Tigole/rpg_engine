#include "ECS_Entity_Loader.hpp"
#include "ECS_EntityManager.hpp"
#include "XMLFileLoader.hpp"
#include "ECS_Game/ComponentPosition.hpp"
#include "ECS_Game/ComponentDrawableSkeleton.hpp"
#include "ECS_Game/ComponentMovable.hpp"
#include "ECS_Game/ComponentState.hpp"
#include "GUI/TextureManager.hpp"

void ECS_Entity_Loader::mt_Prepare(const std::string& file_path, XMLFileLoader& xml_loader, ECS_EntityManager* target, TextureManager* texture_manager)
{
	xml_loader.mt_Set_File(file_path);
	xml_loader.mt_Add_On_Entry_Callback(file_path, "/Entity", &ECS_Entity_Loader::mt_Load_Entity, this);
	xml_loader.mt_Add_On_Entry_Callback(file_path, "/Entity/Position", &ECS_Entity_Loader::mt_Load_Position, this);
	xml_loader.mt_Add_On_Entry_Callback(file_path, "/Entity/Skeleton", &ECS_Entity_Loader::mt_Load_Skeleton, this);
	xml_loader.mt_Add_On_Entry_Callback(file_path, "/Entity/Skeleton/Part", &ECS_Entity_Loader::mt_Load_Skeleton_Part, this);
	xml_loader.mt_Add_On_Entry_Callback(file_path, "/Entity/Movable", &ECS_Entity_Loader::mt_Load_Movable, this);
	xml_loader.mt_Add_On_Entry_Callback(file_path, "/Entity/State", &ECS_Entity_Loader::mt_Load_State, this);

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
	sf::Vector2f l_pos_offset(0.0f, 0.0f);

	l_b_ret = part.mt_Get_Attribute("id", l_part_id);
	if (l_b_ret == true)
	{
		l_b_ret = part.mt_Get_Attribute("texture_id", l_texture_id);
	}
	if (l_b_ret == true)
	{
		part.mt_Get_Attribute("x_offset", l_pos_offset.x);
	}
	if (l_b_ret == true)
	{
		part.mt_Get_Attribute("y_offset", l_pos_offset.y);
	}
	if (l_b_ret == true)
	{
		l_texture = m_texture_manager->mt_Get_Resource(l_texture_id);

		l_b_ret = (l_texture != nullptr);
	}
	if (l_b_ret == true)
	{
		ComponentDrawableSkeleton* l_skeleton = m_target->mt_Get_Component<ComponentDrawableSkeleton>(m_entity_id, ECS_ComponentId::DRAW_SKELETON);

		l_skeleton->mt_Add_Part(l_part_id, l_texture, l_pos_offset.x, l_pos_offset.y);
	}


	return l_b_ret;
}

bool ECS_Entity_Loader::mt_Load_Movable(const XML_Element& movable)
{
	bool l_b_ret;
	float l_max_vel;
	sf::Vector2f l_speed;

	l_b_ret = movable.mt_Get_Attribute("max_vel", l_max_vel);

	if (l_b_ret == true)
	{
		l_b_ret = movable.mt_Get_Attribute("x_speed", l_speed.x);
	}
	if (l_b_ret == true)
	{
		l_b_ret = movable.mt_Get_Attribute("y_speed", l_speed.y);
	}

	if (l_b_ret == true)
	{
		ComponentMovable* l_movable = m_target->mt_Add_Component<ComponentMovable>(m_entity_id, ECS_ComponentId::MOVABLE);

		l_movable->mt_Set_Max_Velocity(l_max_vel);
		l_movable->mt_Set_Speed(l_speed);
	}

	return l_b_ret;
}

bool ECS_Entity_Loader::mt_Load_State(const XML_Element& state)
{
	ECS_EntityState l_id(ECS_EntityState::IDLE);

	state.mt_Get_Attribute("id", l_id, fn_EntityState_String_To_Enum);

	ComponentState* l_state = m_target->mt_Add_Component<ComponentState>(m_entity_id, ECS_ComponentId::STATE);

	l_state->mt_Set_State(l_id);

	return true;
}

std::string fn_ECS_EntityMessageId_Enum_To_String(const ECS_EntityMessageId& id)
{
	std::map<ECS_EntityMessageId, std::string> l_map;
	auto l_it = l_map.end();
	std::string l_ret = "???";

	l_map[ECS_EntityMessageId::DirectionChanged] = "DirectionChanged";
	l_map[ECS_EntityMessageId::MoveRqst] = "MoveRqst";
	l_map[ECS_EntityMessageId::StopMove] = "StopMove";
	l_map[ECS_EntityMessageId::StartMoving] = "StartMoving";
	l_map[ECS_EntityMessageId::StopMoving] = "StopMoving";

	l_it = l_map.find(id);

	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}

ECS_EntityEvent fn_ECS_EntityEvent_Enum_To_String(const std::string& ev)
{
	std::map<std::string, ECS_EntityEvent> l_map;
	auto l_it = l_map.end();
	ECS_EntityEvent l_ret = (ECS_EntityEvent)0;

	l_map["IsMoving"] = ECS_EntityEvent::IsMoving;

	l_it = l_map.find(ev);

	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}

std::string fn_ECS_EntityEvent_Enum_To_String(const ECS_EntityEvent& ev)
{
	std::map<ECS_EntityEvent, std::string> l_map;
	auto l_it = l_map.end();
	std::string l_ret = "???";

	l_map[ECS_EntityEvent::IsMoving] = "IsMoving";

	l_it = l_map.find(ev);

	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}

ECS_EntityState fn_EntityState_String_To_Enum(const std::string& state)
{
	std::map<std::string, ECS_EntityState> l_map;
	auto l_it = l_map.end();
	ECS_EntityState l_ret = ECS_EntityState::COUNT;

	l_map["dead"] = ECS_EntityState::DEAD;
	l_map["DEAD"] = ECS_EntityState::DEAD;
	l_map["Dead"] = ECS_EntityState::DEAD;
	l_map["idle"] = ECS_EntityState::IDLE;
	l_map["IDLE"] = ECS_EntityState::IDLE;
	l_map["Idle"] = ECS_EntityState::IDLE;
	l_map["walking"] = ECS_EntityState::WALKING;
	l_map["WALKING"] = ECS_EntityState::WALKING;
	l_map["Walking"] = ECS_EntityState::WALKING;

	l_it = l_map.find(state);

	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}

std::string fn_EntityState_Enum_To_String(const ECS_EntityState& state)
{
	std::map<ECS_EntityState, std::string> l_map;
	auto l_it = l_map.end();
	std::string l_ret = "???";

	l_map[ECS_EntityState::DEAD] = "Dead";
	l_map[ECS_EntityState::IDLE] = "Idle";
	l_map[ECS_EntityState::WALKING] = "Walking";

	l_it = l_map.find(state);

	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}