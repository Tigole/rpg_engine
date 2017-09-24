#include "DummyLogger.h"

#define DUMMY_LOGGER_UNUSED_PARAMETER(X) (void)(X)

bool DummyLogger::isValid(void)
{
    return true;
}

void DummyLogger::mt_Entrance_Function(const char* function_name)
{
	DUMMY_LOGGER_UNUSED_PARAMETER(function_name);
}

void DummyLogger::mt_Exit_Function(void)
{
	/** *Nothing **/
}

void DummyLogger::onEvent(const char* event_name)
{
	DUMMY_LOGGER_UNUSED_PARAMETER(event_name);
}

void DummyLogger::stopEvent(void)
{
	/** Nothing **/
}

void DummyLogger::mt_Start_Block(const char* block_name)
{
	DUMMY_LOGGER_UNUSED_PARAMETER(block_name);
}

void DummyLogger::mt_End_Block(void)
{
	/** Nothing **/
}

void DummyLogger::stopLog(void)
{
	/** Nothing **/
}

ILogger& DummyLogger::log(const std::string& msg)
{
	DUMMY_LOGGER_UNUSED_PARAMETER(msg);
    return *this;
}
