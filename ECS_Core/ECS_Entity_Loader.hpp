#ifndef _ECS_ENTITY_LOADER_HPP
#define _ECS_ENTITY_LOADER_HPP 1

#include <string>

class ECS_EntityManager;
class XMLFileLoader;
class XML_Element;
class TextureManager;

class ECS_Entity_Loader
{
public:
	void mt_Prepare(const std::string& file_path, XMLFileLoader& xml_loader, ECS_EntityManager* target, TextureManager* texture_manager);

protected:

	bool mt_Load_Entity(const XML_Element& entity);
	bool mt_Load_Position(const XML_Element& position);
	bool mt_Load_Skeleton(const XML_Element& skeleton);
	bool mt_Load_Skeleton_Part(const XML_Element& part);
	bool mt_Load_Movable(const XML_Element& movable);
	bool mt_Load_State(const XML_Element& state);

	ECS_EntityManager* m_target;
	int m_entity_id;
	TextureManager* m_texture_manager;
};

#endif // !_ECS_ENTITY_LOADER_HPP