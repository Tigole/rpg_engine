#ifndef _PARTICLE_SYSTEM_LOADER_HPP
#define _PARTICLE_SYSTEM_LOADER_HPP 1

#include "XMLFileLoader.hpp"

#include "ParticleSystem.hpp"

class ParticleGeneratorLoader
{
public:
	void mt_Prepare(const std::string& filename, XMLFileLoader& loader, GeneratorList& generator_list);

protected:
	//bool mt_Load_Generator(const XML_Element& rccl_Element);
	bool mt_Load_Texture(const XML_Element& rccl_Element);
	bool mt_Load_AreaPosition(const XML_Element& rccl_Element);
	bool mt_Load_PointPosition(const XML_Element& rccl_Element);
	bool mt_Load_RangeColor(const XML_Element& rccl_Element);
	bool mt_Load_RandomColor(const XML_Element& rccl_Element);
	bool mt_Load_RandomVelocity(const XML_Element& rccl_Element);
	bool mt_Load_RangeSize(const XML_Element& rccl_Element);
	bool mt_Load_Life(const XML_Element& rccl_Element);

	GeneratorList* m_generator_list;
};

class ParticleSystemLoader
{
public:
	bool mt_Load(const std::string& resource_path, const std::string& filename, ParticleSystem& target);

private:
	bool mt_Load_Generator(const XML_Element& rccl_Element);
	ParticleSystem* m_Target;
	std::string m_Resource_Path;
};

#endif // !_PARTICLE_SYSTEM_LOADER_HPP