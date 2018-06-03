#ifndef _STRING_MANAGER_HPP
#define _STRING_MANAGER_HPP 1

#include "GameString.hpp"

class XML_Element;

using Strings = std::unordered_map<std::string, GameString>;
using Language = std::unordered_map<std::string, Strings>;

class StringManager
{
public:
	StringManager(const std::string& resource_path);

	void mt_Load(const std::string& conf_file);

	std::string mt_Get_String(const std::string& lang_id, const std::string& string_id, const GameStringArguments& args = GameStringArguments());
	std::string mt_Get_Current_Lang(void) const;

	void mt_Add_Sentence(const std::string& lang_id, const std::string& id, const GameString& string);

private:

	bool mt_Load_Language(const XML_Element& language);
	bool mt_Load_User(const XML_Element& user);

	std::string mt_Get_String(Strings& strings, const std::string& string_id, const GameStringArguments& args);
	std::string mt_Get_String(const std::string& lang_id);
	Language m_languages;
	std::string m_current_lang;
	std::string m_resource_path;
};

#endif // !_STRING_MANAGER_HPP