#ifndef _VARIABLE_LIST_HPP
#define _VARIABLE_LIST_HPP 1

#include <string>
#include <map>

class VariableList
{
public:
	void setVariable(const std::string& var_name, std::string var_value);

	bool getVariable(const std::string& var_name, std::string& var_value) const;

private:
	std::map<std::string, std::string> m_variables;

};

#endif // !_VARIABLE_LIST_HPP
