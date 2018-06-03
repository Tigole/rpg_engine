#ifndef _ISYSTEM_HPP
#define _ISYSTEM_HPP 1

#include <string>
#include <vector>

using SystemType = std::string;
using Requirement = std::string;

class ISystem
{
public:
	ISystem(const SystemType& type);


protected:
	SystemType m_type;
	std::vector<Requirement> m_required_components;
};

#endif // !_ISYSTEM_HPP