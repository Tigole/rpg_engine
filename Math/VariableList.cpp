#include "VariableList.hpp"

VariableList::VariableList()
 :	m_variables()
{
	/** Nothing **/
}

VariableList::VariableList(const std::vector<std::pair<std::string, std::string>>& var_list)
 :	m_variables()
{
	for (auto& var : var_list)
		m_variables[var.first] = var.second;
}

VariableList::VariableList(const std::string& var_name, const std::string& var_value)
 :	m_variables()
{
	m_variables[var_name] = var_value;
}

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
