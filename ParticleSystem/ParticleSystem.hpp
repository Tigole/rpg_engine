#ifndef _PARTICLE_SYSTEM_HPP
#define _PARTICLE_SYSTEM_HPP 1

#include <vector>
#include <memory>
#include <unordered_map>

#include "ParticleGenerator.hpp"
#include "ParticleContainer.hpp"
#include "ParticleEmitter.hpp"
#include "ParticleUpdater.hpp"
#include "GameStates/GameStateTypes.hpp"
#include "FSM/StateManagement.hpp"

#include <SFML/Graphics.hpp>

using GeneratorList = std::vector<std::unique_ptr<ParticleGenerator>>;
using GeneratorContainer = std::unordered_map<std::string, GeneratorList>;
using EmitterList = std::vector<std::unique_ptr<ParticleEmitter>>;
using Emitters = std::unordered_map<GameStateType, EmitterList>;
using Particles = std::unordered_map<GameStateType, ParticleContainer>;
using Updaters = std::unordered_map<std::string, std::unique_ptr<ParticleUpdater>>;

class ParticleSystem : public StateDependent<GameStateType>
{
public:
	ParticleSystem(const std::string& resource_path, TextureManager* tm);

	virtual void mt_OnEntry(const GameStateType& state);
	void mt_Load(const std::string& xml_file_name);

	void mt_Update(float delta_time_s);
	void mt_Draw(sf::RenderWindow& window, int elevation);
	GeneratorList* mt_Get_Generator_List(const std::string& list_id);

	ParticleEmitter* mt_Add_Emitter(GameStateType game_state, const std::string& generator_list_id, const sf::Vector3f& emitter_position, float emitting_rate, std::size_t particle_count);
	void mt_Remove_Emitter(ParticleEmitter* emitter);

private:
	Particles m_Particles;
	GeneratorContainer m_Generators;
	Emitters m_Emitters;
	Updaters m_Updaters;
	TextureManager* m_Manager;
	std::string m_Resource_Path;
	std::vector<ParticleEmitter*> m_Emitter_To_Remove;
};

#endif // !_PARTICLE_SYSTEM_HPP