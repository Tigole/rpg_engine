#include "ILogger.h"

#include "XMLLogger.h"
#include "DummyLogger.h"

#if LOG_XML == 1
static XMLLogger gs_logger("log.xml", "rpg_engine");
#else
static DummyLogger gs_logger;
#endif

ILogger& log()
{
	return gs_logger;
}

ILogger::ILogger()
{}
ILogger::~ILogger()
{}
ILogger& ILogger::mt_Log(bool b)
{
    std::stringstream ss;
    ss << std::boolalpha;
    ss << b;
    mt_Log(ss.str());
    return *this;
}
ILogger& ILogger::mt_Log(const char* msg)
{
    mt_Log(std::string(msg));
    return *this;
}
ILogger& ILogger::mt_Log(char* msg)
{
    mt_Log(std::string(msg));
    return *this;
}

Logger::Logger(const std::string& fichier)
 :  ILogger(),
    m_file_name(fichier),
    m_file(),
    m_functions(),
    m_events(),
    m_blocks(),
    m_stack_entries()
{
    m_file.open(fichier);
}
Logger::~Logger()
{
    if (m_file.is_open())
        m_file.close();
}

bool Logger::mt_Is_Valid(void)
{
    return m_file.is_open();
}

void Logger::mt_Entrance_Function(const char* function_name)
{
    m_stack_entries.push(&Logger::mt_Exit_Function);
	mt_Manage_Format_Entrance(function_name, m_functions, &Logger::mt_Format_Entrance_Function);
}

void Logger::mt_Exit_Function(void)
{
	mt_Manage_Format_Exit(m_functions, &Logger::mt_Format_Exit_Function);
    m_stack_entries.pop();
}

void Logger::mt_On_Event(const char* event_name)
{
    m_stack_entries.push(&Logger::mt_Stop_Event);
	mt_Manage_Format_Entrance(event_name, m_events, &Logger::mt_Format_On_Evenement);
}

void Logger::mt_Stop_Event(void)
{
	mt_Manage_Format_Exit(m_events, &Logger::mt_Format_Stop_Evenement);
    m_stack_entries.pop();
}

void Logger::mt_Start_Block(const char* block_name)
{
    m_stack_entries.push(&Logger::mt_End_Block);
	mt_Manage_Format_Entrance(block_name, m_blocks, &Logger::mt_Format_Start_Block);
}

void Logger::mt_End_Block(void)
{
	mt_Manage_Format_Exit(m_blocks, &Logger::mt_Format_End_Block);
    m_stack_entries.pop();
}

void Logger::mt_Unstack_Entries_For_Stop_Log(void)
{
    while (m_stack_entries.size())
    {
        (this->*(m_stack_entries.top()))();
    }
}

void Logger::mt_Manage_Format_Entrance(const char* name, std::stack<std::string>& stack, void(Logger::*function)(const char*))
{
    (this->*function)(name);
	stack.push(name);
}

void Logger::mt_Manage_Format_Exit(std::stack<std::string>& stack, void(Logger::*function)(const char*))
{
    if (stack.size())
    {
        (this->*function)(stack.top().c_str());
		stack.pop();
    }
}
