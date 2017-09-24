
#include "XMLLogger.h"
#include <map>
#include <iostream>

XMLLogger::XMLLogger(const std::string& file_path, const std::string& root)
 :  Logger(file_path),
    m_root(root),
    m_tab_counter(1),
    m_write_tab(true)
{
    if (mt_Is_Valid())
    {
        m_file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<" << m_root << ">\n";
        m_file << std::boolalpha;
    }
}

XMLLogger::~XMLLogger()
{
    if (mt_Is_Valid())
		mt_Stop_Log();
}

void XMLLogger::mt_Stop_Log(void)
{
    mt_On_Event("Closing");
    mt_Log("Closing log file.\n");
    mt_Stop_Event();
	mt_Unstack_Entries_For_Stop_Log();
    m_file << "</" << m_root << ">\n";
    m_file.close();
}

ILogger& XMLLogger::mt_Log(const std::string& msg)
{
    if (m_write_tab)
    {
        m_write_tab = false;
        mt_Write_Tab();
    }
    m_file << msg;
    /*
    for (int i = 0; i < msg.size(); i++)
    {
        mt_Write_Charactere(msg[i]);
        if ((msg[i] == '\n') && (i < msg.size() - 1))
            mt_Write_Tab();
    }*/
    if (msg.back() == '\n')
        m_write_tab = true;

	m_file << std::flush;

    return *this;
}

void XMLLogger::mt_Write_Charactere(char caractere)
{
    std::map<char, std::string> caracteres_speciaux;
    std::map<char, std::string>::iterator it;

    caracteres_speciaux['<'] = "&lt;";
    caracteres_speciaux['>'] = "&gt;";
    caracteres_speciaux['&'] = "&amp;";
    caracteres_speciaux['\"'] = "&quot;";
    caracteres_speciaux['\''] = "&apos;";

    it = caracteres_speciaux.find(caractere);
    if (it != caracteres_speciaux.end())
        m_file << it->second;
    else
        m_file << caractere;
}

void XMLLogger::mt_Write_Tab(void)
{
    for (int i = 0; i < m_tab_counter; i++)
        m_file << "  ";
}

void XMLLogger::mt_Format_Entrance_Function(const char* nom_fonction)
{
    mt_Start_Mark("function", nom_fonction);
}

void XMLLogger::mt_Format_Exit_Function(const char* nom_fonction)
{
    mt_End_Mark("function", nom_fonction);
}

void XMLLogger::mt_Format_On_Evenement(const char* nom_evenement)
{
    mt_Start_Mark("event", nom_evenement);
}

void XMLLogger::mt_Format_Stop_Evenement(const char* nom_evenement)
{
    mt_End_Mark("event", nom_evenement);
}

void XMLLogger::mt_Format_Start_Block(const char* nom_block)
{
    mt_Start_Mark("block", nom_block);
}

void XMLLogger::mt_Format_End_Block(const char* nom_block)
{
    mt_End_Mark("block", nom_block);
}

void XMLLogger::mt_Start_Mark(const char* balise, const char* nom)
{
    mt_Write_Tab();
    m_file << "<";
    for (auto c : std::string(balise))
        mt_Write_Charactere(c);
    m_file << " name=\"";
    for (auto c : std::string(nom))
        mt_Write_Charactere(c);
    m_file << "\">\n";
    m_tab_counter++;
}

void XMLLogger::mt_End_Mark(const char* balise, const char* nom)
{
    std::string l_nom(nom);
    std::string::size_type pos(l_nom.find('('));

    if (pos != std::string::npos)
    {
        l_nom.erase(pos);
        pos = l_nom.rfind("::");
        if (pos != std::string::npos)
        {
            l_nom.erase(0, pos + 2);
        }
    }

    if (m_tab_counter > 0)
        m_tab_counter--;
    mt_Write_Tab();
    m_file << "</";
    for (auto c : std::string(balise))
        mt_Write_Charactere(c);
    m_file << "><!-- ";
    for (auto c : l_nom)
        mt_Write_Charactere(c);
    m_file << " -->\n";
}
