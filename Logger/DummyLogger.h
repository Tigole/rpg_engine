#ifndef DUMMY_LOGGER_H
#define DUMMY_LOGGER_H 1

#include "ILogger.h"

class DummyLogger : public ILogger
{
public:
	virtual bool isValid(void);
    virtual void mt_Entrance_Function(const char* function_name);
    virtual void mt_Exit_Function(void);
    virtual void onEvent(const char* event_name);
    virtual void stopEvent(void);
    virtual void mt_Start_Block(const char* block_name);
    virtual void mt_End_Block(void);
    virtual void stopLog(void);
    virtual ILogger& log(const std::string& msg);

// Documentation
    /** \class DummyLogger
        \brief Objet ne realisant pas d'enregistrement
    **/
};

#endif // DUMMY_LOGGER_H
