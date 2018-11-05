#include "ParticleSystem.hpp"

#include "Generator/ParticleGeneratorTexture.hpp"
#include "Generator/ParticleGeneratorAreaPosition.hpp"
#include "Generator/ParticleGeneratorRangeColor.hpp"
#include "Generator/ParticleGeneratorLifespan.hpp"
#include "Generator/ParticleGeneratorRandomColor.hpp"
#include "Generator/ParticleGeneratorRandomSize.hpp"
#include "Generator/ParticleGeneratorRandomVelocity.hpp"
#include "Generator/ParticleGeneratorRangeRotation.hpp"
#include "Generator/ParticleGeneratorRangeSize.hpp"

#include "Updater/ParticleUpdaterDrawable.hpp"
#include "Updater/ParticleUpdaterInterpolator.hpp"
#include "Updater/ParticleUpdaterLifespan.hpp"
#include "Updater/ParticleUpdaterSpatial.hpp"

#include "ParticleEmitter.hpp"

#include "ParticleSystemLoader.hpp"


ParticleSystem::ParticleSystem(const std::string& resource_path, TextureManager* tm)
	:m_Manager(tm),
	m_Resource_Path(resource_path)
{
	/*auto l_Texture = std::make_unique<ParticleGeneratorTexture>();
	auto l_Pos = std::make_unique<ParticleGeneratorAreaPosition>();
	auto l_Col = std::make_unique<ParticleGeneratorRangeColor>();
	auto l_Life = std::make_unique<ParticleGeneratorLifespan>();
	auto l_Vel = std::make_unique<ParticleGeneratorRandomVelocity>();
	auto l_Size = std::make_unique<ParticleGeneratorRangeSize>();
	//ParticleGeneratorRandomColor* l_RCol = new ParticleGeneratorRandomColor();
	l_Texture->m_Texture_Id = "Circle";
	l_Pos->m_Deviation = { 0.0f, 0.0f, 0.0f };
	l_Col->m_Start_Color = sf::Color::Red;// (0xFE, 0x1B, 0x00);
	l_Col->m_Final_Color = sf::Color::White;
	l_Life->m_From = 5;
	l_Life->m_To = 5;
	l_Vel->m_From = { -100, -100, 0 };
	l_Vel->m_To = { -75, -75, 0 };
	l_Size->m_From = 5;
	l_Size->m_To = 25;

	m_Particles.emplace(GameStateType::Game, ParticleContainer());
	m_Particles[GameStateType::Game].mt_Set_Texture_Manager(m_Manager);
	m_Particles[GameStateType::Game].mt_Resize(50);
	m_Generators.emplace("Flame", GeneratorList());
	m_Generators["Flame"].push_back(std::move(l_Texture));
	m_Generators["Flame"].push_back(std::move(l_Pos));
	m_Generators["Flame"].push_back(std::move(l_Col));
	m_Generators["Flame"].push_back(std::move(l_Life));
	m_Generators["Flame"].push_back(std::move(l_Size));
	m_Generators["Flame"].push_back(std::move(l_Vel));
	
	m_Emitters.emplace(GameStateType::Game, EmitterList());
	m_Emitters[GameStateType::Game].push_back(std::make_unique<ParticleEmitter>(ParticleEmitter({ 330.0f, 325.0f, 1.0f }, 1)));
	m_Emitters[GameStateType::Game][0]->mt_Set_System(this);
	m_Emitters[GameStateType::Game][0]->mt_Set_Emitting_Rate(0.1f * 10);
	m_Emitters[GameStateType::Game][0]->mt_Set_Generator_List("Flame");*/

	for (std::size_t ii = 0; ii < static_cast<std::size_t>(GameStateType::COUNT); ii++)
	{
		m_Emitters.emplace(static_cast<GameStateType>(ii), EmitterList());
		m_Particles.emplace(static_cast<GameStateType>(ii), ParticleContainer());
		m_Particles[static_cast<GameStateType>(ii)].mt_Set_Texture_Manager(tm);
		m_Particles[static_cast<GameStateType>(ii)].mt_Resize(ParticleContainer::Max_Particle);
	}
	
	m_Updaters.emplace("Drawable", std::make_unique<ParticleUpdaterDrawable>());
	m_Updaters.emplace("Interpolator", std::make_unique<ParticleUpdaterInterpolator>());
	m_Updaters.emplace("Spatial", std::make_unique<ParticleUpdaterSpatial>());
	m_Updaters.emplace("Lifespan", std::make_unique<ParticleUpdaterLifespan>());
}

void ParticleSystem::mt_OnEntry(const GameStateType& state)
{
	m_current_state = state;
}

void ParticleSystem::mt_Update(float delta_time_s)
{
	auto l_emitter_list = m_Emitters.find(m_current_state);
	auto l_particle = m_Particles.find(m_current_state);
	if (l_particle != m_Particles.end())
	{
		if (l_emitter_list != m_Emitters.end())
		{
			for (auto& l_emitter : l_emitter_list->second)
			{
				l_emitter->mt_Update(delta_time_s, l_particle->second);
			}
		}
		for (auto& l_updater : m_Updaters)
		{
			l_updater.second->mt_Update(delta_time_s, l_particle->second);
		}
	}

	for (auto& emitter_to_remove : m_Emitter_To_Remove)
	{
		auto l_it = std::remove_if(m_Emitters[m_current_state].begin(), m_Emitters[m_current_state].end(), [emitter_to_remove](std::unique_ptr<ParticleEmitter>& emitter)
		{
			return emitter.get() == emitter_to_remove;
		});

		if (l_it != m_Emitters[m_current_state].end())
		{
			m_Emitters[m_current_state].erase(l_it);
		}
	}
	m_Emitter_To_Remove.resize(0);
}

void ParticleSystem::mt_Draw(sf::RenderWindow& window, int elevation)
{
	auto l_Particles = m_Particles.find(m_current_state);
	if (l_Particles != m_Particles.end())
	{
		auto& l_P = l_Particles->second;
		for (std::size_t ii = 0; ii < l_P.mt_Get_Alive_Count(); ii++)
		{
			if (l_P.m_Position[ii].z == elevation)
			{
				window.draw(l_P.m_Drawable[ii]);
			}
		}
	}
}

GeneratorList* ParticleSystem::mt_Get_Generator_List(const std::string& list_id)
{
	GeneratorList* l_ret(nullptr);
	auto l_list = m_Generators.find(list_id);

	if (l_list != m_Generators.end())
	{
		l_ret = &l_list->second;
	}
	else
	{
		l_ret = &m_Generators.emplace(list_id, GeneratorList()).first->second;
	}

	return l_ret;
}

ParticleEmitter* ParticleSystem::mt_Add_Emitter(GameStateType game_state, const std::string& generator_list_id, const sf::Vector3f& emitter_position, float emitting_rate, std::size_t particle_count)
{
	ParticleEmitter*  l_Ret(nullptr);
	auto l_it = m_Emitters.find(game_state);
	auto l_emitter = std::make_unique<ParticleEmitter>();

	l_emitter->mt_Set_System(this);
	l_emitter->mt_Set_Position(emitter_position);
	l_emitter->mt_Set_Emitting_Rate(emitting_rate);
	l_emitter->mt_Set_Particle_Count(particle_count);
	l_emitter->mt_Set_Generator_List(generator_list_id);

	m_Emitters[game_state].push_back(std::move(l_emitter));
	l_Ret = m_Emitters[game_state].back().get();

	return l_Ret;
}

void ParticleSystem::mt_Load(const std::string& xml_file_name)
{
	ParticleSystemLoader l_loader;

	l_loader.mt_Load(m_Resource_Path, xml_file_name, *this);
}

void ParticleSystem::mt_Remove_Emitter(ParticleEmitter* emitter)
{
	m_Emitter_To_Remove.push_back(emitter);
}