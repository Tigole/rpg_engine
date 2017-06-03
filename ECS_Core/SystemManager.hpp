#ifndef _SYSTEM_MANAGER_HPP
#define _SYSTEM_MANAGER_HPP 1

#include <unordered_map>
#include <memory>
#include "ISystem.hpp"

#include "Miscellaneous.hpp"

using SystemContainer = std::unordered_map<SystemType, std::unique_ptr<ISystem>>;

class SytemManager
{
public:
	SytemManager();
	~SytemManager();
	
	template<typename T>
	T* getSystem(const SystemType& system_type)
	{
		T* l_ret(nullptr);
		SystemContainer::iterator l_it;

		l_it = m_systems.find(system_type);
		if (l_it != m_systems.end())
		{
			l_ret = dynamicCast<T*>(l_it->second.get());
		}

		return l_ret;
	}

private:
	SystemContainer m_systems;
};

#endif // !_SYSTEM_MANAGER_HPP