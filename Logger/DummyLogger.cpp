#include "DummyLogger.h"

#define DUMMY_LOGGER_UNUSED_PARAMETER(X) (void)(X)

bool DummyLogger::isValid(void)
{
    return true;
}

void DummyLogger::entranceFunction(const char* function_name)
{
	DUMMY_LOGGER_UNUSED_PARAMETER(function_name);
}

void DummyLogger::exitFunction(void)
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

void DummyLogger::startBlock(const char* block_name)
{
	DUMMY_LOGGER_UNUSED_PARAMETER(block_name);
}

void DummyLogger::endBlock(void)
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
