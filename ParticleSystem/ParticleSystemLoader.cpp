#include "ParticleSystemLoader.hpp"

#include "Generator/ParticleGeneratorTexture.hpp"
#include "Generator/ParticleGeneratorAreaPosition.hpp"
#include "Generator/ParticleGeneratorRangeColor.hpp"
#include "Generator/ParticleGeneratorLifespan.hpp"
#include "Generator/ParticleGeneratorRandomColor.hpp"
#include "Generator/ParticleGeneratorRandomSize.hpp"
#include "Generator/ParticleGeneratorRandomVelocity.hpp"
#include "Generator/ParticleGeneratorRangeRotation.hpp"
#include "Generator/ParticleGeneratorRangeSize.hpp"
#include "Generator/ParticleGeneratorPointPosition.hpp"

void ParticleGeneratorLoader::mt_Prepare(const std::string& filename, XMLFileLoader& loader, GeneratorList& generator_list)
{
	m_generator_list = &generator_list;

	loader.mt_Set_File(filename);
	//loader.mt_Add_On_Entry_Callback("/Generator", &ParticleGeneratorLoader::mt_Load_Generator, this);
	loader.mt_Add_On_Entry_Callback("/Generator/Texture", &ParticleGeneratorLoader::mt_Load_Texture, this);
	loader.mt_Add_On_Entry_Callback("/Generator/AreaPosition", &ParticleGeneratorLoader::mt_Load_AreaPosition, this);
	loader.mt_Add_On_Entry_Callback("/Generator/PointPosition", &ParticleGeneratorLoader::mt_Load_PointPosition, this);
	loader.mt_Add_On_Entry_Callback("/Generator/RangeColor", &ParticleGeneratorLoader::mt_Load_RangeColor, this);
	loader.mt_Add_On_Entry_Callback("/Generator/RandomColor", &ParticleGeneratorLoader::mt_Load_RandomColor, this);
	loader.mt_Add_On_Entry_Callback("/Generator/RandomVelocity", &ParticleGeneratorLoader::mt_Load_RandomVelocity, this);
	loader.mt_Add_On_Entry_Callback("/Generator/RangeSize", &ParticleGeneratorLoader::mt_Load_RangeSize, this);
	loader.mt_Add_On_Entry_Callback("/Generator/Life", &ParticleGeneratorLoader::mt_Load_Life, this);
}

/*bool ParticleGeneratorLoader::mt_Load_Generator(const XML_Element& rccl_Element)
{
	bool l_b_Ret;
	float l_emitting_rate;
	std::size_t l_particle_count(-1);

	l_b_Ret = rccl_Element.mt_Get_Attribute("emittig_rate", l_emitting_rate);
	if (l_b_Ret == true) m_emitter->mt_Set_Emitting_Rate(l_emitting_rate);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("particle_count", l_particle_count);
	if (l_b_Ret == true) m_emitter->mt_Set_Particle_Count(l_particle_count);

	return l_b_Ret;
}*/

bool ParticleGeneratorLoader::mt_Load_Texture(const XML_Element& rccl_Element)
{
	bool l_b_Ret;
	std::unique_ptr<ParticleGeneratorTexture> l_Texture(std::make_unique<ParticleGeneratorTexture>());

	l_b_Ret = rccl_Element.mt_Get_Attribute("id", l_Texture->m_Texture_Id);
	if (l_b_Ret == true) m_generator_list->push_back(std::move(l_Texture));

	return l_b_Ret;
}

bool ParticleGeneratorLoader::mt_Load_AreaPosition(const XML_Element& rccl_Element)
{
	auto l_Pos = std::make_unique<ParticleGeneratorAreaPosition>();

	rccl_Element.mt_Get_Attribute("x", l_Pos->m_Deviation.x);
	rccl_Element.mt_Get_Attribute("y", l_Pos->m_Deviation.y);
	rccl_Element.mt_Get_Attribute("z", l_Pos->m_Deviation.z);

	m_generator_list->push_back(std::move(l_Pos));

	return true;
}

bool ParticleGeneratorLoader::mt_Load_PointPosition(const XML_Element& rccl_Element)
{
	m_generator_list->push_back(std::make_unique<ParticleGeneratorPointPosition>());

	return true;
}

bool ParticleGeneratorLoader::mt_Load_RangeColor(const XML_Element& rccl_Element)
{
	bool l_b_Ret;
	auto l_Col = std::make_unique<ParticleGeneratorRangeColor>();

	l_b_Ret = rccl_Element.mt_Get_Attribute("sr", l_Col->m_Start_Color.r);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("sg", l_Col->m_Start_Color.g);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("sb", l_Col->m_Start_Color.b);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("sa", l_Col->m_Start_Color.a);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("fa", l_Col->m_Final_Color.r);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("fg", l_Col->m_Final_Color.g);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("fb", l_Col->m_Final_Color.b);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("fa", l_Col->m_Final_Color.a);

	if (l_b_Ret == true)
	{
		m_generator_list->push_back(std::move(l_Col));
	}

	return l_b_Ret;
}

bool ParticleGeneratorLoader::mt_Load_RandomColor(const XML_Element& rccl_Element)
{
	bool l_b_Ret;
	auto l_Col = std::make_unique<ParticleGeneratorRandomColor>();

	l_b_Ret = rccl_Element.mt_Get_Attribute("fr", l_Col->m_From.x);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("fg", l_Col->m_From.y);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("fb", l_Col->m_From.z);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("tr", l_Col->m_To.x);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("tg", l_Col->m_To.y);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("tb", l_Col->m_To.z);

	if (l_b_Ret == true)
	{
		m_generator_list->push_back(std::move(l_Col));
	}

	return l_b_Ret;
}

bool ParticleGeneratorLoader::mt_Load_RandomVelocity(const XML_Element& rccl_Element)
{
	auto l_Vel = std::make_unique<ParticleGeneratorRandomVelocity>();

	rccl_Element.mt_Get_Attribute("fx", l_Vel->m_From.x);
	rccl_Element.mt_Get_Attribute("fy", l_Vel->m_From.y);
	rccl_Element.mt_Get_Attribute("fz", l_Vel->m_From.z);
	rccl_Element.mt_Get_Attribute("tx", l_Vel->m_To.x);
	rccl_Element.mt_Get_Attribute("ty", l_Vel->m_To.y);
	rccl_Element.mt_Get_Attribute("tz", l_Vel->m_To.z);

	m_generator_list->push_back(std::move(l_Vel));

	return true;
}

bool ParticleGeneratorLoader::mt_Load_RangeSize(const XML_Element& rccl_Element)
{
	bool l_b_Ret;
	auto l_Size = std::make_unique<ParticleGeneratorRangeSize>();

	l_b_Ret = rccl_Element.mt_Get_Attribute("start", l_Size->m_From);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("final", l_Size->m_To);
	if (l_b_Ret == true) m_generator_list->push_back(std::move(l_Size));

	return l_b_Ret;
}

bool ParticleGeneratorLoader::mt_Load_Life(const XML_Element& rccl_Element)
{
	bool l_b_Ret;
	auto l_Life = std::make_unique<ParticleGeneratorLifespan>();

	l_b_Ret = rccl_Element.mt_Get_Attribute("min", l_Life->m_From);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("max", l_Life->m_To);
	if (l_b_Ret == true) m_generator_list->push_back(std::move(l_Life));

	return l_b_Ret;
}








bool ParticleSystemLoader::mt_Load(const std::string& resource_path, const std::string& filename, ParticleSystem& target)
{
	bool l_b_Ret = true;
	XMLFileLoader l_xml_loader;

	m_Resource_Path = resource_path;
	m_Target = &target;

	l_xml_loader.mt_Set_File(filename);
	l_xml_loader.mt_Add_On_Entry_Callback(filename, "/ParticleSystem/Generator", &ParticleSystemLoader::mt_Load_Generator, this);

	l_xml_loader.mt_Start();
	l_xml_loader.mt_Wait_For_Ending();

	return l_b_Ret;
}

bool ParticleSystemLoader::mt_Load_Generator(const XML_Element& rccl_Element)
{
	bool l_b_Ret = false;
	XMLFileLoader l_xml_loader;
	ParticleGeneratorLoader l_loader;
	std::string l_generator_list_id;
	std::string l_path;

	l_b_Ret = rccl_Element.mt_Get_Attribute("id", l_generator_list_id);
	if (l_b_Ret == true) l_b_Ret = rccl_Element.mt_Get_Attribute("path", l_path);
	if (l_b_Ret == true)
	{
		auto l_list = m_Target->mt_Get_Generator_List(l_generator_list_id);

		if (l_list != nullptr)
		{
			l_loader.mt_Prepare(m_Resource_Path + "Data/" + l_path, l_xml_loader, *l_list);
			l_xml_loader.mt_Start();
			l_xml_loader.mt_Wait_For_Ending(1);
		}
		else
		{
			l_b_Ret = false;
		}
	}

	return l_b_Ret;
}
