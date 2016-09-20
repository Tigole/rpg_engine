#ifndef _VARIABLE_LIST_HPP
#define _VARIABLE_LIST_HPP 1

#include <string>
#include <map>
#include <vector>
#include <utility>

class VariableList
{
public:
	VariableList();
	VariableList(const std::vector<std::pair<std::string, std::string>>& var_list);
	VariableList(const std::string& var_name, const std::string& var_value);

	void setVariable(const std::string& var_name, std::string var_value);
	bool getVariable(const std::string& var_name, std::string& var_value) const;

private:
	std::map<std::string, std::string> m_variables;

};

#endif // !_VARIABLE_LIST_HPP
