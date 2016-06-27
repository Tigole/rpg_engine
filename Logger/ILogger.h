#ifndef _ILOGGER_H
#define _ILOGGER_H 1

#include <string>
#include <sstream>
#include <fstream>
#include <stack>

#include "Miscellaneous.hpp"

class ILogger;

ILogger& log();

class ILogger
{
public:
    ILogger();
    virtual ~ILogger();

    virtual bool isValid(void) = 0;
    virtual void entranceFunction(const char* function_name) = 0;
    virtual void exitFunction(void) = 0;
    virtual void onEvent(const char* event_name) = 0;
    virtual void stopEvent(void) = 0;
    virtual void startBlock(const char* block_name) = 0;
    virtual void endBlock(void) = 0;
    virtual void stopLog(void) = 0;
    virtual ILogger& log(const std::string& msg) = 0;
    ILogger& log(bool b);
    ILogger& log(const char* msg);
    template<typename T>
    ILogger& log(const T& nombre)
    {
        return log(misc::numberToHexDec(nombre));
    }

// Documentation
    /** \class ILogger
        \brief Classe used to log information for debugging purpose using markers.
    **/
};

class Logger : public ILogger
{
public:
    Logger(const std::string& fichier);
    virtual ~Logger();

    bool isValid(void);
    virtual void entranceFunction(const char* function_name);
    virtual void exitFunction(void);
    virtual void onEvent(const char* nom_evenement);
    virtual void stopEvent(void);
    virtual void startBlock(const char* nom_balise);
    virtual void endBlock(void);
protected:
    const std::string m_file_name;
    std::ofstream m_file;

    virtual void FormatEntranceFunction(const char* function_name) = 0;
    virtual void FormatExiteFunction(const char* function_name) = 0;
    virtual void FormatOnEvenement(const char* event_name) = 0;
    virtual void FormatStopEvenement(const char* event_name) = 0;
    virtual void FormatStartBlock(const char* block_name) = 0;
    virtual void FormatEndBlock(const char* block_name) = 0;
    void unstackEntriesForStopLog(void);
private:
    std::stack<std::string> m_functions, m_events, m_blocks;
    std::stack<void (Logger::*)(void)> m_stack_entries;
    void manageFormatEntrance(const char* name, std::stack<std::string>& stack, void (Logger::*function)(const char*));
    void manageFormatExit(std::stack<std::string>& stack, void (Logger::*function)(const char*));

// Documentation
    /** \class Logger
        \brief Concretise partiellement et implemente la methode estValide
    **/
};

template<typename T>
ILogger& operator<<(ILogger& log, const T& msg)
{
    return log.log(msg);
}
/** \fn template<typename T> ILogger& operator<<(ILogger& log, const T& msg)
    \brief Surcharge de l'operateur d'insertion pour le log
    \param[in, out] log Le log
    \param[in] msg la donnee a log
    \return log.
**/

#endif // _ILOGGER_H
