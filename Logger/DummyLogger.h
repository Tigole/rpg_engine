#ifndef DUMMY_LOGGER_H
#define DUMMY_LOGGER_H 1

#include "ILogger.h"

class DummyLogger : public ILogger
{
public:
	virtual bool isValid(void);
    virtual void entranceFunction(const char* function_name);
    virtual void exitFunction(void);
    virtual void onEvent(const char* event_name);
    virtual void stopEvent(void);
    virtual void startBlock(const char* block_name);
    virtual void endBlock(void);
    virtual void stopLog(void);
    virtual ILogger& log(const std::string& msg);

// Documentation
    /** \class DummyLogger
        \brief Objet ne realisant pas d'enregistrement
    **/
};

#endif // DUMMY_LOGGER_H
