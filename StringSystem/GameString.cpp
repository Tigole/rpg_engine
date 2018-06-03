#include "GameString.hpp"


GameString::GameString(const std::string& sentence)
	:m_sentence(sentence)
{}

std::string GameString::mt_Get_String(const GameStringArguments& args)
{
	std::string l_ret; 

	for (std::size_t i = 0; i < m_sentence.size(); i++)
	{
		if (m_sentence[i] == '{')
		{
			i = mt_Parse_Arg(i, l_ret, args);
		}
		else
		{
			l_ret.push_back(m_sentence[i]);
		}
	}

	return l_ret;
}

void GameString::mt_Set(const std::string& sentence)
{
	m_sentence = sentence;
}

std::size_t GameString::mt_Parse_Arg(std::size_t start, std::string& ret, const GameStringArguments& args)
{
	std::string l_arg_name;
	std::size_t l_stop;
	GameStringArguments::const_iterator l_it;

	l_stop = m_sentence.find('}', start);

	l_arg_name = m_sentence.substr(start + 1, l_stop - 1);

	l_it = args.find(l_arg_name);
	if (l_it != args.end())
	{
		ret += l_it->second;
	}
	else
	{
		ret += '{' + l_arg_name + '}';
	}

	return l_stop;
}