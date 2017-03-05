#include "ILogger.h"

#include "XMLLogger.h"
#include "DummyLogger.h"

#define STRINGIZE(X)	#X


#if LOG_XML == 1
static XMLLogger gs_logger(STRINGIZE(LOG_FILE), "rpg_engine");
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
ILogger& ILogger::log(bool b)
{
    std::stringstream ss;
    ss << std::boolalpha;
    ss << b;
    log(ss.str());
    return *this;
}
ILogger& ILogger::log(const char* msg)
{
    log(std::string(msg));
    return *this;
}
ILogger& ILogger::log(char* msg)
{
    log(std::string(msg));
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

bool Logger::isValid(void)
{
    return m_file.is_open();
}

void Logger::entranceFunction(const char* function_name)
{
    m_stack_entries.push(&Logger::exitFunction);
	manageFormatEntrance(function_name, m_functions, &Logger::FormatEntranceFunction);
}

void Logger::exitFunction(void)
{
	manageFormatExit(m_functions, &Logger::FormatExiteFunction);
    m_stack_entries.pop();
}

void Logger::onEvent(const char* event_name)
{
    m_stack_entries.push(&Logger::stopEvent);
	manageFormatEntrance(event_name, m_events, &Logger::FormatOnEvenement);
}

void Logger::stopEvent(void)
{
	manageFormatExit(m_events, &Logger::FormatStopEvenement);
    m_stack_entries.pop();
}

void Logger::startBlock(const char* block_name)
{
    m_stack_entries.push(&Logger::endBlock);
	manageFormatEntrance(block_name, m_blocks, &Logger::FormatStartBlock);
}

void Logger::endBlock(void)
{
	manageFormatExit(m_blocks, &Logger::FormatEndBlock);
    m_stack_entries.pop();
}

void Logger::unstackEntriesForStopLog(void)
{
    while (m_stack_entries.size())
    {
        (this->*(m_stack_entries.top()))();
    }
}

void Logger::manageFormatEntrance(const char* name, std::stack<std::string>& stack, void(Logger::*function)(const char*))
{
    (this->*function)(name);
	stack.push(name);
}

void Logger::manageFormatExit(std::stack<std::string>& stack, void(Logger::*function)(const char*))
{
    if (stack.size())
    {
        (this->*function)(stack.top().c_str());
		stack.pop();
    }
}
