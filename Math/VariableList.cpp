#include "VariableList.hpp"

void VariableList::setVariable(const std::string& var_name, std::string var_value)
{
	m_variables[var_name] = var_value;
}

bool VariableList::getVariable(const std::string& var_name, std::string& var_value) const
{
	bool l_ret(false);
	std::map<std::string, std::string>::const_iterator it;

	it = m_variables.find(var_name);
	if (it != m_variables.end())
	{
		l_ret = true;
		var_value = it->second;
	}

	return l_ret;
}
