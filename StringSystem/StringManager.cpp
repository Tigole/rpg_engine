#include "StringManager.hpp"

#include "XMLFileLoader.hpp"

class StringManager_TextLoader
{
public:
	void mt_Prepare(XMLFileLoader& loader, const std::string& file_path, const std::string& lang_id, StringManager* target)
	{
		m_target = target;
		m_lang_id = lang_id;

		loader.mt_Set_File(file_path);
		loader.mt_Add_On_Entry_Callback(file_path, "/Texts/Text", &StringManager_TextLoader::mt_Load_Text, this);
	}

private:
	bool mt_Load_Text(const XML_Element& text)
	{
		bool l_b_ret(false);
		std::string l_id, l_sentence;

		l_b_ret = text.mt_Get_Attribute("id", l_id);
		if (l_b_ret == true)
		{
			l_b_ret = text.mt_Get_Attribute("val", l_sentence);
		}
		if (l_b_ret == true)
		{
			m_target->mt_Add_Sentence(m_lang_id, l_id, GameString(l_sentence));
		}

		return l_b_ret;
	}
	StringManager* m_target;
	std::string m_lang_id;
};

StringManager::StringManager(const std::string& resource_path)
	:m_resource_path(resource_path)
{}


void StringManager::mt_Load(const std::string& conf_file)
{
	XMLFileLoader l_xml_loader;

	l_xml_loader.mt_Set_File(conf_file);
	l_xml_loader.mt_Add_On_Entry_Callback(conf_file, "/Languages/User", &StringManager::mt_Load_User, this);
	l_xml_loader.mt_Add_On_Entry_Callback(conf_file, "/Languages/Language", &StringManager::mt_Load_Language, this);

	l_xml_loader.mt_Start();
	l_xml_loader.mt_Wait_For_Ending();
}

sf::String StringManager::mt_Get_String(const std::string& lang_id, const std::string& string_id, const GameStringArguments& args)
{
	std::string l_ret;
	auto l_lang(m_languages.find(lang_id));

	if (l_lang != m_languages.end())
	{
		l_ret = mt_Get_String(l_lang->second, string_id, args);
	}
	else
	{
		l_ret = mt_Get_String(lang_id);
	}

	return sf::String::fromUtf8(l_ret.begin(), l_ret.end());
}

std::string StringManager::mt_Get_Current_Lang(void) const
{
	return m_current_lang;
}

std::string StringManager::mt_Get_String(Strings& strings, const std::string& string_id, const GameStringArguments& args)
{
	std::string l_ret;
	auto l_str(strings.find(string_id));

	if (l_str != strings.end())
	{
		l_ret = l_str->second.mt_Get_String(args);
	}

	return l_ret;
}

std::string StringManager::mt_Get_String(const std::string& lang_id)
{
	std::string l_ret;

	l_ret.resize(26);

	for (std::size_t i = 0; i < l_ret.size(); i++)
	{
		l_ret[i] = i + 'a';
	}

	return l_ret;
}

void StringManager::mt_Add_Sentence(const std::string& lang_id, const std::string& id, const GameString& string)
{
	auto l_lang(m_languages.find(lang_id));
	Strings::iterator l_id;

	if (l_lang == m_languages.end())
	{
		l_lang = m_languages.emplace(lang_id, Strings()).first;
	}

	l_lang->second.emplace(id, string);
}

bool StringManager::mt_Load_Language(const XML_Element& language)
{
	bool l_b_ret(false);
	std::string l_lang_id;
	std::string l_file;
	StringManager_TextLoader l_loader;
	XMLFileLoader l_xml_loader;

	l_b_ret = language.mt_Get_Attribute("id", l_lang_id);

	if (l_b_ret == true)
	{
		l_b_ret = language.mt_Get_Attribute("path", l_file);
	}

	if (l_b_ret == true)
	{
		l_loader.mt_Prepare(l_xml_loader, m_resource_path + l_file, l_lang_id, this);

		l_xml_loader.mt_Start();
		l_xml_loader.mt_Wait_For_Ending();
	}

	return l_b_ret;
}

bool StringManager::mt_Load_User(const XML_Element& user)
{
	bool l_b_ret(false);

	l_b_ret = user.mt_Get_Attribute("id", m_current_lang);

	return l_b_ret;
}