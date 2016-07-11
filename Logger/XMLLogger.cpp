
#include "XMLLogger.h"
#include <map>
#include <iostream>

XMLLogger::XMLLogger(const std::string& file_path, const std::string& root)
 :  Logger(file_path),
    m_root(root),
    m_tab_counter(1),
    m_write_tab(true)
{
    if (isValid())
    {
        m_file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<" << m_root << ">\n";
        m_file << std::boolalpha;
    }
}

XMLLogger::~XMLLogger()
{
    if (isValid())
		stopLog();
}

void XMLLogger::stopLog(void)
{
    onEvent("Closing");
    log("Closing log file.\n");
    stopEvent();
	unstackEntriesForStopLog();
    m_file << "</" << m_root << ">\n";
    m_file.close();
}

ILogger& XMLLogger::log(const std::string& msg)
{
    if (m_write_tab)
    {
        m_write_tab = false;
        writeTab();
    }
    m_file << msg;
    /*
    for (int i = 0; i < msg.size(); i++)
    {
        writeCharactere(msg[i]);
        if ((msg[i] == '\n') && (i < msg.size() - 1))
            writeTab();
    }*/
    if (msg.back() == '\n')
        m_write_tab = true;

	m_file << std::flush;

    return *this;
}

void XMLLogger::writeCharactere(char caractere)
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

void XMLLogger::writeTab(void)
{
    for (int i = 0; i < m_tab_counter; i++)
        m_file << "  ";
}

void XMLLogger::FormatEntranceFunction(const char* nom_fonction)
{
    startMark("function", nom_fonction);
}

void XMLLogger::FormatExiteFunction(const char* nom_fonction)
{
    endMark("function", nom_fonction);
}

void XMLLogger::FormatOnEvenement(const char* nom_evenement)
{
    startMark("event", nom_evenement);
}

void XMLLogger::FormatStopEvenement(const char* nom_evenement)
{
    endMark("event", nom_evenement);
}

void XMLLogger::FormatStartBlock(const char* nom_block)
{
    startMark("block", nom_block);
}

void XMLLogger::FormatEndBlock(const char* nom_block)
{
    endMark("block", nom_block);
}

void XMLLogger::startMark(const char* balise, const char* nom)
{
    writeTab();
    m_file << "<";
    for (auto c : std::string(balise))
        writeCharactere(c);
    m_file << " name=\"";
    for (auto c : std::string(nom))
        writeCharactere(c);
    m_file << "\">\n";
    m_tab_counter++;
}

void XMLLogger::endMark(const char* balise, const char* nom)
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
    writeTab();
    m_file << "</";
    for (auto c : std::string(balise))
        writeCharactere(c);
    m_file << "><!-- ";
    for (auto c : l_nom)
        writeCharactere(c);
    m_file << " -->\n";
}
